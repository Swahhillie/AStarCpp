#include "TiledWorld.hpp"
#include <assert.h>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include "UnitTest++.h"

TiledWorld::TiledWorld(const std::string & name)
:GameObject(name)
{
	//ctor

}

TiledWorld::~TiledWorld()
{
	//dtor
}
void TiledWorld::generateWorld(int x, int y, const sf::Vector2f & tileSize)
{
	int verticeCount = x * y * 4;

	quads_ = sf::VertexArray(sf::Quads, verticeCount);

	auto tileIndex = 0;
	auto c = 0;
	auto r = 0;
	for(auto i = 0; i < verticeCount; i+=4, tileIndex ++)
	{
		c  = tileIndex % x ;
		r = tileIndex / x;

		quads_[i + 0].position = sf::Vector2f(c * tileSize.x, r * tileSize.y); //top left
		quads_[i + 1].position = sf::Vector2f(c * tileSize.x + tileSize.x, r * tileSize.y); // top right
		quads_[i + 2].position = sf::Vector2f(c * tileSize.x, r * tileSize.y) + tileSize; //bottom right
		quads_[i + 3].position = sf::Vector2f(c * tileSize.x, r * tileSize.y + tileSize.y); //bottom left

	}
	assert(tileIndex == x * y);


}
void TiledWorld::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	states.texture = &worldSprite_;
	target.draw(quads_, states);
}
void TiledWorld::loadTiledMap()
{
	std::ifstream file("assets/hubworld.json", std::ifstream::in);
	std::string fullFileContent;
	std::string temp;
	while(std::getline(file, temp))
	{
		fullFileContent.append(temp);
	}
	tiledFile_.loadFromJsonString(fullFileContent);



	bool loadingSuccess = worldSprite_.loadFromFile("assets/" + tiledFile_.tilesets.front().image);

	generateWorld(tiledFile_.width, tiledFile_.height, sf::Vector2f(tiledFile_.tilewidth, tiledFile_.tilewidth));
	assert (loadingSuccess);
}


