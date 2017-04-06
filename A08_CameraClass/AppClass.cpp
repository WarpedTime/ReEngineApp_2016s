#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E10_Projections"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);

	//Generate the Cylinder
	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(1.0f, 1.0f, 10, REGREEN);

	camera = Camera();

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f); //field of view, aspect ratio, near clipping, far clipping
	m_m4Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);  
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //origin, look at(normalized), up vector
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	vector3 origin = vector3(0.0, 0.0, -3.0f);

	//mouse move
	if (mouseMove) {
		float width = m_pWindow->GetWidth();
		float height = m_pWindow->GetHeight();
		
		vector3 cen = vector3(width / 2, height / 2, 1.0f);
		vector3 mPos = vector3(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, 1.0f);

		vector3 mDir = mPos - cen;
		mDir.z = camera.v3Position.z;
		camera.SetTarget(mDir-origin);
	}






}

vector3 AppClass::NormalizeV3(vector3 v)
{
	float mag = sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
	return vector3(v.x / mag, v.y / mag, v.z / mag);
}
void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the cone
	m_pCone->Render(camera.GetProjection(false), camera.GetView() , IDENTITY_M4);

	//Render the cylinder
	m_pCylinder->Render(camera.GetProjection(false), camera.GetView(), glm::translate(IDENTITY_M4, REAXISZ * -3.0f));

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	super::Release(); 
}