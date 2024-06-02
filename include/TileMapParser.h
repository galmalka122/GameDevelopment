#ifndef TileMapParser_h
#define TileMapParser_h

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <sstream>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "Tile.h"
#include "Utilities.h"
#include "Object.h"
#include "C_Sprite.h"
#include "WorkingDirectory.h"

using namespace rapidxml;

struct TileSheetData{

    int textureID;
    sf::Vector2i imageSize;
    int columns;
    int rows;
    sf::Vector2u tileSize;

};

using Layer = std::vector<std::shared_ptr<Tile>>;
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>;
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;
using TileSheets = std::map<int, std::shared_ptr<TileSheetData>>;


class TileMapParser {

public:

    TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator, WorkingDirectory& workingDirectory);

    std::vector<std::shared_ptr<Object>> Parse(const std::string& file, sf::Vector2i offset);

private:

    std::shared_ptr<TileSheets> BuildTileSheetData(xml_node<>* rootNode);
    std::shared_ptr<MapTiles> BuildMapTiles(xml_node<>* rootNode);
    std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheets> tileSheets);


    ResourceAllocator<sf::Texture>& textureAllocator;
    WorkingDirectory& workingDirectory;

};


#endif // TileMapParser_h
