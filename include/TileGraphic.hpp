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

		void setText(std::string txt){debugText_.setString(txt);}
	protected:
		virtual void update();
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	private:
		sf::Text debugText_;
		sf::RectangleShape rectangle_;

		static sf::Font debugTextFont_;
};

#endif // TILEGRAPHIC_HPP
