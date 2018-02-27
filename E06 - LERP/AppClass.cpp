#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(vector3(5.0f,3.0f,15.0f), ZERO_V3, AXIS_Y);

	m_pModel = new Simplex::Model();
	m_pModel->Load("Sorted\\WallEye.bto");
	
	m_stopsList.push_back(vector3(-4.0f, -2.0f, 5.0f));
	m_stopsList.push_back(vector3(1.0f, -2.0f, 5.0f));

	m_stopsList.push_back(vector3(-3.0f, -1.0f, 3.0f));
	m_stopsList.push_back(vector3(2.0f, -1.0f, 3.0f));

	m_stopsList.push_back(vector3(-2.0f, 0.0f, 0.0f));
	m_stopsList.push_back(vector3(3.0f, 0.0f, 0.0f));

	m_stopsList.push_back(vector3(-1.0f, 1.0f, -3.0f));
	m_stopsList.push_back(vector3(4.0f, 1.0f, -3.0f));

	m_stopsList.push_back(vector3(0.0f, 2.0f, -5.0f));
	m_stopsList.push_back(vector3(5.0f, 2.0f, -5.0f));

	m_stopsList.push_back(vector3(1.0f, 3.0f, -5.0f));
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Draw the model
	m_pModel->PlaySequence();

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer


	//your code goes here
	static std::vector<vector3> v3Stop;

	static bool bInit = false;

	if (!bInit)
	{
		v3Stop.push_back(vector3(-4.0f, -2.0f, 5.0f));
		v3Stop.push_back(vector3(1.0f, -2.0f, 5.0f));
		v3Stop.push_back(vector3(-3.0f, -1.0f, 3.0f));
		v3Stop.push_back(vector3(2.0f, -1.0f, 3.0f));
		v3Stop.push_back(vector3(-2.0f, 0.0f, 0.0f));
		v3Stop.push_back(vector3(3.0f, 0.0f, 0.0f));
		v3Stop.push_back(vector3(-1.0f, 1.0f, -3.0f));
		v3Stop.push_back(vector3(4.0f, 1.0f, -3.0f));
		v3Stop.push_back(vector3(0.0f, 2.0f, -5.0f));
		v3Stop.push_back(vector3(5.0f, 2.0f, -5.0f));
		v3Stop.push_back(vector3(1.0f, 3.0f, -5.0f));
		bInit = true;
	}

	vector3 v3Start;
	vector3 v3End;
	static uint route = 0;

	v3Start = v3Stop[route];
	v3End = v3Stop[(route + 1) % v3Stop.size()];

	float fTimeBetweenStops = 2.0;
	float fPercentage = MapValue(fTimer, 0.0f, fTimeBetweenStops, 0.0f, 1.0f);
	vector3 v3CurrentPos = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 m4Model = glm::translate(IDENTITY_M4, v3CurrentPos);
	
	if (fPercentage >= 1.0f)
	{
		route++;
		fTimer = m_pSystem->GetDeltaTime(uClock);
		route %= v3Stop.size();
	}

	m_pModel->SetModelMatrix(m4Model);

	m_pMeshMngr->Print("\nTimer: ");//Add a line on top
	m_pMeshMngr->PrintLine(std::to_string(fTimer), C_YELLOW);

	// Draw stops
	for (uint i = 0; i < m_stopsList.size(); ++i)
	{
		m_pMeshMngr->AddSphereToRenderList(glm::translate(m_stopsList[i]) * glm::scale(vector3(0.05f)), C_GREEN, RENDER_WIRE);
	}
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pModel);
	//release GUI
	ShutdownGUI();
}