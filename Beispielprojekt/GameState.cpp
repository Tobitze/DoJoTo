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
	//Spieler* p1 = (Spieler*) malloc(sizeof(Spieler));
	p1 = new Spieler();
	//Spieler p1;
	//Spieler& p1ref = p1;

	ilistenproblenloeser = erstelle_Objekt_fest_ptr(0, 0, 0, 0, 0, nullptr, nullptr, 1, 1);					 //Einfach nicht hinterfragen
	ibodenR = erstelle_Objekt_fest_ptr(474, 58, 400, 550, 100, ilistenproblenloeser, std::make_shared<Gosu::Image>(bodenR),1 ,1);
	ibodenL = erstelle_Objekt_fest_ptr(474, 58, 0, 550, 100, ibodenR, std::make_shared<Gosu::Image>(bodenL), 1, 1);				 //Linked list über pointer
	iKiste = erstelle_Objekt_fest_ptr(168, 168, 730, 300, 100, ibodenL, std::make_shared<Gosu::Image>(Kiste), 1, 1);
	iPlattform1 = erstelle_Objekt_fest_ptr(1075, 233, 300, 200, 100, iKiste, std::make_shared<Gosu::Image>(Plattform1), 1, 1);
	iWand = erstelle_Objekt_fest_ptr(474, 58, 700, 500, 100, iPlattform1, std::make_shared<Gosu::Image>(Wand), 1, 1);

	elem_O_f = std::make_shared<Objekt_fest>();
	listenstart_O_f = iWand; //Hier immer letztes Element hinschreiben

	//Liste für Player
	ilistenproblenloeserplayer = erstelle_Player_data_ptr(0, 0, nullptr, nullptr, false, 1, 1);
	iplayertemp = erstelle_Player_data_ptr(53, 94, ilistenproblenloeserplayer, std::make_shared<Gosu::Image>(rPlayertemp1), true, 1, 1);

	elem_P_d = std::make_shared<Player_data>();
	listenstart_P_d = iplayertemp; //Hier immer letztes Element hinschreiben
	elem_P_d = listenstart_P_d;

};

Spieler* GameState::get_Spieler()
{
	return this->p1;
}

//std::shared_ptr<Spieler> GameState::get_Spieler()
//{
//	return std::make_shared<Spieler>(this->p1);
//}

//Spieler& GameState::get_Spieler()
//{
//	return this->p1;
//}

//std::shared_ptr<GameState::Objekt_fest> GameState::get_listenstart_O_f()
//{
//	return this->iWand;
//}
//
//std::shared_ptr<GameState::Player_data> GameState::get_listenstart_P_d()
//{
//	return this->listenstart_P_d;
//}

std::shared_ptr<GameState::Objekt_fest> GameState::erstelle_Objekt_fest_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<GameState::Objekt_fest> next, std::shared_ptr<Gosu::Image> image, double scale_x, double scale_y)
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
	return std::make_shared<GameState::Objekt_fest>(temp);
}
	
std::shared_ptr<GameState::Player_data> GameState::erstelle_Player_data_ptr(double breite, double hoehe, std::shared_ptr<GameState::Player_data> next, std::shared_ptr<Gosu::Image> image, bool active, double scale_x, double scale_y)
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
	return std::make_shared<GameState::Player_data>(temp);
}

	

	
	 
double distance_from_player(std::shared_ptr<GameState::Objekt_fest> o2, Spieler* p1)
{
	return sqrt(pow((p1->player_x - o2->startx), 2) + pow((p1->player_y - o2->starty), 2));
}
	bool GameState::kollision_rechts(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, std::shared_ptr<Spieler> p1)//std::shared_ptr<GameState::Objekt_fest> listenstart_O_f, Spieler p1, std::shared_ptr<GameState::Player_data> iplayertemp)
	{
		std::shared_ptr<GameState::Objekt_fest> elem_O_f = this->listenstart_O_f;
		//std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
		bool tmp = false;
		//auto elem_O_f = GameState::get_listenstart_O_f();   //listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != nullptr)
		{
			//if (distance_from_player(elem_O_f, p1) < 5000)
			//{
				if ((this->p1->player_x + iplayertemp->breite + 3 + this->p1->speedPlayer) > elem_O_f->startx && (this->p1->player_x) < (elem_O_f->startx + elem_O_f->breite) - 5)
				{
					if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			//}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
	bool GameState::kollision_links(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, Spieler* p1)
	{
		std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
		bool tmp = false;
		//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != nullptr)
		{
			//if (distance_from_player(elem_O_f, p1) < 5000)
			//{
				if ((this->p1->player_x - (3 + this->p1->speedPlayer)) < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) > (elem_O_f->startx + 5))
				{
					if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			//}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
	bool GameState::kollision_oben(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, Spieler* p1)
	{
		std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
		bool tmp = false;
		//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != nullptr)
		{
			//if (distance_from_player(elem_O_f, p1) < 5000)
			//{
				if (this->p1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) >(elem_O_f->startx))
				{
					if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y - (5 + abs(this->p1->speedPlayerY))) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			//}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
	bool GameState::kollision_unten(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, Spieler* p1)
	{
		std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
		bool tmp = false;
		//elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != nullptr)
		{
			//if (distance_from_player(elem_O_f, p1) < 5000)
			//{
				if (this->p1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) >(elem_O_f->startx))
				{
					if ((this->p1->player_y + iplayertemp->hoehe + 5 + abs(this->p1->speedPlayerY)) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			//}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}	
