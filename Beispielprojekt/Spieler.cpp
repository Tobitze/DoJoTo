#include <math.h>
#include "Spieler.h"

//Konstruktor
Spieler::Spieler() {
	this->player_x = player_start_x;
	this->player_y = player_start_y;
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

};
