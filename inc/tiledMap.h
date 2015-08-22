#ifndef TILED_MAP_H
#define TILED_MAP_H

#include <string>
#include <list>
#include <map>
#include <json/json.h>

#include "texture.h"

#include "iGameObject.h"
#include "iCollidable.h"

class TiledMap : public IGameObject, public ICollidable
{
public:
	TiledMap();
	TiledMap(const std::string& filePath);

	void load(const std::string& filePath);

	virtual void update();
	virtual void render(Camera& camera);

	virtual std::vector<Rect> getCollideRects(Rect& target);

	int getPixelWidth() const { return tileWidth_ * mapWidth_; }
	int getPixelHeight() const { return tileHeight_ * mapHeight_; }

	Rect getObjectPos(const std::string& objName) const;
private:
	int mapWidth_, mapHeight_;
	int tileWidth_, tileHeight_;
	Json::Value mapData_;

	std::list<Json::Value> tileLayers_;
	std::list<Json::Value> objectLayers_;
	std::vector<Json::Value> tileSets_;
	std::map<std::string, std::vector<Texture>> tileSprites_;

	std::list<Json::Value> collidableLayers_;
};

#endif /* TILED_MAP_H */
