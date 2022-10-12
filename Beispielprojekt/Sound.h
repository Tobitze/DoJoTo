#pragma once
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

class Sound
{	
public:

	Sound(); //Konstruktor
	Gosu::Channel Hintergrund;
	Gosu::Channel Sprung;
	Gosu::Channel Gewonnen;
	Gosu::Channel Verloren;
	Gosu::Channel Tür;
	Gosu::Channel Schaden;
	Gosu::Channel Wand;
	Gosu::Channel SchadenGegner;
	Gosu::Channel Laser;
};