#include "TileManager.hpp"
#include <vector>
#include <sstream>
#include "Tile.hpp"
#include <iostream>
#include "Scene.hpp"
#include "TileGraphic.hpp"

TileManager::TileManager():
	columns_(20),
	rows_(10)
{
	//ctor
	generateTiles();
}

TileManager::~TileManager()
{
	//dtor
}

TileManager::TileManager(const TileManager& other)
{
	//copy ctor
}

TileManager& TileManager::operator=(const TileManager& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment opersstream << "\n";ator
	return *this;
}

void TileManager::generateTiles(){

	tiles_.resize(rows_);

	for(auto i = 0; i < rows_; i++)
	{
		tiles_[i].resize(columns_);
	}



	Scene & scene = Scene::instance();
	GameObject * tileHolder = scene.createGameObject<GameObject>("TileHolder");
	for(auto i = 0; i < rows_; i++)
	{
		for(auto j = 0; j < columns_; j++)
		{
			auto * go = scene.createGameObject<TileGraphic>("Tile");
			go->setParent(tileHolder);
			tiles_[i][j] = std::unique_ptr<Tile>(new Tile(i, j, go));
		}
	}

/*
	for(auto i = 0; i < height_; i++)
	{

		for(auto j = 0 ; j < width_; j++)
		{
			tiles_[i][j] = new Tile(i, j);
			sstream << (i * height_ + j) << ",";
		}
		sstream << "\n";

	}
	sstream << "]" << std::endl;
	std::cout << sstream.str();

*/

}
