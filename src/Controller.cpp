#include "Controller.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <assert.h>

Controller::Controller(sf::RenderWindow & window):window_(window)
{
    //ctor
    assert(instance == nullptr); // do not make 2 instances of controller.

    mousePressed = false;
    isRunning_ = true;
    instance = this;
    pressedKeys_ = std::vector<bool>(sf::Keyboard::KeyCount, false);
    lastKeys_ = std::vector<bool>(sf::Keyboard::KeyCount, false);
    pressedButtons_ = std::vector<bool>(sf::Mouse::ButtonCount, false);
    lastButtons_ = std::vector<bool>(sf::Mouse::ButtonCount, false);



    //add handlers for reading controls
    addDefaultHandlers();

}

Controller::~Controller()
{
    //dtor
    assert(instance != nullptr);
    instance = nullptr;
}
void Controller::addDefaultHandlers()
{
     //fill handlers with empty functions
    handlers_=  std::vector<EventHandler>(sf::Event::EventType::Count, [](const sf::Event & event) {});
    handlersSet_  = std::vector<bool>(sf::Event::EventType::Count, false);

    //set the functions
    addHandler(sf::Event::EventType::KeyPressed, [&](const sf::Event & event)
    {
        if(event.key.code >= 0)
            pressedKeys_[event.key.code] = true;
    });


    addHandler(sf::Event::EventType::KeyReleased, [&](const sf::Event & event)
    {
        if(event.key.code >= 0)
            pressedKeys_[event.key.code] = false;
    });
    addHandler(sf::Event::EventType::TextEntered, [&](const sf::Event & event)
    {
        uint32_t uniC = event.text.unicode;
        if(uniC < 128)
        {
            std::string newTxt = "";
            sf::Utf32::encodeAnsi(uniC, std::back_inserter(newTxt));
            capturedText += newTxt;
        }
    });
    addHandler(sf::Event::EventType::Closed,[&](const sf::Event & event)
    {
        isRunning_ = false;
        window_.close();
    });
    addHandler(sf::Event::EventType::MouseButtonPressed,  [&](const sf::Event & event)
    {
       pressedButtons_[event.mouseButton.button] = true;
    });
    addHandler(sf::Event::EventType::MouseButtonReleased, [&](const sf::Event & event)
    {
        pressedButtons_[event.mouseButton.button] = false;
    });

}
void Controller::addHandler(sf::Event::EventType type, EventHandler handler )
{
    assert(instance != nullptr); // the controller must be instanciated somewhere before.

    assert(instance->handlersSet_[type] == false); // adding multiple handlers to the same event, not supported
    instance->handlers_[type] = handler;
    instance->handlersSet_[type] = true;
}
void Controller::removeHandler(sf::Event::EventType type)
{
    if(instance){

		assert(instance != nullptr);
		assert(instance->handlersSet_[type]);
		instance->handlers_[type] = [](const sf::Event &){};
		instance->handlersSet_[type] = false;
    }
    else
	{
		//game is being deconstructed
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
        handlers_[event.type](event);
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
