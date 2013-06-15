#ifndef TILEGRAPHIC_HPP
#define TILEGRAPHIC_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
class Tile;

class TileGraphic : public GameObject
{
	friend class Tile;
	public:
		TileGraphic(std::string name);
		virtual ~TileGraphic();
	protected:
		virtual void update();
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	private:
		sf::Text debugText;
		sf::RectangleShape rectangle;

		static sf::Font debugTextFont;
};

#endif // TILEGRAPHIC_HPP
