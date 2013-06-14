#ifndef TILEGRAPHIC_HPP
#define TILEGRAPHIC_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class TileGraphic : public GameObject
{
	public:
		TileGraphic(std::string name);
		virtual ~TileGraphic();
	protected:
		virtual void update();
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	private:

		sf::RectangleShape rectangle;
};

#endif // TILEGRAPHIC_HPP
