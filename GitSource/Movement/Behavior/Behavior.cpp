#include "Behavior.h"

void Behavior::move(Vector2T<int>& position, Vector2T<float> velocity)
{
	if (CameraManager::getFocusId() != _id)
	{
		_offset = CameraManager::offset;
	}

	Vector2T<float> direction(0, 0);

	//adaug _mapTileDim deoarece vreau punctul de mijloc 
	Vector2T<float> potentialPos = { (float)(position._x + AssetsStorage::_tileDim),
									(float)(position._y + AssetsStorage::_tileDim) };

	if (_moves._up)
	{
		direction.setY(-1);
		potentialPos._y += 1;
	}
	if (_moves._down)
	{
		direction.setY(1);
	}
	if (_moves._right)
	{
		direction.setX(1);
	}
	if (_moves._left)
	{
		direction.setX(-1);
		potentialPos._x += 1;
	}	//am adaugat 1 la stanga si sus deoarece apar erori de truchiere

	// normalizam viteza pe diagonala
	if (abs(direction._x) != 0 && abs(direction._y) != 0)
	{
		velocity *= sqrt(velocity._x + velocity._x);
	}

	// calculam pozitia viitorae
	potentialPos += velocity * direction * TimeManager::getDeltaTime();

	//verificam coliziunile cu celelalte tank-uri
	int rectDim = 2 * AssetsStorage::_tileDim;
	for (auto& i : Mediator::recieveTanksPositions(_id))
	{
		CollisionManager::circleRectagleCollision(potentialPos, i, rectDim);
	}
	
	CollisionManager::mapCollision(potentialPos);

	position._x = static_cast <int>(potentialPos._x) - AssetsStorage::_tileDim;
	position._y = static_cast <int>(potentialPos._y) - AssetsStorage::_tileDim;

	//notificam mediator-ul 
	Mediator::registerTank(position, _id);
}

void Behavior::rotationB(float& _angle, float& _angle1)
{
	bool oneKeyPressed = true;
	//directie individuala
	if (_moves._up && !_moves._right && !_moves._left && _angle != 0)
	{

		if ((_angle >= 0 && _angle <= 180) || _angle < -180)
		{
			_angle -= 5;
		}
		else if ((_angle <= 0 && _angle >= -180) || _angle > 180)
		{
			_angle += 5;
		}

	}
	if (_moves._right && !_moves._up && !_moves._down && _angle != 90)
	{
		if (_angle <= -180 || (_angle <= 180 && _angle >= 90) || _angle <= -90)
		{
			_angle -= 5;
		}
		else if (_angle >= 0 || (_angle > -90))
		{
			_angle += 5;
		}
	}
	if (_moves._left && !_moves._up && !_moves._down && _angle != -90)
	{
		if (_angle >= 180 || (_angle >= -180 && _angle <= -90) || _angle >= 90)
		{
			_angle += 5;
		}
		else if (_angle <= 0 || (_angle < 90))
		{
			_angle -= 5;
		}
	}
	if (_moves._down && !_moves._right && !_moves._left && (_angle != 180 && _angle != -180))
	{
		if (_angle >= 90 || (_angle >= 0 && _angle < 90))
		{
			_angle += 5;
		}
		else if (_angle <= 0)
		{
			_angle -= 5;
		}
	}

	//directie comuna

	if (_moves._up && _moves._left && _angle != -45 && _angle != 360 - 45)
	{
		oneKeyPressed = false;
		if ((_angle >= 180 && _angle >= 45) || (_angle <= 0 && _angle <= -45))
		{
			_angle += 5;
		}
		else
		{
			_angle -= 5;
		}

	}
	else if (_moves._up && _moves._right && _angle != 45 && _angle != 45 - 360)
	{
		oneKeyPressed = false;
		if (_angle > -180 && _angle > 180 || (_angle >= 0 && _angle <= 45))
		{
			_angle += 5;
		}
		else
		{
			_angle -= 5;
		}

	}

	if (_moves._down && _moves._left && _angle != -135 && _angle != 360 - 135)
	{
		oneKeyPressed = false;
		if (_angle <= 0 && _angle >= -135)
		{
			_angle -= 5;
		}
		else
		{
			_angle += 5;
		}
	}
	else if (_moves._down && _moves._right && _angle != 135 && _angle != 135 - 360)
	{
		if (_angle >= 0 && _angle <= 135)
		{
			_angle += 5;
		}
		else
		{
			_angle -= 5;
		}
	}

	//translari
	if (oneKeyPressed)
	{
		if (_angle == -270)
		{
			_angle = 90;
		}
		if (_angle == 270)
		{
			_angle = -90;
		}
	}

	if (_angle == 360 - 45)
	{
		_angle = -45;
	}

	if (!oneKeyPressed)
	{
		if (_moves._up)
		{
			if (_angle == 45 - 360)
			{
				_angle = 45;
			}
			if (_angle == -45)
			{
				_angle = 360 - 45;
			}
		}
	}

	if (_angle >= 360 || _angle <= -360)
	{
		_angle = 0;
	}

	_angle1 = _angle;
}

void Behavior::rotationC(Vector2T<int>& position, float& angle)
{
	double posY = static_cast<double>(_target._y) + static_cast<double>(_offset._y)
		- (static_cast<double>(position._y) + static_cast<double>(AssetsStorage::_rotCenter->y));

	double posX = static_cast<double>(_target._x) + static_cast<double>(_offset._x)
		- (static_cast<double>(position._x) + static_cast<double>(AssetsStorage::_rotCenter->x));

	angle = (SDL_atan2(posY, posX) * 180 / M_PI) + 90;
}
