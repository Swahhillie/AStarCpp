#include "TiledFile.hpp"
#include "UnitTest++.h"
#include <assert.h>
#include <limits>
#include <cmath>
#include <algorithm>

void TiledFile::loadFromJsonString(const std::string & jsonString)
{
    Json::Value root;
    Json::Reader reader;
    if(reader.parse(jsonString, root))
    {
        assert(root.size() == 9u);

        width = root["width"].asUInt();
        height = root["height"].asUInt();

        tilewidth = root["tilewidth"].asUInt();
        tileheight = root["tileheight"].asUInt();

        orientation = root["orientation"].asString();
        version = root["version"].asUInt();
        properties = parseProperties(root["properties"]);
        layers = parseLayers(root["layers"]);
        tilesets = parseTileSets(root["tilesets"]);


    }
    else
    {
        std::cout << reader.getFormatedErrorMessages() << std::endl;
        std::cout << "Press any key to exit" << std::endl;
        std::string temp;
        std::cin >> temp;
        assert(1 == 2);
    }
}
std::vector<TiledFile::Layer> TiledFile::parseLayers(const Json::Value & node)
{

    assert(node.isArray());
    std::vector<TiledFile::Layer> layers;
    for(Json::Value lay : node)
    {

        layers.push_back(TiledFile::Layer());
        auto & newLayer = layers.back();
        Json::Value data = lay["data"];

        newLayer.data = std::vector<unsigned int>(data.size(), 0u);
        for(auto i = 0u; i < data.size(); i++)
        {
            newLayer.data[i] = data[i].asUInt();
        }

        newLayer.height = lay["height"].asUInt();
        newLayer.width = lay["width"].asUInt();
        newLayer.name = lay["name"].asString();
        newLayer.type = lay["type"].asString();
        newLayer.opacity = lay["opacity"].asFloat();
        newLayer.visible = lay["visible"].asBool();
        newLayer.x = lay["x"].asUInt();
        newLayer.y = lay["y"].asUInt();
        newLayer.properties = parseProperties(lay["properties"]);



    }
    return layers;
}
std::vector<TiledFile::TileSet> TiledFile::parseTileSets(const Json::Value & node)
{
    std::vector<TiledFile::TileSet> tilesets;
    assert(node.isArray());
    for(Json::Value lay : node)
    {
        tilesets.push_back(TiledFile::TileSet());
        TiledFile::TileSet & tileset = tilesets.back();

        tileset.firstgid = lay["firstgid"].asUInt();;
        tileset.image = lay["image"].asString();
        tileset.imageheight = lay["imageheight"].asUInt();
        tileset.imagewidth = lay["imagewidth"].asUInt();
        tileset.margin = lay["margin"].asUInt();
        tileset.name = lay["name"].asString();
        //tileset.properties
        tileset.spacing = lay["spacing"].asUInt();
        tileset.tileheight = lay["tileheight"].asUInt();
        tileset.tilewidth = lay["tilewidth"].asUInt();
        tileset.properties = parseProperties(lay["properties"]);

        Json::Value tilepropertiesNode = lay["tileproperties"];
        for(auto propName : tilepropertiesNode.getMemberNames())
        {
            unsigned int tileId = 0u;
            std::stringstream stream;
            stream << propName;
            stream >> tileId;
            tileset.tileproperties[tileId] = parseProperties(tilepropertiesNode[propName]);
        }


    }
    return tilesets;
}
TiledFile::Properties TiledFile::parseProperties(const Json::Value & node)
{
    Properties properties;
    for(auto propName : node.getMemberNames())
    {
        properties[propName] = node[propName].asString();
    }
    return properties;
}
bool TiledFile::operator==(const TiledFile & other)const
{
    //compare with self
    if(this == &other)return true;

    //not compare with self
    return (
               other.height == height &&
               other.width == width &&
               other.orientation == orientation &&
               other.tilewidth == tilewidth &&
               other.tileheight == tileheight &&
               other.layers == layers &&
               other.tilesets == tilesets &&
               other.properties == properties);
}
bool TiledFile::Layer::operator == (const TiledFile::Layer & other)const
{
    if(this == &other)return true;

    return(
              other.data == data &&
              other.width == width &&
              other.height == height &&
              other.name == name &&
              other.type == type &&
              other.x == x &&
              other.y == y &&
              other.properties == properties &&
              (std::fabs(other.opacity - opacity) < std::numeric_limits<float>::epsilon()));
}
bool TiledFile::TileSet::operator == (const TiledFile::TileSet & other)const
{
    if(this == &other)return true;

    return (
               other.firstgid == firstgid &&
               other.image == image &&
               other.imageheight == imageheight &&
               other.imagewidth == imagewidth &&
               other.margin == margin &&
               other.spacing == spacing &&
               other.tilewidth == tilewidth &&
               other.tileheight == tileheight &&
               other.properties == properties &&
               other.tileproperties == tileproperties
           );
}

TEST(comparisonOperatorTiledFile)
{
    //compare tiled files
    TiledFile a;
    TiledFile b;
    CHECK(a == b);

    //make different
    a.height = 1;

    CHECK(!(a == b));

    a = b;
    CHECK(a == b);
}
TEST(basicJson)
{
    const std::string testJson(R"({ "height":30,
                               "layers":[
                               {
                               "data":[30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30],
                               "height":30,
                               "name":"Tile Layer 1",
                               "opacity":1,
                               "type":"tilelayer",
                               "visible":true,
                               "width":30,
                               "x":0,
                               "y":0
                           }],
                               "orientation":"orthogonal",
                               "properties":
                               {

                           },
                               "tileheight":32,
                               "tilesets":[
                               {
                               "firstgid":1,
                               "image":"tmw_desert_spacing.png",
                               "imageheight":199,
                               "imagewidth":265,
                               "margin":1,
                               "name":"tmw_desert_spacing",
                               "properties":
                               {

                           },
                               "tileproperties":{
                               "9":
                               {
                               "traversable":"false"
                           }
                           },
                               "spacing":1,
                               "tileheight":32,
                               "tilewidth":32
                           }],
                               "tilewidth":32,
                               "version":1,
                               "width":30
                           })");

    TiledFile testComparison;

    testComparison.height = 30u;
    testComparison.width = 30u;
    testComparison.orientation = "orthogonal";
    testComparison.tileheight = 32u;
    testComparison.tilewidth =32u;
    testComparison.version = 1u;

    testComparison.layers.push_back(TiledFile::Layer());
    auto & layer = testComparison.layers.back();
    layer.data = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
    layer.width = 30u;
    layer.height = 30u;
    assert(layer.data.size() == layer.width * layer.height);
    layer.visible = true;
    layer.opacity = 1.0f;
    layer.x = 0;
    layer.y = 0;
    layer.name = "Tile Layer 1";
    layer.type = "tilelayer";


    testComparison.tilesets.push_back(TiledFile::TileSet());
    TiledFile::TileSet & tileset = testComparison.tilesets.back();
    tileset.firstgid = 1u;
    tileset.image = "tmw_desert_spacing.png";
    tileset.imageheight = 199u;
    tileset.imagewidth = 265u;
    tileset.margin = 1;
    tileset.name = "tmw_desert_spacing";
    //tileset.properties
    tileset.spacing = 1u;
    tileset.tileheight = 32u;
    tileset.tilewidth = 32u;
    tileset.tileproperties[9u]["traversable"] = "false";

    TiledFile testLoaded;
    testLoaded.loadFromJsonString(testJson);

    CHECK(testComparison == testLoaded);
}
