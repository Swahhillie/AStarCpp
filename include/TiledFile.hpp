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

	typedef std::map<std::string, std::string> Properties;
	Properties properties;

    struct Layer
    {
        Layer():

            width(0u),
            height(0u),
            opacity(0.0f),
            visible(true),
            x(0),
            y(0)
        {

        }
        std::string name;
        std::string type;
        std::vector<unsigned int> data;
		Properties properties;

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
        unsigned int firstgid;
        std::string image;
        unsigned int imageheight;
        unsigned int imagewidth;
        unsigned int margin;
        unsigned int spacing;
        unsigned int tilewidth;
        unsigned int tileheight;
        Properties properties;
        std::map<unsigned int, Properties> tileproperties;

		bool operator == (const TileSet & other)const;

    };
    std::vector<TileSet> tilesets;


	bool operator == ( const TiledFile & other)const;

private:
    static std::vector<TileSet> parseTileSets(const Json::Value & node);
    static std::vector<Layer> parseLayers(const Json::Value & node);
    static Properties parseProperties(const Json::Value & node);

};

#endif // TILEDFILE_H
