#ifndef TILEDFILE_H
#define TILEDFILE_H

#include <string>
#include <map>
#include <vector>
#include <json/json.h>
struct TiledFile
{


    TiledFile():
        width(0),
        height(0),
        tileheight(0),
        tilewidth(0)
    {

    }
    void loadFromJsonString(const std::string & jsonString);

    unsigned int width;
    unsigned int height;
    unsigned int tileheight;
    unsigned int tilewidth;

    std::string orientation;
    unsigned int version;

    std::map<std::string, std::string> properties;

    struct Layer
    {
        Layer():
            name(""),
            width(0u),
            height(0u),
            opacity(0.0f),
            visible(true),
            x(0),
            y(0)
        {

        }
        std::string name;
        std::vector<unsigned int> data;

        unsigned int width;
        unsigned int height;

        float opacity;
        bool visible;

        int x;
        int y;

        bool operator == (const Layer &other)const;


    };

    std::vector<Layer> layers;

    struct TileSet
    {
        std::string name;
        unsigned int firstgrid;
        std::string image;
        unsigned int imageheight;
        unsigned int imagewidth;
        unsigned int margin;
        unsigned int spacing;
        unsigned int tilewidth;
        unsigned int tileheight;
        std::map<std::string, std::string> properties;

		bool operator == (const TileSet & other)const;

    };
    std::vector<TileSet> tilesets;


	bool operator == ( const TiledFile & other)const;

private:
    std::vector<TileSet> parseTileSets(const Json::Value & node)const;
    std::vector<Layer> parseLayers(const Json::Value & node)const;
    std::map<std::string, std::string> parseProperties(const Json::Value & node)const;

};

#endif // TILEDFILE_H
