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
	, Wand_r1("Wand rechts.png")
	, Wand_l1("Wand links.png")
	, hintergrund("hintergrund.jfif")
	, Kiste("Block.png")
	, Plattform1("Plattform1.png")
	, Plattform2("Plattform1.png")
	//HUD
	, hudHP("hud_hp.png")
	, hudHP2("hud_hp-1.png")
	, hudHP1("hud_hp-2.png")
	, hudHP0("hud_hp-3.png")
	, Scroll("Scroll.png")
	, Scroll2("Scroll2.png")
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
	, Laserbild("Laser.png")
	// Gegener
	, MisterCoco("Mister Coco.png")
	
	//Sounds
	, HintergrundSound("Hintergrund.mp3")
	, SprungSound("Sprung.mp3")
	, GewonnenSound("Gewonnen.mp3")
	, VerlorenSound("Verloren.mp3")
	, TuerSound("Tuer.mp3")
	, SchadenSound("Schaden.mp3")
	, WandSound("Wand.mp3")
	, SchadenGegnerSound("Gegner_Schaden.mp3")
	, LaserSound("Laser.mp3")

{

	p1 = new Spieler();
	g1 = new Spieler();

	ilistenproblenloeser = erstelle_Objekt_fest_ptr(0, 0, 0, 0, 0, nullptr, nullptr, 1, 1);					 //Einfach nicht hinterfragen
	ibodenR = erstelle_Objekt_fest_ptr(474, 58, 476, 550, 100, ilistenproblenloeser, std::make_shared<Gosu::Image>(bodenR),1 ,1);
	ibodenL = erstelle_Objekt_fest_ptr(474, 58, 0, 550, 100, ibodenR, std::make_shared<Gosu::Image>(bodenL), 1, 1);				 //Linked list über pointer
	iKiste = erstelle_Objekt_fest_ptr(80, 80, 700, 469, 100, ibodenL, std::make_shared<Gosu::Image>(Kiste), 1, 1);
	iPlattform1 = erstelle_Objekt_fest_ptr(200, 43, 300, 200, 100, iKiste, std::make_shared<Gosu::Image>(Plattform1), 1, 1);
	iPlattform2 = erstelle_Objekt_fest_ptr(200, 43, 700, 10, 100, iPlattform1, std::make_shared<Gosu::Image>(Plattform2), 1, 1);
	iWand_r1 = erstelle_Objekt_fest_ptr(58, 473, 890, 90, 100, iPlattform2, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	iWand_r2 = erstelle_Objekt_fest_ptr(58, 473, 890, -383, 150, iWand_r1, std::make_shared<Gosu::Image>(Wand_r1), 1, 1);
	iWand_l1 = erstelle_Objekt_fest_ptr(58, 473, 0, 90, 100, iWand_r2, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	iWand_l2 = erstelle_Objekt_fest_ptr(58, 473, 0, 0, 100, iWand_l1, std::make_shared<Gosu::Image>(Wand_l1), 1, 1);
	iBoden3 = erstelle_Objekt_fest_ptr(474, 58, 0, -30, 100, iWand_l2, std::make_shared<Gosu::Image>(bodenR), 1, 1);
	iBoden4 = erstelle_Objekt_fest_ptr(474, 58, -474, -30, 100, iBoden3, std::make_shared<Gosu::Image>(bodenR), 1, 1);

	elem_O_f = std::make_shared<Objekt_fest>();
	listenstart_O_f = iBoden4; //Hier immer letztes Element hinschreiben

	//Liste für Player
	ilistenproblenloeserplayer = erstelle_Player_data_ptr(0, 0, nullptr, nullptr, false, 1, 1);
	iplayertempr1 = erstelle_Player_data_ptr(35, 94, ilistenproblenloeserplayer, std::make_shared<Gosu::Image>(rPlayertemp1), true, 1, 1);
	iplayertempr2 = erstelle_Player_data_ptr(35, 94, iplayertempr1, std::make_shared<Gosu::Image>(rPlayertemp2), false, 1, 1);
	iplayertempl1 = erstelle_Player_data_ptr(35, 94, iplayertempr2, std::make_shared<Gosu::Image>(lPlayertemp1), false, 1, 1);
	iplayertempl2 = erstelle_Player_data_ptr(35, 94, iplayertempl1, std::make_shared<Gosu::Image>(lPlayertemp2), false, 1, 1);
	iplayertempl1A = erstelle_Player_data_ptr(35, 94, iplayertempl2, std::make_shared<Gosu::Image>(lPlayertempA1), false, 1, 1);
	iplayertempl2A = erstelle_Player_data_ptr(35, 94, iplayertempl1A, std::make_shared<Gosu::Image>(lPlayertempA2), false, 1, 1);
	iplayertempr1A = erstelle_Player_data_ptr(35, 94, iplayertempl2A, std::make_shared<Gosu::Image>(rPlayertempA1), false, 1, 1);
	iplayertempr2A = erstelle_Player_data_ptr(35, 94, iplayertempr1A, std::make_shared<Gosu::Image>(rPlayertempA2), false, 1, 1);

	elem_P_d = std::make_shared<Player_data>();
	listenstart_P_d = iplayertempr2A; //Hier immer letztes Element hinschreiben
	elem_P_d = listenstart_P_d;

	//Liste für Objekt_damage

	ilistenproblemloeserobjektdamage = erstelle_Objekt_damage_ptr(0, 0, 0, 0, 0, nullptr, nullptr, 1, 1);	//Never touch a working system
	ikisteschaden = erstelle_Objekt_damage_ptr(80, 80, 90, 450, 100, ilistenproblemloeserobjektdamage, std::make_shared<Gosu::Image>(MisterCoco), 1, 1);
	//Hier neue einfügen

	elem_O_d = std::make_shared<Objekt_damage>();
	listenstart_O_d = ikisteschaden; //Hier immer letztes Element hinschreiben



};

void GameState::Rolle() //entrollen der schriftrolle
{
	
	if (i > (i/2)) {
		Scroll.draw_rot(400, 174, 150.0, 0.0, 0.5, 0.5);
		i = i - 1;
	}
	else if (i <= (i / 3) && i > 2*i/3)
	{
		Scroll2.draw_rot(400, 243, 150.0, 0.0, 0.5, 0.5);
	}
	else if (i <= (2*i / 3) && i > 0)
	{
		Scroll3.draw_rot(400, 291, 150.0, 0.0, 0.5, 0.5);
	}
	else if (i ==0)
	{
		GameOver.draw_rot(400, 300, 150.0, 0.0, 0.5, 0.5); }

}

void GameState::SpielerModelupdate() 
	{ 
	elem_P_d = listenstart_P_d;
	while (elem_P_d->next != nullptr)	//Alle Grafiken deaktivieren
	{
		elem_P_d->active = false;
		elem_P_d = elem_P_d->next;
	}
	t = (t == 0) ? IMAGE_CYCLE_TIME : t - 1;	//Danke Gabriel :D
	if (attack)
	{
		if (facing_l && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl1A->active = true;
		}
		else if (facing_l && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl2A->active = true;
		}
		else if (facing_r && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr1A->active = true;
		}
		else if (facing_r && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr2A->active = true;
		}
	}
	else {
		if (facing_l && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl1->active = true;
		}
		else if (facing_l && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempl2->active = true;
		}
		else if (facing_r && t < (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr1->active = true;
		}
		else if (facing_r && t >= (IMAGE_CYCLE_TIME / 2))
		{
			iplayertempr2->active = true;
		}
	}
}

std::vector<GameState::Laser> GameState::getLaserVektor()
{
	return this->Laservektor;
}
void GameState::Lasershooter()
{
	if (attack)
	{
		tl = (tl == 0) ? LASER_SHOOTING_TIMER : tl - 1;	//Danke Gabriel :D
		if (tl == LASER_SHOOTING_TIMER - 1)
		{
			if (facing_r)
			{
				Laservektor.push_back(erstelle_Laser((35 + p1->player_start_x), p1->player_y + 19, facing_r));
			}
			else {
				Laservektor.push_back(erstelle_Laser((p1->player_start_x), p1->player_y + 19, facing_r));
			}
		}
	}
	else {
		tl = LASER_SHOOTING_TIMER;
	}
	for (size_t i = 0; i < Laservektor.size(); i++)
	{
		Laservektor.at(i).posx = Laservektor.at(i).posx + (p1->player_x_alt - p1->player_x);
		Laservektor.at(i).posy = Laservektor.at(i).starty - (p1->player_y - p1->player_start_y);
		if (Laservektor.at(i).direction_right)
		{
			Laservektor.at(i).posx = Laservektor.at(i).posx + LASER_SPEED;
		}
		else {
			Laservektor.at(i).posx = Laservektor.at(i).posx - LASER_SPEED;
		}
		if (distance_from_player(i) > LASER_RENDERDISTANCE)
		{
			Laservektor.erase(Laservektor.begin() + i);
		}
	}
	std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart_O_f;
	bool crash = false;
	for (size_t i = 0; i < Laservektor.size(); i++)	//Zweite schleife, sonst wird auf evtl. gelöschtes zugegriffen...
	{
		elem_O_f = listenstart_O_f;
		crash = false;

		while (elem_O_f->next != nullptr && crash == false)
		{
			if (elem_O_f->nohitbox == false)
			{
				if (Laservektor.at(i).posx < (elem_O_f->posx + elem_O_f->breite - 1) && (Laservektor.at(i).posx + 25) > (elem_O_f->posx))
				{
					if ((Laservektor.at(i).posy + 1) > elem_O_f->posy && (Laservektor.at(i).posy) < (elem_O_f->posy + elem_O_f->hoehe - 1))
					{
						//Theoretisch muss hier jede Laser - Objekt - Kollision behandelt werden
						
						Laservektor.erase(Laservektor.begin() + i);;
						crash = true;	//Setzen des bools, um weitere ausführung der Schleife zu verhindern (Sonst wird auf gelöschtes zugegriffen...)
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
	}



}


Spieler* GameState::get_Spieler()
{
	return this->p1;
}

Spieler* GameState::get_Gegner()
{
	return this->g1;
}

std::shared_ptr<GameState::Objekt_fest> GameState::erstelle_Objekt_fest_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<GameState::Objekt_fest> next, std::shared_ptr<Gosu::Image> image, double scale_x, double scale_y, bool hit, bool destr)
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
	temp.nohitbox = hit;

	temp.next = next;
	temp.image = image;
	temp.scale_x = scale_x;
	temp.scale_y = scale_y;
	temp.destroyable = destr;
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

std::shared_ptr<GameState::Objekt_damage> GameState::erstelle_Objekt_damage_ptr(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<GameState::Objekt_damage> next, std::shared_ptr<Gosu::Image> image, double scale_x, double scale_y)
{
	GameState::Objekt_damage temp;
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
	return std::make_shared<GameState::Objekt_damage>(temp);
}
	
GameState::Laser GameState::erstelle_Laser(double x, double y, bool d_r)
{
	GameState::Laser temp;
	temp.posx = x;
	temp.posy = y;
	temp.startx = x;
	temp.starty = y;
	temp.direction_right = d_r;
	return temp;
}
	
	 
	double GameState::distance_from_player(std::shared_ptr<GameState::Objekt_fest> o2)
	{
		return sqrt(pow((this->p1->player_x - o2->startx), 2) + pow((this->p1->player_y - o2->starty), 2));
	}
	double GameState::distance_from_player(std::shared_ptr<GameState::Objekt_damage> o2)
	{
		return sqrt(pow((this->p1->player_x - o2->startx), 2) + pow((this->p1->player_y - o2->starty), 2));
	}
	double GameState::distance_from_player(int vektorlisteni)
	{
		return sqrt(pow((this->p1->player_x - Laservektor.at(vektorlisteni).posx), 2) + pow((this->p1->player_y - (Laservektor.at(vektorlisteni).posy)), 2));
	}
	bool GameState::kollision_rechts(std::shared_ptr<GameState::Objekt_fest> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)//, std::shared_ptr<Spieler> p1)//std::shared_ptr<GameState::Objekt_fest> listenstart_O_f, Spieler p1, std::shared_ptr<GameState::Player_data> iplayertemp)
	{
		std::shared_ptr<GameState::Objekt_fest> elem_O_f = this->listenstart_O_f;
		//std::shared_ptr<GameState::Objekt_fest> elem_O_f = listenstart;
		bool tmp = false;
		//auto elem_O_f = GameState::get_listenstart_O_f();   //listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != nullptr)
		{
			if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
			{
				if ((this->p1->player_x + iplayertemp->breite + 3 + this->p1->speedPlayer) > elem_O_f->startx && (this->p1->player_x) < (elem_O_f->startx + elem_O_f->breite) - 5)
				{
					if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
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
			if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
			{
				if ((this->p1->player_x - (3 + this->p1->speedPlayer)) < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) > (elem_O_f->startx + 5))
				{
					if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
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
			if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
			{
				if (this->p1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) >(elem_O_f->startx))
				{
					if ((this->p1->player_y + iplayertemp->hoehe) > elem_O_f->starty && (this->p1->player_y - (5 + abs(this->p1->speedPlayerY))) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
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
			if (distance_from_player(elem_O_f) < 5000 && elem_O_f->nohitbox == false)
			{
				if (this->p1->player_x < (elem_O_f->startx + elem_O_f->breite) && (this->p1->player_x + iplayertemp->breite) >(elem_O_f->startx))
				{
					if ((this->p1->player_y + iplayertemp->hoehe + 5 + abs(this->p1->speedPlayerY)) > elem_O_f->starty && (this->p1->player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}	
	bool GameState::kollsion_damage(std::shared_ptr<GameState::Objekt_damage> listenstart, std::shared_ptr<GameState::Player_data> iplayertemp)
	{
		std::shared_ptr<GameState::Objekt_damage> elem_O_d = listenstart;
		bool tmp = false;
		while (elem_O_d->next != nullptr)
		{
			if (distance_from_player(elem_O_d) < 5000 && elem_O_f->nohitbox == false)
			{
				if (this->p1->player_x < (elem_O_d->startx + elem_O_d->breite - 1) && (this->p1->player_x + iplayertemp->breite - 1) >(elem_O_d->startx))
				{
					if ((this->p1->player_y + iplayertemp->hoehe -1 ) > elem_O_d->starty && (this->p1->player_y) < (elem_O_d->starty + elem_O_d->hoehe - 1))
					{
						tmp = true;
					}
				}
			}
			elem_O_d = elem_O_d->next;
		}
		return tmp;
	}