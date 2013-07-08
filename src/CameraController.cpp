#include "CameraController.hpp"
#include "Scene.hpp"
#include <math.h>
#include "Time.hpp"
#include "Controller.hpp"
#include <assert.h>
#include <functional>

CameraController::CameraController(const std::string & name):GameObject(name),
    moveSpeed_(100.0f),
    zoomSpeed_(.5f),
    view_(Scene::instance().getView())
{
    //ctor

    //bind add a listener to the resize event of the controller
    auto resizeHandlerFunc = std::bind(&CameraController::resizeHandler, this, std::placeholders::_1);
    Controller::addHandler(sf::Event::EventType::Resized, resizeHandlerFunc);
}

CameraController::~CameraController()
{
    //dtor
    Controller::removeHandler(sf::Event::EventType::Resized);
}
void CameraController::update()
{

    moveView();
    rotateView();
    zoomView();



}
void CameraController::rotateView()
{

    if(Controller::getKey(sf::Keyboard::Key::Z))
    {
        view_.rotate(rotateSpeed_ * Time::deltaTime);
    }
    if(Controller::getKey(sf::Keyboard::Key::X))
    {
        view_.rotate(-rotateSpeed_ * Time::deltaTime);
    }
}
void CameraController::moveView()
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

}
void CameraController::zoomView()
{
    if(Controller::getKey(sf::Keyboard::Key::Q))
    {
        view_.zoom(1.0f + zoomSpeed_ * Time::deltaTime);
    }
    else if(Controller::getKey(sf::Keyboard::Key::E))
    {
        view_.zoom(1.0f - zoomSpeed_ * Time::deltaTime);
    }

}
void CameraController::resizeHandler(const sf::Event & event)
{
    assert(event.type == sf::Event::EventType::Resized);
    sf::FloatRect visibleArea(view_.getCenter().x - view_.getSize().x /2, view_.getCenter().y - view_.getSize().y /2, event.size.width, event.size.height);
    view_ = sf::View(visibleArea);
}
