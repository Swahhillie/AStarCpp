#include "CameraController.hpp"
#include "Scene.hpp"
#include <math.h>
#include "Time.hpp"
#include "Controller.hpp"
#include <assert.h>
#include <functional>

CameraController::CameraController(const std::string & name):GameObject(name),
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




        float currentRotation = view_.getRotation();

         dir = rotateVector2(dir, currentRotation);


        //calculate the distance that will be traveled in 1 second
        float magnitude = sqrtf(dir.x * dir.x + dir.y * dir.y);
        dir /= magnitude;


        dir *= moveSpeed_;

        //limit speed by dt
        dir *= Time::deltaTime;


        //rotate dir by the views rotation

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
sf::Vector2f CameraController::rotateVector2(const sf::Vector2f & v, float degrees)
{
    float cosRadians = cos(degrees * degToRad);
    float sinRadians = sin(degrees * degToRad);

    return sf::Vector2f(
               v.x * cosRadians - v.y * sinRadians,
               v.x * sinRadians + v.y * cosRadians);
}
