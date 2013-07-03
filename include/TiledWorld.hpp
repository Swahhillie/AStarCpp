#ifndef TILEDWORLD_HPP
#define TILEDWORLD_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class TiledWorld : public GameObject
{
	public:
		TiledWorld(int columns, int rows, const sf::Vector2f & tileSize);
		virtual ~TiledWorld();



	protected:

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	private:


		sf::VertexArray quads_;
		sf::Texture worldSprite_;


};

#endif // TILEDWORLD_HPP
