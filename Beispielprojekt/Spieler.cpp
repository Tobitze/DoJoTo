#include <math.h>
#include "Spieler.h"
#include <memory>

//Konstruktor
Spieler::Spieler() 
{
	this->player_x = player_start_x;
	this->player_y = player_start_y;
	this->fallTime = 0;
	this->jumpTime = 0;
	this->playerTimeXA = 0;
	this->playerTimeXD = 0;
}

// Beschleunigung in x-Richtung 
double Spieler::PlayerBeschleunigung(const double bx, double tx) {
	return bx * (tx / 5);
	//std::cout << ax << std::endl;
};

// Sprung in y richtung
double Spieler::PlayerSprung(int t, const double MAX_H, double v, bool p) {		//noch in verwendung?
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
};

void Spieler::reset()
{
	this->player_x = this->player_start_x;
	this->player_y = this->player_start_y;
	this->speedPlayer = 0;
	this->speedPlayerY = 0;
}
