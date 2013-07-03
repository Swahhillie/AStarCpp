#include "TiledWorld.hpp"
#include <assert.h>

TiledWorld::TiledWorld(int columns, int rows, const sf::Vector2f & tileSize)
{
	//ctor
	int verticeCount = columns * rows * 4;

	quads_ = sf::VertexArray(sf::Quads, verticeCount);

	auto tileIndex = 0;
	for(auto i = 0; i < columns * rows; i+=4, tileIndex ++)
	{

		auto c = tileIndex % columns;
		auto r = tileIndex % rows;
		quads_[i + 0].position = sf::Vector2f(c * tileSize.x, c * tileSize.y); //top left
		quads_[i + 1].position = sf::Vector2f(c * tileSize.x + tileSize.x, c * tileSize.y); // top right
		quads_[i + 2].position = sf::Vector2f(c * tileSize.x, c * tileSize.y + tileSize.y); //bottom left
		quads_[i + 3].position = sf::Vector2f(c * tileSize.x, c * tileSize.y) + tileSize; //bottom right

		quads_[i + 0].texCoords = sf::Vector2f(0, 0);
		quads_[i + 1].texCoords = sf::Vector2f(100, 0);
		quads_[i + 2].texCoords = sf::Vector2f(0, 100);
		quads_[i + 3].texCoords = sf::Vector2f(100, 100);

	}

	bool loadingSuccess = worldSprite_.loadFromFile("assets/superBasicTile100x100.png");
	assert (loadingSuccess);

}

TiledWorld::~TiledWorld()
{
	//dtor
}
void TiledWorld::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	states.texture = &worldSprite_;
	target.draw(quads_, states);
}
