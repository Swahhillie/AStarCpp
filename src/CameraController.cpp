#include "CameraController.hpp"
#include "Scene.hpp"
#include <math.h>
#include "Time.hpp"
#include "Controller.hpp"
CameraController::CameraController(const std::string & name):GameObject(name),
    moveSpeed_(100.0f),
    zoomSpeed_(.5f),
    view_(Scene::instance().getView())
{
    //ctor
}

CameraController::~CameraController()
{
    //dtor
}
void CameraController::update()
{

    sf::Vector2f dir(0.0f, 0.0f);
    if(Controller::getKey(sf::Keyboard::Key::D))
        dir.x += moveSpeed_;
    if(Controller::getKey(sf::Keyboard::Key::A))
        dir.x -= moveSpeed_;
    if(Controller::getKey(sf::Keyboard::Key::W))
        dir.y -= moveSpeed_;
    if(Controller::getKey(sf::Keyboard::Key::S))
        dir.y += moveSpeed_;

    //normalize dir
    if(dir != sf::Vector2f(0,0))
    {
        float magnitude = sqrtf(dir.x * dir.x + dir.y * dir.y);
        dir /= magnitude;
        dir *= moveSpeed_;
        dir *= Time::deltaTime;
        //std::cout << dir.x << ", " << dir.y << std::endl;
        view_.move(dir);
    }

    if(Controller::getKey(sf::Keyboard::Key::Q))
    {
        view_.zoom(1.0f + zoomSpeed_ * Time::deltaTime);
    }
    else if(Controller::getKey(sf::Keyboard::Key::E))
    {
        view_.zoom(1.0f - zoomSpeed_ * Time::deltaTime);
    }


}
