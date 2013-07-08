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
		float moveSpeed_ = 100.f;
		float zoomSpeed_ = 0.5f;
		float rotateSpeed_ = 50.0f;
		sf::View & view_;

		void resizeHandler(const sf::Event & event);

		void moveView();
		void zoomView();
		void rotateView();





};

#endif // CAMERACONTROLLER_HPP
