#include <algorithm>
#include <fstream>

#include "rect.h"
#include "camera.h"

#include "tiledMap.h"

TiledMap::TiledMap()
{
}

TiledMap::TiledMap(const std::string& filePath)
{
	load(filePath);
}

void
TiledMap::load(const std::string& filePath)
{
	Json::Reader reader;
	std::fstream fd;

	/* Load entire data */
	fd.open(filePath, std::fstream::in);
	if (!fd.is_open()) {
		std::string errMsg = "[MapLoader] file not found: " + filePath;

		throw std::runtime_error(errMsg);
	}

	if (reader.parse(fd, mapData_) == false) {
		fd.close();
		throw std::runtime_error(reader.getFormattedErrorMessages());
	}

	/* Store map basic properties */
	mapWidth_ = mapData_["width"].asInt();
	mapHeight_ = mapData_["height"].asInt();
	tileWidth_ = mapData_["tilewidth"].asInt();
	tileHeight_ = mapData_["tileheight"].asInt();

	/* Dump each tile layer */
	if (mapData_["layers"].isNull())
		throw std::runtime_error("No object 'layers' in map file, "
					 "map file '" + filePath +
					 "' is broken");

	for (auto& layer : mapData_["layers"]) {
		if (layer["type"].asString() == "tilelayer") {
			tileLayers_.emplace_back(layer);

			if (!layer["properties"]["collidable"].isNull() &&
			    layer["properties"]["collidable"].asString() == "true") {
				collidableLayers_.emplace_back(layer);
			}


		} else if (layer["type"].asString() == "objectgroup") {
			objectLayers_.emplace_back(layer);

		} else {
			printf("[TiledMap] Unkonwn layer type: %s\n",
			       layer["type"].asCString());
		}
	}

	/* Dump tile sets */
	if (mapData_["tilesets"].isNull())
		throw std::runtime_error("No object 'tilesets' in map file, "
					 "map file '" + filePath +
					 "' is broken");

	for (auto& tileSet : mapData_["tilesets"])
		tileSets_.push_back(tileSet);

	/* "firstgid" order from large to small, 10 , 5 , 3, 2 */
	std::sort(tileSets_.begin(), tileSets_.end(),
		  [](const Json::Value& a, const Json::Value& b)
		  {
			  int gidA = a["firstgid"].asInt();
			  int gidB = b["firstgid"].asInt();

			  return gidA > gidB;
		  });

	/* Find out sprite sheet */
	for (auto& tileSet : tileSets_) {
		int tileRow, tileCol;
		Rect tileClip;
		std::string imageName;

		imageName = tileSet["image"].asString();

		tileRow =
			tileSet["imageheight"].asInt() /
			tileSet["tileheight"].asInt();
		tileCol =
			tileSet["imagewidth"].asInt() /
			tileSet["tilewidth"].asInt();

		/* Find sprite pos */
		for (int row = 0; row < tileRow; ++row) {
			for (int col = 0; col < tileCol; ++col) {
				tileClip.x = col * tileWidth_;
				tileClip.y = row * tileHeight_;
				tileClip.w = tileWidth_;
				tileClip.h = tileHeight_;

				tileSprites_[imageName].emplace_back(
					imageName, tileClip);
			}
		}
	}
}

void
TiledMap::update()
{
}

void
TiledMap::render(Camera& camera)
{
	int leftBorder = std::floor((float)camera.getLeft() /
				    (float)tileWidth_);
	int rightBorder = std::floor((float)camera.getRight() /
				     (float)tileWidth_);
	int topBorder = std::floor((float)camera.getTop() /
				   (float)tileHeight_);
	int bottomBorder = std::floor((float)camera.getBottom() /
				      (float)tileHeight_);

	for (auto& layer : tileLayers_) {
		for (int y = topBorder; y <= bottomBorder; ++y) {
			for (int x = leftBorder; x <= rightBorder; ++x) {
				int tileId, firstTileId;

				tileId = layer["data"][mapWidth_ * y + x].asInt();
				if (tileId == 0)
					continue;

				for (const auto& tileSet : tileSets_) {
					Rect tileDst;
					std::string imageName;

					firstTileId = tileSet["firstgid"].asInt();
					if (tileId < firstTileId)
						continue;

					imageName = tileSet["image"].asString();

					tileDst.x = x * tileWidth_ - camera.getLeft();
					tileDst.y = y * tileHeight_ - camera.getTop();
					tileDst.w = tileWidth_;
					tileDst.h = tileHeight_;

					tileSprites_[imageName][tileId - firstTileId].render(tileDst);

					break;
				}
			}
		}
	}
}

std::vector<Rect>
TiledMap::getCollideRects(Rect& target)
{
	std::vector<Rect> tilesToReturn;
	int leftBorder, rightBorder, topBorder, bottomBorder;

	leftBorder = std::floor(target.x / tileWidth_);
	rightBorder = std::ceil((target.x + target.w - 1) / tileWidth_);
	topBorder = std::floor(target.y / tileHeight_);
	bottomBorder = std::ceil((target.y + target.h - 1) / tileHeight_);

	for (auto& layer : collidableLayers_) {
		for (int row = topBorder; row <= bottomBorder; ++row) {
			for (int col = leftBorder; col <= rightBorder; ++col) {
				/* TODO
				 * Now return only solid tile, maybe not the
				 * best way
				 */
				if (layer["data"][row * mapWidth_ + col] == 0)
					continue;

				Rect tile;

				tile.w = tileWidth_;
				tile.h = tileHeight_;
				tile.x = tileWidth_ * col;
				tile.y = tileHeight_ * row;

				tilesToReturn.emplace_back(tile);
			}
		}
	}

	return tilesToReturn;
}

Rect
TiledMap::getObjectPos(const std::string& objName) const
{
	Rect rectToReturn;

	rectToReturn.x = 0;
	rectToReturn.y = 0;
	rectToReturn.w = 0;
	rectToReturn.h = 0;

	for (auto& layer : objectLayers_) {
		for (auto& object : layer["objects"]) {
			if (object["name"].asString() == objName) {
				rectToReturn.x = object["x"].asInt();
				rectToReturn.y = object["y"].asInt();
				rectToReturn.w = object["width"].asInt();
				rectToReturn.h = object["height"].asInt();

				break;
			}
		}
	}

	return rectToReturn;
}
