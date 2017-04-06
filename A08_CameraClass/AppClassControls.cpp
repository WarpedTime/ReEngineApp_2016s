#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	//F1 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 100.0f);
		m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	//F2 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f); //field of view, aspect ratio, near clipping, far clipping
		m_m4View = glm::lookAt(glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //origin, look at(normalized), up vector
	}

	//F3 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
	{
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 16.0f);
		m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	//F4 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
	{
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f); //field of view, aspect ratio, near clipping, far clipping
		m_m4View = glm::lookAt(glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //origin, look at(normalized), up vector
	}

	//F5 Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
	{
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 2000.0f, 0.01f, 1000.0f); //field of view, aspect ratio, near clipping, far clipping
		m_m4View = glm::lookAt(glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //origin, look at(normalized), up vector
	}
	//move forwards
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		camera.MoveForward(-0.1f);
	}
	//move backwards
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		camera.MoveForward(0.1f);
	}
	//strafe right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		camera.MoveSideways(-0.1f);
	}
	//strafe left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		camera.MoveSideways(0.1f);
	}
	//move up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		camera.MoveVertical(0.1f);
	}
	//move down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		camera.MoveVertical(-0.1f);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouseMove = true;
	}
	else mouseMove = false;

	//alternate for mouse controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//camera.ChangePitch(0.1f);
		camera.ChangeRoll(0.1f);
		//camera.ChangeYaw(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//camera.ChangePitch(-0.1f);
		camera.ChangeRoll(-0.1f);
		//camera.ChangeYaw(-0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//camera.ChangePitch(0.1f);
		//camera.ChangeRoll(0.1f);
		camera.ChangeYaw(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//camera.ChangePitch(-0.1f);
		//camera.ChangeRoll(-0.1f);
		camera.ChangeYaw(-0.1f);
	}


	//reset
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		camera = Camera();
	}

	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}