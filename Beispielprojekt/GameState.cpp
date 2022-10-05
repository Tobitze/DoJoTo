#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include "Spieler.h"
#include <math.h>
#include "GameState.h"



GameState::GameState()
//Level Design
	: bodenR("boden1.jpg")
	, bodenL("boden1.jpg")
	, Wand("boden1.jpg")
	, hintergrund("hintergrund.jfif")
	, Kiste("Block.png")
	, Plattform1("Plattform1.png")
	//HUD
	, hudHP("hud_hp.png")
	, hudHP2("hud_hp-1.png")
	, hudHP1("hud_hp-2.png")
	, hudHP0("hud_hp-3.png")
	, GameOver("GameOver.png")
	//Player (temp)
	, rPlayertemp1("r-Dr.Salzig1.png")
	, rPlayertemp2("r-Dr.Salzig2.png")
	, rPlayertempA1("r-Dr.Salzig1-attack.png")
	, rPlayertempA2("r-Dr.Salzig2-attack.png")
	, lPlayertemp1("l-Dr.Salzig1.png")
	, lPlayertemp2("l-Dr.Salzig2.png")
	, lPlayertempA1("l-Dr.Salzig1-attack.png")
	, lPlayertempA2("l-Dr.Salzig2-attack.png")
{
	ilistenproblenloeser = erstelle_Objekt_fest(0, 0, 0, 0, 0, NULL, NULL);
	ibodenR = erstelle_Objekt_fest(474, 58, 400, 550, 100, &ilistenproblenloeser, &bodenR);
	ibodenL = erstelle_Objekt_fest(474, 58, 0, 550, 100, &ibodenR, &bodenL);				 //Linked list über pointer
	iKiste = erstelle_Objekt_fest(168, 168, 730, 300, 100, &ibodenL, &Kiste);
	iPlattform1 = erstelle_Objekt_fest(1075, 233, 300, 200, 100, &iKiste, &Plattform1);
	iWand = erstelle_Objekt_fest(474, 58, 700, 500, 100, &iPlattform1, &Wand);


	listenstart_O_f = &iWand; //Hier immer letztes Element hinschreiben

   //Liste für Player
	ilistenproblenloeserplayer = erstelle_Player_data(0, 0, NULL, NULL, false);
	iplayertemp = erstelle_Player_data(35, 94, &ilistenproblenloeserplayer, &rPlayertemp1, true);


	listenstart_P_d = &iplayertemp;
	p1 = new Spieler();
};

Spieler* GameState::get_Spieler()
{
	return this->p1;
}

GameState::Objekt_fest GameState::erstelle_Objekt_fest(double breite, double hoehe, double posx, double posy, double posz, GameState::Objekt_fest* next, Gosu::Image* image, double scale_x, double scale_y)
{
	GameState::Objekt_fest temp;
	//double breitetemp2 = (double)image->width();
	temp.breite = breite * scale_x;
	//temp.breite = breitetemp2;
	temp.hoehe = hoehe * scale_y;
	//temp.hoehe = (double)image->height();
	temp.posx = posx;
	temp.posy = posy;
	temp.startx = posx;
	temp.starty = posy;
	temp.posz = posz;
	temp.next = next;
	temp.image = image;
	temp.scale_x = scale_x;
	temp.scale_y = scale_y;
	return temp;
}
	
GameState::Player_data GameState::erstelle_Player_data(double breite, double hoehe, GameState::Player_data* next, Gosu::Image* image, bool active, double scale_x, double scale_y)
{
	GameState::Player_data temp;
	//double breitetemp2 = (double)image->width();
	temp.breite = breite * scale_x;
	//temp.breite = breitetemp2;
	temp.hoehe = hoehe * scale_y;
	//temp.hoehe = (double)image->height();
	temp.next = next;
	temp.image = image;
	temp.scale_x = scale_x;
	temp.scale_y = scale_y;
	temp.active = active;
	return temp;
}

	

	
	 
#pragma region 1 //Kollsionskäse
	double GameState::distance_from_player(GameState::Objekt_fest* o2)
	{
		return sqrt(pow((GameState::get_Spieler()->player_x - o2->startx), 2) + pow((GameState::get_Spieler()->player_y - o2->starty), 2));
	}
	bool GameState::kollision_rechts()
	{
		bool tmp = false;
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
			{
				if ((GameState::get_Spieler()->player_x + iplayertemp.breite + 3 + GameState::get_Spieler()->speedPlayer) > elem_O_f->startx && (GameState::get_Spieler()->player_x) < (elem_O_f->startx + elem_O_f->breite) - 5)
				{
					if ((GameState::get_Spieler()->player_y + iplayertemp.hoehe) > elem_O_f->starty && (GameState::get_Spieler()->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
	bool GameState::kollision_links()
	{
		bool tmp = false;
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
			{
				if ((GameState::get_Spieler()->player_x - (3 + GameState::get_Spieler()->speedPlayer)) < (elem_O_f->startx + elem_O_f->breite) && (GameState::get_Spieler()->player_x + iplayertemp.breite) > (elem_O_f->startx + 5))
				{
					if ((GameState::get_Spieler()->player_y + iplayertemp.hoehe) > elem_O_f->starty && (GameState::get_Spieler()->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
	bool GameState::kollision_oben()
	{
		bool tmp = false;
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
			{
				if (GameState::get_Spieler()->player_x < (elem_O_f->startx + elem_O_f->breite) && (GameState::get_Spieler()->player_x + iplayertemp.breite) >(elem_O_f->startx))
				{
					if ((GameState::get_Spieler()->player_y + iplayertemp.hoehe) > elem_O_f->starty && (GameState::get_Spieler()->player_y - 5) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
	bool GameState::kollision_unten()
	{
		bool tmp = false;
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
			{
				if (GameState::get_Spieler()->player_x < (elem_O_f->startx + elem_O_f->breite) && (GameState::get_Spieler()->player_x + iplayertemp.breite) >(elem_O_f->startx))
				{
					if ((GameState::get_Spieler()->player_y + iplayertemp.hoehe + 5) > elem_O_f->starty && (GameState::get_Spieler()->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
#pragma endregion	
