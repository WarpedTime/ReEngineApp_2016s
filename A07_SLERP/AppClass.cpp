#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - YOUR USER NAME GOES HERE"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	m_m4Sun = IDENTITY_M4;
	m_m4Earth = IDENTITY_M4;
	m_m4Moon = IDENTITY_M4;

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	static float fTimer = 0.0f;
	fTimer += m_pSystem->LapClock(); //dt

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

#pragma region MYCODE
	
	//This matrices will hold the relative transformation of the Moon and the Earth
	matrix4 distanceEarth = glm::translate(11.0f, 0.0f, 0.0f);
	matrix4 distanceMoon = glm::translate(2.0f, 0.0f, 0.0f);

	quaternion angleZero = glm::quat(vector3(0.0f,0.0f, 0.0f));
	quaternion angle180Y = glm::quat(vector3(0.0f, glm::radians(180.0f), 0.0f)); 
	quaternion angle180Z = glm::quat(vector3(0.0f, 0.0f ,glm::radians(180.0f)));

	//SUN
	//move sun with x,y,z (+shift for inverse)
	m_m4Sun = glm::translate(IDENTITY_M4, sunPos);

	//EARTH
	//Calculate the position of the Earth
	//m_m4Earth = glm::rotate(m_m4Sun, m_fEarthTimer, vector3(0.0f, 1.0f, 0.0f));
	quaternion q3 = glm::mix(angleZero, angle180Y, (float)fRunTime/365);
	m_m4Earth = ToMatrix4(q3);

	//tanslate to proper position based on sun and orbit
	m_m4Earth = glm::translate(m_m4Earth*distanceEarth, vector3(0, 0, 0));

	//save the location without earth rotation for moon
	matrix4 tempEarth = m_m4Earth;

	//rotate around self axis
	//m_m4Earth = glm::rotate(m_m4Earth, m_fEarthTimer * 360, vector3(0.0f, 0.0f, 1.0f));
	//q3 = glm::mix(angleZero, angle180Z, (float)fRunTime);
	//m_m4Earth = glm::rotate(q3,vector3(0,0,1.0f));

	//MOON
	//Calculate the position of the Moon
	m_m4Moon = glm::rotate(tempEarth, m_fMoonTimer, vector3(0.0f, 1.0f, 0.0f));

	//translate
	m_m4Moon = glm::translate(m_m4Moon*distanceMoon, vector3(0, 0, 0));

	//rotate around self axis
	m_m4Moon = glm::rotate(m_m4Moon, m_fMoonTimer * 24, vector3(1.0f, 0.0f, 0.0f));

	//scale earth and moon a bit
	m_m4Moon = glm::scale(m_m4Moon, vector3(0.20f, 0.20f, 0.20f));
	m_m4Earth = glm::scale(m_m4Earth, vector3(0.50f, 0.50f, 0.50f));





#pragma endregion

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	//update timers
	m_fMoonTimer++;//Increase Moon timer
	m_fEarthTimer = m_fMoonTimer / 28.0f; //divide by the moon's day
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList();
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}