#include"InputManager.h"


bool InputManager::clicked = false;
bool InputManager::_down = false;
bool InputManager::_up = false;
bool InputManager::_left = false;
bool InputManager::_right = false;
bool InputManager::_escape = false;
Vector2T<float> InputManager::mousePos = { 0 , 0 };
bool * InputManager::_keys = new bool[256];