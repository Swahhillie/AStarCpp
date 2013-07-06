#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <functional>

class Controller
{
public:
    Controller(sf::RenderWindow & window);
    virtual ~Controller();

    void update();
    bool running()const
    {
        return isRunning_;
    }
    void stopRunning()
    {
        isRunning_ = false;
    }

    //keyboard
    static bool getKey(sf::Keyboard::Key keyCode);
    static bool getKeyDown(sf::Keyboard::Key keyCode);
    static bool getKeyUp(sf::Keyboard::Key keyCode);

    //mouse
    static bool getButton(sf::Mouse::Button button);
    static bool getButtonDown(sf::Mouse::Button button);
    static bool getButtonUp(sf::Mouse::Button button);
    typedef std::function<void (const sf::Event &)> EventHandler;

    static void addHandler(sf::Event::EventType type, EventHandler handler);
    static void removeHandler(sf::Event::EventType type);
/** \brief If a text event has occurred in the last frame txt will be set to the captured text.
 *
 * \param string will be set to caught characters of the last frame.
 * \return If any text was entered will return true.
 */

	static bool getTextEntered(std::string & txt);

    static sf::Vector2i getDeltaMouse();

    static sf::Vector2i mousePosition;
    static sf::Vector2i lastMousePosition;


protected:
private:

    sf::RenderWindow & window_;
    bool isRunning_;


private:
    void refresh();


    std::vector< EventHandler > handlers_;
    std::vector<bool> handlersSet_;

    void addDefaultHandlers();

    static Controller * instance;
    std::vector<bool> pressedKeys_;
    std::vector<bool> lastKeys_;

    std::vector<bool> pressedButtons_;
    std::vector<bool> lastButtons_;


	std::string capturedText;

    bool mousePressed;


};
std::ostream & operator << (std::ostream & left, const sf::Event::EventType & type);
#endif // CONTROLLER_H
