#include "CameraController.hpp"
#include "Scene.hpp"
#include <math.h>
#include "Time.hpp"
#include "Controller.hpp"
CameraController::CameraController(const std::string & name):GameObject(name),view_(Scene::instance().getView())
{
	//ctor
}

CameraController::~CameraController()
{
	//dtor
}
void CameraController::update()
{
	float speed = 50.0f;
	sf::Vector2f dir(0.0f, 0.0f);
	if(Controller::getKey(sf::Keyboard::Key::D))
	dir.x += speed;
	if(Controller::getKey(sf::Keyboard::Key::A))
	dir.x -= speed;
	if(Controller::getKey(sf::Keyboard::Key::W))
	dir.y -= speed;
	if(Controller::getKey(sf::Keyboard::Key::S))
	dir.y += speed;

	//normalize dir
	if(dir != sf::Vector2f(0,0))
	{
		float magnitude = sqrtf(dir.x * dir.x + dir.y * dir.y);
		dir /= magnitude;
		dir *= speed;
		dir *= Time::deltaTime;
		//std::cout << dir.x << ", " << dir.y << std::endl;
		view_.move(dir);
	}

}
