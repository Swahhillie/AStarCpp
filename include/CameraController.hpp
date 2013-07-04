#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP

#include "GameObject.hpp"


class CameraController : public GameObject
{
	public:
		CameraController(const std::string & name);
		virtual ~CameraController();
	protected:

		virtual void update();

	private:

		sf::View & view_;
};

#endif // CAMERACONTROLLER_HPP
