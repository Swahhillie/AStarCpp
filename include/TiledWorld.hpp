#ifndef TILEDWORLD_HPP
#define TILEDWORLD_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <json/json.h>
#include <map>
#include "TiledFile.hpp"



class TiledWorld : public GameObject
{
public:
    TiledWorld(const std::string & name);
    virtual ~TiledWorld();


    void loadTiledMap();


	sf::VertexArray & getQuads(){return quads_;}
	TiledFile & getTiledFile(){return tiledFile_;}

protected:

    virtual void draw(sf::RenderTarget & target, sf::RenderStates states)const;
private:


    void generateWorld(int columns, int rows, const sf::Vector2f & tileSize);

    sf::VertexArray quads_;
    sf::Texture worldSprite_;



    TiledFile tiledFile_;


};

#endif // TILEDWORLD_HPP
