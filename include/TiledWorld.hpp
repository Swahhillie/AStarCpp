#ifndef TILEDWORLD_HPP
#define TILEDWORLD_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class TiledWorld : public GameObject
{
	public:
		TiledWorld(const std::string & name);
		virtual ~TiledWorld();


		void generateWorld(int columns, int rows, const sf::Vector2f & tileSize);
	protected:

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	private:


		sf::VertexArray quads_;
		sf::Texture worldSprite_;


};

#endif // TILEDWORLD_HPP
