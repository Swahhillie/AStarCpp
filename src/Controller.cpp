#include "Controller.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Controller::Controller(sf::RenderWindow & window):window_(window)
{
    //ctor
    mousePressed = false;
    isRunning_ = true;
    instance = this;
    pressedKeys_ = std::vector<bool>(sf::Keyboard::KeyCount, false);
    lastKeys_ = std::vector<bool>(sf::Keyboard::KeyCount, false);
    pressedButtons_ = std::vector<bool>(sf::Mouse::ButtonCount, false);
    lastButtons_ = std::vector<bool>(sf::Mouse::ButtonCount, false);

}

Controller::~Controller()
{
    //dtor
}
void Controller::handleEvent(const sf::Event & event)
{
    switch (event.type)
    {
    case sf::Event::TextEntered:
    {
        uint32_t uniC = event.text.unicode;
        if(uniC < 128)
        {
            std::string newTxt = "";
            sf::Utf32::encodeAnsi(uniC, std::back_inserter(newTxt));
            capturedText += newTxt;
        }
    }
    break;
    case sf::Event::Closed:
        {
            //window_ closed. should destroy everything now..
        isRunning_ = false;
        window_.close();

        }
    break;
    case sf::Event::KeyPressed:
        {

        if(event.key.code >= 0)
            pressedKeys_[event.key.code] = true;

        }
    break;
    case sf::Event::KeyReleased:
        {
                    if(event.key.code >= 0)
            pressedKeys_[event.key.code] = false;

        }
    break;
    case sf::Event::MouseButtonPressed:
        {
             pressedButtons_[event.mouseButton.button] = true;

        }
    break;
    case sf::Event::MouseButtonReleased:
        {

            pressedButtons_[event.mouseButton.button] = false;
        }
    break;
    case sf::Event::Resized:
        {
            //Scene::instance().getView().setSize(event.size.width, event.size.height);
        }
        break;
    case sf::Event::LostFocus:
        {

        }
        break;
    case sf::Event::GainedFocus:
        {

        }
        break;
    default:
        {
            //std::cout << "Unhandled event : " << event.type << std::endl;
        }
    }




}
void Controller::update()
{

    //if the window_ has been closed the controller will do nothing
    if(!isRunning_)return;


    refresh();

    sf::Event event;
    while(window_.pollEvent(event))
    {
        handleEvent(event);
    }
    mousePosition = sf::Mouse::getPosition(window_);
    //update is used for continuos events suchs when a key is held down.
}
void Controller::refresh()
{
    lastKeys_ = std::vector<bool>(pressedKeys_);

    lastMousePosition = mousePosition;

    lastButtons_ = std::vector<bool>(pressedButtons_);

    capturedText = "";


}

bool Controller::getKey(sf::Keyboard::Key keyCode)
{
    return instance->pressedKeys_[keyCode];
}

bool Controller::getKeyUp(sf::Keyboard::Key keyCode)
{
    return instance->lastKeys_[keyCode] == true && instance->pressedKeys_[keyCode] == false;
}

bool Controller::getKeyDown(sf::Keyboard::Key keyCode)
{
    return instance->lastKeys_[keyCode] == false && instance->pressedKeys_[keyCode] == true;
}

bool Controller::getButton(sf::Mouse::Button button)
{
    return instance->pressedButtons_[button];
}

bool Controller::getButtonUp(sf::Mouse::Button button)
{
    return instance->lastButtons_[button] == true && instance->pressedButtons_[button] == false;
}

bool Controller::getButtonDown(sf::Mouse::Button button)
{
    return instance->lastButtons_[button] == false && instance->pressedButtons_[button] == true;
}

sf::Vector2i Controller::getDeltaMouse()
{
    return lastMousePosition - mousePosition;
}

bool Controller::getTextEntered(std::string & input)
{
    if(instance->capturedText != "")
    {
        input = instance->capturedText;
        return true;
    }
    else return false;
}
std::ostream & operator <<(std::ostream & left, const sf::Event::EventType & right)
{
    static const char * enumNames[] =
    {
         "None","Resized","LostFocus","GainedFocus","TextEntered","KeyPressed","KeyReleased",
         "MouseWheelMoved","MouseButtonPressed","MouseButtonReleased","MouseMoved",
         "MouseEntered","MouseLeft","JoystickButtonPressed","JoystickButtonReleased","JoystickMoved",
         "JoystickConnected","JoystickDisconnected","Count"
    };
    /*
    switch(right)
    {
        case sf::Event::EventType::Resized:                 left << "Resized"; break;
        case sf::Event::EventType::LostFocus:               left << "LostFocus"; break;
        case sf::Event::EventType::GainedFocus:             left << "GainedFocus"; break;
        case sf::Event::EventType::TextEntered:             left << "TextEntered"; break;
        case sf::Event::EventType::KeyPressed:              left << "KeyPressed"; break;
        case sf::Event::EventType::KeyReleased:             left << "KeyReleased"; break;
        case sf::Event::EventType::MouseWheelMoved:         left << "MouseWheelMoved"; break;
        case sf::Event::EventType::MouseButtonPressed:      left << "MouseButtonPressed"; break;
        case sf::Event::EventType::MouseButtonReleased:     left << "MouseButtonReleased"; break;
        case sf::Event::EventType::MouseMoved:              left << "MouseMoved"; break;
        case sf::Event::EventType::MouseEntered:            left << "MouseEntered"; break;
        case sf::Event::EventType::MouseLeft:               left << "MouseLeft"; break;
        case sf::Event::EventType::JoystickButtonPressed:   left << "JoystickButtonPressed"; break;
        case sf::Event::EventType::JoystickButtonReleased:  left << "JoystickButtonReleased"; break;
        case sf::Event::EventType::JoystickMoved:           left << "JoystickMoved"; break;
        case sf::Event::EventType::JoystickConnected:       left << "JoystickConnected"; break;
        case sf::Event::EventType::JoystickDisconnected:    left << "JoystickDisconnected"; break;
        case sf::Event::EventType::Count:                   left << "Count"; break;
    }
    */
    return left << enumNames[right];
}
Controller * Controller::instance;
sf::Vector2i Controller::mousePosition;
sf::Vector2i Controller::lastMousePosition;
