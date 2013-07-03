#include "TileManager.hpp"
#include <vector>
#include <sstream>
#include "Tile.hpp"
#include <iostream>
#include "Scene.hpp"
#include "TileGraphic.hpp"
#include "Controller.hpp"
#include "UnitTest++.h"
#include <assert.h>
#include "Pathfinder.hpp"
#include "Random.hpp"

TileManager::TileManager():
    columns_(30),
    rows_(20),
    tileHolder_(nullptr),
    tiledWorld_(nullptr)
{
    //ctor
	tileSize_ = sf::Vector2f(30.0f, 30.0f);
    tileHolder_ = Scene::instance().createGameObject<GameObject>("TileHolder");

    tileHolder_->setPosition(sf::Vector2f(50.0f, 50.0f));
    generateTiles(columns_, rows_);

    tiledWorld_ = Scene::instance().createGameObject<TiledWorld>(columns_, rows_, tileSize_);

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

void TileManager::generateTiles(int columns, int rows)
{

	//cleanup the existing tiles
	forEachTile([](Tile & tile){ delete &tile; });
	for(auto * go : tileHolder_->getChildren())
	{
		GameObject::destroy(go);
	}
	tiles_.clear();

	//assign the new width and height of the tiles
	columns_ = columns;
	rows_ = rows;

    tiles_.resize(columns_);

    for(auto i = 0; i < columns_; i++)
    {
        tiles_[i].resize(rows_);
    }



    Scene & scene = Scene::instance();

    for(auto i = 0; i < columns_; i++)
    {
        for(auto j = 0; j < rows_; j++)
        {
            auto * go = scene.createGameObject<TileGraphic>("Tile");
            go->setParent(tileHolder_);
            tiles_[i][j] = new Tile(i, j, go);
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
void TileManager::cleanMap()
{
	forEachTile([](Tile & tile){tile.setTraversable(true);});
}
void TileManager::generateWalls(float percentage)
{
	forEachTile([](Tile & tile){tile.setTraversable(Random::inRange(0.f, 100.0f) > 0);});
}
void TileManager::update()
{
    static Tile * clicked = nullptr;

    //the mouse in the window.
    sf::Vector2i mousePos = Controller::mousePosition;
    //transform the mouse position in to tile space
    sf::Vector2f transformedPosition = tileHolder_->getTransform().getInverse().transformPoint(mousePos.x, mousePos.y);

    sf::Vector2i coordinates = sf::Vector2i(transformedPosition.x / getTileSize().x, transformedPosition.y / getTileSize().y);

    if(coordinatesAreIn(coordinates))
    {
    	//the tile that the mouse is currently hovering over
        Tile * hoverTile = getTile(coordinates);
        assert(hoverTile != nullptr);
        if(Controller::getButton(sf::Mouse::Button::Right))
        {
            for(auto * tile : hoverTile->getAllNeighbours())
            {
                tile->setColor(sf::Color::Red);
                tile->setText("");
                coloredTiles_.push_back(tile);
            }
        }

        if(Controller::getButton(sf::Mouse::Button::Middle))
		{
			if(Controller::getKey(sf::Keyboard::Key::LShift))hoverTile->setTraversable(true);
			else hoverTile->setTraversable(false);
			hoverTile->recolor();
		}


        if(Controller::getButtonDown(sf::Mouse::Button::Left))
        {
            clicked = getTile(coordinates);
        }
        else if(Controller::getButtonUp(sf::Mouse::Button::Left) && clicked != nullptr)
        {
            TileManager::instance().forEachTile([](Tile & tile)
            {
                tile.g_ = 0;
                tile.h_ = 0;
                tile.f_ = 0;
                tile.recolor();
                tile.setText("");
            });

            path_ = Pathfinder::instance().getPath(clicked, hoverTile);
            clicked = nullptr;



         //   auto steps = path.size();

            TileManager::instance().forEachTile([&](Tile & tile)
            {
                std::stringstream sstream;
				if(tile.f_ > 0)
				{
					sstream << tile.g_ << "\n" << tile.h_ << "\n" << tile.f_;
					tile.setText(sstream.str());
				}

                //tile.setColor(sf::Color(r, g, b));
            }
                                               );

            for(auto * pn : path_)
            {
                auto * tile = static_cast<Tile*>(pn);

				tile->setColor(sf::Color::Yellow);
                //coloredTiles_.push_back(tile);
            }

        }
    }

}
void TileManager::draw(sf::RenderWindow & window)
{
	sf::Vertex points[path_.size()];
	int i = 0;
	for(auto * pn : path_){
		sf::Vertex v = sf::Vector2f(pn->getCoordinates());

		v.position *= TileManager::getTileSize().x;
		v.color = sf::Color::Cyan;

		v.position += sf::Vector2f(TileManager::getTileSize() /2.0f);
		v.position = tileHolder_->getTransform() * v.position;

		points[i] = v;
		i++;

	}


	window.draw(points, path_.size(), sf::LinesStrip );
}
void TileManager::postRender()
{
    for(auto * tile : coloredTiles_)
    {
        tile->recolor();
    }
    coloredTiles_.clear();
}
sf::Vector2f TileManager::tileSize_;

//check if the top left node has 2 neighbours
TEST(testPathnodeNeighbourCount)
{

    //create the tiles
    TileManager & tileManager = TileManager::instance();

    //tiles array must be at least 2 by 2, otherwise there would be a missing neighbour
    assert(tileManager.getColumns() > 1 && tileManager.getRows() > 1);

    auto & tiles = tileManager.getTiles();
    auto & tile0 = *(tiles[0][0]);

    CHECK_EQUAL(tile0.getDirectNeighbours().size(), 2U);
}

TEST(testPathnodeNeighbourIsActual)
{
    TileManager & tileManager = TileManager::instance();

    assert(tileManager.getColumns() > 1 && tileManager.getRows() > 1);

    auto & tiles = tileManager.getTiles();
    auto * tile0 = tiles[0][0];

    auto * neighbourRight = tiles[1][0];
    auto * neighbourDown = tiles[0][1];

    auto neighbours = tile0->getDirectNeighbours();

    assert(neighbours.size() == 2u);

    CHECK(neighbours[0] == neighbourRight);
    CHECK(neighbours[1] == neighbourDown);
    //CHECK_ARRAY_EQUAL(tile0actualNeighbours, tile0expectedNeighbours);

}
TEST(xyAlwaysTheSameAsCoordinates)
{
    //check if the coordinates get properly matched up

    TileManager & tileManager = TileManager::instance();

    for( auto & column : tileManager.getTiles())
    {
        for(auto i = 0u; i < column.size(); i++)
        {
            auto & tile = *column[i];
            CHECK(sf::Vector2i(tile.x_, tile.y_) == tile.getCoordinates());
        }
    }
}

TEST(forEachTileHitsAllTiles)
{
    //walk over all neighbours  and check if the neighbours are valid positions

    TileManager & tileManager = TileManager::instance();
    auto tileCount = 0;
    tileManager.forEachTile([&](Tile & tile)
    {
        tileCount++;
    });

    CHECK_EQUAL(tileCount, tileManager.getColumns() * tileManager.getRows());

}
TEST(accessAllTiles)
{
    TileManager & tileManager = TileManager::instance();

    tileManager.forEachTile([](Tile & tile)
    {
        tile.setColor(sf::Color::Yellow);
    });
    tileManager.forEachTile([](Tile & tile)
    {
        tile.setColor(sf::Color::White);
    });
}


TEST(regenerateTiles)
{
	TileManager & tileManager = TileManager::instance();

	//store current values
	auto c = tileManager.getColumns();
	auto r = tileManager.getRows();

	//regenerate tiles with specific size

	auto newColumns = 25;
	auto newRows = 50;

	tileManager.generateTiles(newColumns, newRows);

	//check dimensions
	CHECK(tileManager.getColumns() == newColumns && tileManager.getRows() == newRows);

	//check tile count and validity
	auto count = 0;
	tileManager.forEachTile([&](Tile & tile){count ++;});
	CHECK(count == newColumns * newRows);

	//restore original
	tileManager.generateTiles(c, r);
	CHECK(tileManager.getColumns() == c && tileManager.getRows() == r);



}
