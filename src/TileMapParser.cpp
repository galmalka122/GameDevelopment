#include <cstring>
#include "TileMapParser.h"

TileMapParser::TileMapParser(ResourceAllocator<sf::Texture> &textureAllocator, WorkingDirectory& workingDirectory) :
                    textureAllocator(textureAllocator), workingDirectory(workingDirectory) { }

std::vector<std::shared_ptr<Object>> TileMapParser::Parse(const std::string &file, sf::Vector2i offset) {

    char* fileLocation = new char[file.size() + 1];

#ifdef MACOS
    strlcpy(fileLocation, file.c_str(), file.size() + 1);
#else
    strcpy_s(fileLocation, file.size() + 1, file.c_str());
#endif

    rapidxml::file<> xmlFile(fileLocation);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<>* rootNode = doc.first_node("map");

    std::shared_ptr<MapTiles> map = BuildMapTiles(rootNode);

    int tileSizeX = std::stoi(rootNode->first_attribute("tilewidth")->value());
    int tileSizeY = std::stoi(rootNode->first_attribute("tileheight")->value());
    // int mapSizeX = std::stoi(rootNode->first_attribute("width")->value());
    // int mapSizeY = std::stoi(rootNode->first_attribute("height")->value());

    std::vector<std::shared_ptr<Object>> tileObjects;

    size_t layerCount = map->size() - 1;

    for(const auto& layer : *map){

        for(const auto& tile : layer.second->tiles){

            std::shared_ptr<TileInfo> tileInfo = tile->properties;

            std::shared_ptr<Object> tileObject = std::make_shared<Object>();

            const unsigned int tileScale = 3;

            if(layer.second->isVisible){
                auto sprite = tileObject->AddComponent<C_Sprite>();
                sprite->SetTextureAllocator(&textureAllocator);
                sprite->Load(tileInfo->textureID);
                sprite->SetTextureRect(tileInfo->textureRect);
                sprite->SetScale(tileScale, tileScale);
                sprite->SetOrder(layerCount);

                sprite->SetDrawLayer(DrawLayer::Background);
            }

            auto x = (float)(tile->x * tileSizeX * tileScale + offset.x);
            auto y = (float)(tile->y * tileSizeY * tileScale + offset.y);
            tileObject->transform->SetPosition(x, y);

            if(layer.first == "Collisions"){

                auto collider = tileObject->AddComponent<C_BoxCollider>();

                auto left = x - float(tileSizeX * tileScale) * 0.5f;
                auto top = y - float(tileSizeY * tileScale) * 0.5f;
                auto width = float(tileSizeX * tileScale);
                auto height = float(tileSizeY * tileScale);

                collider->SetCollidable(sf::FloatRect(left, top, width, height));
                collider->SetLayer(CollisionLayer::Tile);
            }

            tileObjects.emplace_back(tileObject);
        }

        layerCount--;
    }

    return tileObjects;
}

std::shared_ptr<TileSheets> TileMapParser::BuildTileSheetData(xml_node<> *rootNode) {

    TileSheets tileSheets;

    for(xml_node<>* tileSheetNode = rootNode->first_node("tileset"); tileSheetNode; tileSheetNode = tileSheetNode->next_sibling("tileset")){

        TileSheetData tileSheetData;

        int firstID = std::stoi(tileSheetNode->first_attribute("firstgid")->value());

        tileSheetData.tileSize.x = std::stoi(tileSheetNode->first_attribute("tilewidth")->value());
        tileSheetData.tileSize.y = std::stoi(tileSheetNode->first_attribute("tileheight")->value());
        int tileCount = std::stoi(tileSheetNode->first_attribute("tilecount")->value());
        tileSheetData.columns = std::stoi(tileSheetNode->first_attribute("columns")->value());
        tileSheetData.rows = tileCount / tileSheetData.columns;

        xml_node<>* imageNode = tileSheetNode->first_node("image");
        tileSheetData.textureID = textureAllocator.Add(
                workingDirectory.Get() + std::string(imageNode->first_attribute("source")->value()));

        tileSheetData.imageSize.x = std::stoi(imageNode->first_attribute("width")->value());
        tileSheetData.imageSize.y = std::stoi(imageNode->first_attribute("height")->value());

        tileSheets.insert(std::make_pair(firstID, std::make_shared<TileSheetData>(tileSheetData)));
    }

    return std::make_shared<TileSheets>(tileSheets);

}

std::shared_ptr<MapTiles> TileMapParser::BuildMapTiles(xml_node<> *rootNode) {

    std::shared_ptr<TileSheets> tileSheetData = BuildTileSheetData(rootNode);
    std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();

    for(xml_node<>* node = rootNode->last_node("layer"); node; node = node->previous_sibling("layer")){

        std::pair<std::string, std::shared_ptr<Layer>> mapLayer = BuildLayer(node, tileSheetData);
        map->emplace_back(mapLayer);
    }

    return map;

}

std::pair<std::string, std::shared_ptr<Layer>>
TileMapParser::BuildLayer(xml_node<> *layerNode, const std::shared_ptr<TileSheets>& tileSheets) {

    TileSet tileSet;
    std::shared_ptr<Layer> layer = std::make_shared<Layer>();

    int width = std::stoi(layerNode->first_attribute("width")->value());
    // int height = std::stoi(layerNode->first_attribute("height")->value());

    xml_node<>* dataNode = layerNode->first_node("data");
    char* mapIndices = dataNode->value();

    std::stringstream fileStream(mapIndices);

    int count = 0;

    std::string line;
    while (fileStream.good())
    {
        std::string substr;
        std::getline(fileStream, substr, ',');

        if (!Utilities::IsInteger(substr))
        {
            substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end());
            substr.erase(std::remove(substr.begin(), substr.end(), '\n'), substr.end());

            // add additional check to confirm that the character removals have worked:
            /*
            if(!Utilities::IsInteger(substr))
            {
                //String is still not integer.
            }
            */
        }

        int tileId = std::stoi(substr);

        if (tileId != 0)
        {
            auto itr = tileSet.find(tileId);
            if (itr == tileSet.end())
            {
                std::shared_ptr<TileSheetData> tileSheetData;
                int firstID = 0;

                for(auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter){

                    if(tileId >= iter->first){
                        firstID = iter->first;
                        tileSheetData = iter->second;
                        break;

                    }
                }

                if(!tileSheetData) // 3
                {
                    // Output error message.
                    continue;
                }

                int textureX = (tileId - firstID) % tileSheetData->columns;
                int textureY = (tileId - firstID) / tileSheetData->columns;

                if(textureX < 0) { std::cout << "here" << std::endl; }

                std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(
                        tileSheetData->textureID,
                        tileId,
                        sf::IntRect(
                                (int)(textureX * tileSheetData->tileSize.x),
                                (int)(textureY * tileSheetData->tileSize.y),
                                (int)tileSheetData->tileSize.x,
                                (int)tileSheetData->tileSize.y
                        )
                );

                itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
            }

            std::shared_ptr<Tile> tile = std::make_shared<Tile>();

            // Bind properties of a tile from a set.
            tile->properties = itr->second;
            tile->x = count % width - 1;
            tile->y = count / width;


            layer->tiles.emplace_back(tile);
        }

        count++;
    }

    const std::string layerName = layerNode->first_attribute("name")->value();
    bool layerVisibility = true;
    xml_attribute<>* visibilityAttribute = layerNode->first_attribute("visible");

    if(visibilityAttribute) {
        layerVisibility = std::stoi(visibilityAttribute->value());
    }
    layer->isVisible = layerVisibility;

    return std::make_pair(layerName, layer);
}
