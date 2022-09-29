#pragma once
#include <cstdint>
#include <Gosu/Gosu.hpp>
class Objekte_fest
{
	//struct für objekt
	//Hier nur Deklarationen
public:

	int64_t breite, hoehe, posx, posy;
	Gosu::Image bild;

	Objekte_fest(int64_t breite, int64_t hoehe, int64_t posx, int64_t posy, Gosu::Image bild);

	void startup();

};

