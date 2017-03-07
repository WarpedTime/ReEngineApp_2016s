#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region YOUR CODE GOES HERE

	//get program run time
	static DWORD timerSinceBoot = GetTickCount(); //computer boot time (ms)
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot; //program boot time (ms)
	float fTimer = timerSinceStart / 1000.0f;
	
	//print timer
	m_pMeshMngr->PrintLine(""); //one empty because window bar hides the first one
	m_pMeshMngr->Print(std::to_string(fTimer)); //print
	
	//make a sphere
	matrix4 m4SpherePosition = glm::translate(vector3(1,0,0)) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, RERED, WIRE | SOLID);

	//make model move lerp between two points
	vector3 v3Start = targets[currentTarget];
	vector3 v3End = vector3(5, 0, 0);
	float reachInTime = 5.0f; //time  to reach goal
	float percentage = MapValue(fTimer, 0.0f , reachInTime, 0.0f, 1.0f); //percentage of distance travelled
	//stop moving at end
	if (percentage > 1.0f) { 
		percentage = 1.0f;
	}
	
	//current model position
	vector3 v3Current = glm::lerp(v3Start, v3End, percentage);
	m_pMeshMngr->PrintLine("Move Progress: " + std::to_string(percentage), vector3(0, 255, 0));

	//move model
	matrix4 m4Creeper = glm::translate(v3Current);
	m_pMeshMngr->SetModelMatrix(m4Creeper, "WallEye");
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}