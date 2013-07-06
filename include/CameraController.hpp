#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class CameraController : public GameObject
{
	public:
		CameraController(const std::string & name);
		virtual ~CameraController();
	protected:

		virtual void update();

	private:
		float moveSpeed_;
		float zoomSpeed_;
		sf::View & view_;

		void resizeHandler(const sf::Event & event);
};

#endif // CAMERACONTROLLER_HPP
