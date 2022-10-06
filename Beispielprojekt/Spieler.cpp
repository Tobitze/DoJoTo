#include <math.h>
#include "Spieler.h"
#include <memory>

//Konstruktor
Spieler::Spieler() 
{
	this->player_x = 300;			//Später wieder anpassen in Spieler::player_start_x oder nur player_start_x
	this->player_y = 456; //Spieler::player_start_y;
	this->fallTime = 0;
	this->jumpTime = 0;
	this->playerTimeXA = 0;
	this->playerTimeXD = 0;
}

// Beschleunigung in x-Richtung 
double Spieler::PlayerBeschleunigung(double bx, double tx) {
	double ax;
	ax = bx * (tx / 5);
	return ax;
	//std::cout << ax << std::endl;
};

// Sprung in y richtung
double Spieler::PlayerSprung(int t, const double MAX_H, double v, bool p) {
	const double g = 9.81;
	double yt = t * v;
	double gt = -g * 0.1 * t;

	if ((yt < MAX_H) && (p = true)) {
		return yt;
	}
	else if ((yt >= MAX_H) && (p = true)) {
		return gt;
	}
	else if ((yt < MAX_H) && (p = false)) {
		return gt;
	}
	else if ((yt >= MAX_H) && (p = false)) {
		return gt;
	}
	else {			//kann später wieder weg falls alles geht
		return 1;
	}
};

void Spieler::reset()
{
	this->player_x = this->player_start_x;
	this->player_y = this->player_start_y;
	this->speedPlayer = 0;
	this->speedPlayerY = 0;
}
