#pragma once
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <math.h>
class GameWindow;
class GameMenu {
public:
	GameMenu()
		: Menu("menu.png") {};
	Gosu::Image Menu;
};