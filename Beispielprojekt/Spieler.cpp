#include <math.h>
#include "Spieler.h"
#include <memory>
#include <stdlib.h>

//Konstruktor
Spieler::Spieler() 
{
	this->player_x = player_start_x;
	this->player_y = player_start_y;
	this->fallTime = 0;
	this->jumpTime = 0;
	this->playerTimeXA = 0;
	this->playerTimeXD = 0;
	this->playeraction = 0;
	this->speedPlayer = 0;
	this->speedPlayerY = 0;
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

void Spieler::KI() {
	KI_timer = (KI_timer == 0) ? KI_ACTION_LOOP_TIMER : KI_timer - 1;		//Danke Gabriel :)
	if (KI_timer < (KI_ACTION_LOOP_TIMER - GEGNER_MAX_JUMP_TIME) && this->playeraction == 3)
	{
		this->playeraction = 0;
	}
	if (KI_timer == 0)
	{
		int rd = rand() % 100;
		if (rd > 50)
		{
			this->playeraction = 0;		//nix
		}
		else if (rd <= 50 && rd > 30)
		{
			this->playeraction = 1;		//links
		}
		else if (rd <= 30 && rd > 10)
		{
			this->playeraction = 2;		//rechts
		}
		else if (rd <= 10 && rd >= 0)
		{
			this->playeraction = 3;		//hoch
		}
	}
	
}
