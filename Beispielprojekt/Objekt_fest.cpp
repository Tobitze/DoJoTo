#include "Objekt_fest.h"
#include <Gosu/Gosu.hpp>
#include <vector>
class Objekt_fest
{
	double breite, hoehe, posx, posy;
	//Gosu::Image bild;

public:
	Objekt_fest(double breite, double hoehe, double posx, double posy/*, Gosu::Image bild*/)
	{
		this->breite = breite;
		this->hoehe = hoehe;
		this->posx = posx;
		this->posy = posy;
		//this->bild = bild;
	}

	void move_x(double deltax)
	{
		this->posx = this->posx + deltax;
	}
	void move_y(double deltay)
	{
		this->posy = this->posy + deltay;
	}
};