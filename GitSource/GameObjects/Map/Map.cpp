#include"Map.h"


Map::Map()
{
	init();
}

Map::~Map()
{
	for (auto& i : _drawbles)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = 0;
	}
	_drawbles.clear();
}

void Map::init()
{
	/*
	* sunt incarcate obiectele de ce pot di desenabile
	*/
	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["ground"][i][j] != 0)
			{
				SpriteComponent* tile = new SpriteComponent(AssetsStorage::_tiles[AssetsStorage::_mapLayers["ground"][i][j] - 1]);
				tile->setCameraPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
				tile->setMapObjectStatus(true);
				_drawbles.push_back(tile);

				tile = nullptr;
			}
		}
	}

	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["decor"][i][j] != 0)
			{
				SpriteComponent* tile = new SpriteComponent(AssetsStorage::_tiles[AssetsStorage::_mapLayers["decor"][i][j] - 1]);
				tile->setCameraPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
				tile->setMapObjectStatus(true);
				_drawbles.push_back(tile);
				tile = nullptr;
			}
		}
	}


	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["colidble"][i][j] != 0)
			{
				/*
				*  trebuie indetificat tipul obiectului colidble
				*  in functie de tipul obiectului comportamentul este diferit
				*/

				if (AssetsStorage::_mapLayers["colidble"][i][j] == AssetsStorage::_barrelId)
				{
					Barrel* barrel = new Barrel(AssetsStorage::_tiles[AssetsStorage::_mapLayers["colidble"][i][j] - 1], Vector2T<int>(j, i));
					barrel->setCameraPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
					barrel->setMapObjectStatus(true);
					if (i == 0 || j == 0 || i == AssetsStorage::_layerHeight - 1 || j == AssetsStorage::_layerWidth - 1)
					{
						barrel->_isBorder = true;
					}
					_drawbles.push_back(barrel);
					barrel = nullptr;
				}
				else
				{
					MapDestructibleObject* object = new MapDestructibleObject(AssetsStorage::_tiles[AssetsStorage::_mapLayers["colidble"][i][j] - 1], Vector2T<int>(j, i));
					object->setCameraPosition(Vector2T<int>(j * AssetsStorage::_tileDim, i * AssetsStorage::_tileDim));
					object->setMapObjectStatus(true);
					if (i == 0 || j == 0 || i == AssetsStorage::_layerHeight - 1 || j == AssetsStorage::_layerWidth - 1)
					{
						object->_isBorder = true;
					}
					_drawbles.push_back(object);
					object = nullptr;
				}

			}

		}
	}
}

void Map::draw()
{
	for (auto& i : _drawbles)
	{
		i->draw();
	}
}

void Map::update()
{
	for (auto& i : _drawbles)
	{
		i->update();
	}
}

MiniMap::MiniMap()
{
	init();
}

MiniMap::~MiniMap()
{
	for (auto& i : _drawbles)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = nullptr;
	}
	for (auto& i : _movebles)
	{
		i->setSrcTextNullPtr();
		delete i;
		i = nullptr;
	}
	_movebles.clear();
}

void MiniMap::init()
{
	SpriteComponent* tile = new SpriteComponent(AssetsStorage::_miniMapTiles["gray"]);
	tile->setScaleDimension(_scaleDim * AssetsStorage::_layerWidth, _scaleDim * AssetsStorage::_layerHeight);
	tile->setOpacity(128);
	_drawbles.push_back(tile);
	tile = nullptr;

	for (int i = 0; i < AssetsStorage::_layerHeight; i++)
	{
		for (int j = 0; j < AssetsStorage::_layerWidth; j++)
		{
			if (AssetsStorage::_mapLayers["colidble"][i][j] != 0)
			{
				SpriteComponent* object = new SpriteComponent(AssetsStorage::_miniMapTiles["blackGray"]);
				object->setCameraPosition(Vector2T<int>(j * _scaleDim, i * _scaleDim));
				object->setScaleDimension(_scaleDim, _scaleDim);
				object->setOpacity(128);
				object->setBorder(true);
				_drawbles.push_back(object);
			}
		}
	}

	for (auto& i : Mediator::getTanksPositions())
	{
		SpriteComponent* sprite = new SpriteComponent(AssetsStorage::_miniMapTiles[Mediator::getColorTeam(i.first)]);
		sprite->setCameraPosition(i.second / AssetsStorage::_tileDim * _scaleDim);
		sprite->setScaleDimension(2 * _scaleDim, 2 * _scaleDim);
		sprite->_id = i.first;
		sprite->setBorder(true);
		_movebles.push_back(sprite);
	}
}
void MiniMap::draw()
{
	for (auto& i : _drawbles)
	{
		i->draw();
	}
	for (auto& i : _movebles)
	{
		i->draw();
	}
}

void MiniMap::update()
{
	for (int i = 0; i < _drawbles.size(); i++)
	{
		if (Mediator::stillExist(Mediator::getId({ _drawbles[i]->getPosition() / _scaleDim })))
		{
			_drawbles[i]->enable();
		}
		else
		{
			_drawbles[i]->disable();
		}
	}

	for (int i = 0; i < _movebles.size(); i++)
	{
		if (Mediator::stillExist(_movebles[i]->_id))
		{
			_movebles[i]->enable();
			_movebles[i]->setCameraPosition(Mediator::getPosition(_movebles[i]->_id) / AssetsStorage::_tileDim * _scaleDim);
		}
		else
		{
			_movebles[i]->disable();
		}
	} 

}

