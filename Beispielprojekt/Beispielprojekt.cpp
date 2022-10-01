#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include "Spieler.cpp"
#include <math.h>

bool y_down = false; // sprung?
bool x_down = false; // ist waagerecht gedrückt ?
bool collision_rechts = false;
bool collision_links = false;
bool collision_oben = false;
bool collision_unten = true;
Spieler p1;

class GameWindow : public Gosu::Window
{
public:

	struct Objekt_fest
	{
		double posx, posy, startx, starty, posz;
		double breite, hoehe;
		Objekt_fest *next;
		Gosu::Image* image;
		void reset() 
		{
			this->posx = startx;
			this->posy = starty;
		}	
	};
	Objekt_fest erstelle_Objekt_fest(double breite, double hoehe, double posx, double posy, double posz, struct Objekt_fest* next, Gosu::Image* image)
	{
		Objekt_fest temp;
		temp.breite = breite;
		//temp.breite = image->width();
		temp.hoehe = hoehe;
		//temp.hoehe = image->height();
		temp.posx = posx;
		temp.posy = posy;
		temp.startx = posx;
		temp.starty = posy;
		temp.posz = posz;
		temp.next = next;
		temp.image = image;
		return temp;
	}
	
	Objekt_fest* elem_O_f;

	int health = 3;

	bool pressed = false;
	bool w_pressed = false;// player sprung
	bool a_pressed = false;// player links
	bool d_pressed = false;// player rechts

	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image Wand;
	Gosu::Image hintergrund;
	//HUD
	Gosu::Image hudHP;
	Gosu::Image hudHP2;
	Gosu::Image hudHP1;
	Gosu::Image hudHP0;
	Gosu::Image GameOver;
	//Player, temp
	Gosu::Image Playertemp;

	//Game Window
	GameWindow()
		: Window(800, 600)
		//Level Design
		, bodenR("boden1.jpg")
		, bodenL("boden1.jpg")
		, Wand("boden1.jpg")
		, hintergrund("hintergrund.jfif")
		//HUD
		, hudHP("hud_hp.png")
		, hudHP2("hud_hp-1.png")
		, hudHP1("hud_hp-2.png")
		, hudHP0("hud_hp-3.png")
		, GameOver("GameOver.png")
		//Player (temp)
		, Playertemp("Forscher.jpg")
	{
		set_caption("Dr. Salzig und Mister Coco");
	}

	Objekt_fest ilistenproblenloeser = erstelle_Objekt_fest(0, 0, 0, 0, 0, NULL, NULL);					 //Einfach nicht hinterfragen
	Objekt_fest ibodenR = erstelle_Objekt_fest(474, 58, 600, 575, 100, &ilistenproblenloeser, &bodenR);	 
	Objekt_fest ibodenL = erstelle_Objekt_fest(474, 58, 200, 575, 100, &ibodenR, &bodenL);				 //Linked list über pointer
	Objekt_fest iWand = erstelle_Objekt_fest(474, 58, 700, 525, 100, &ibodenL, &Wand);
	//Bei erstellung eines neuen Objektes immer die Listenschleifen anpassen!   Oder neues Objekt iwo zwischenreinpfuschen

	//Liste für Player
	Objekt_fest iplayertemp = erstelle_Objekt_fest(53, 94, 300, 500, 100, &ilistenproblenloeser, &Playertemp);

	void map_reset()
	{
		//elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!     //Wenn Player fertig, unnötig weil rendering automatisch von Player-pos abhängig
		//while (elem_O_f->next != NULL)
		//{
		//	elem_O_f->reset();
		//	elem_O_f = elem_O_f->next;
		//}
		 
		p1.player_x = 300;         //Auskommentieren wenn Player fertig
		p1.player_y = 500;
	}

	double distance_from_player(Objekt_fest* o2)
	{
		return sqrt(pow((p1.player_x - o2->posx), 2) + pow((p1.player_y - o2->posy), 2));
	}

	bool kollision_rechts()
	{
		bool tmp = false;
		elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 1000)
			{
				if ((p1.player_x + iplayertemp.breite + 5) > elem_O_f->startx && (p1.player_x + iplayertemp.breite) < (elem_O_f->startx + elem_O_f->breite))
				{
					std::cout << "Stufe 1" << "	";
					if ((p1.player_y + iplayertemp.hoehe) > elem_O_f->starty && (p1.player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}

	bool kollision_links()
	{

		return true;
	}

	bool kollision_oben()
	{

		return true;
	}

	bool kollision_unten()
	{

		return true;
	}

	
	void draw() override
	{
		//Level Design
		elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!  (Weil wegen sonst wird der Player gerendert wo er net soll, weil der is ja starr)
		while (elem_O_f->next != NULL) 
		{
			elem_O_f->image->draw_rot(elem_O_f->posx, elem_O_f->posy, elem_O_f->posz,
				0.0,
				0.5, 0.5);
			elem_O_f = elem_O_f->next;
		}
		hintergrund.draw_rot(400, 320, 10.0,
			0.0,
			0.5, 0.5);
		//HUD
		if (health == 3)
		{
			hudHP.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
		}
		else if (health == 2)
		{
			hudHP2.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
		}
		else if (health == 1)
		{
			hudHP1.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
		}
		else if (health <= 0)
		{
			hudHP0.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
			GameOver.draw_rot(400, 300, 100.0,
				0.0,
				0.5, 0.5);


		}
		Playertemp.draw_rot(300, 500, 100, 0.0, 0.5, 0.5, 0.2, 0.2);
	}
	
	void update() override
	{
		collision_rechts = kollision_rechts();
		collision_links = kollision_links();
		collision_oben = kollision_oben();
		collision_unten = kollision_unten();

		//HUD
		if (input().down(Gosu::KB_K)&& !pressed)
		{
			pressed = true;
			health = health - 1;
			
		}
		else if (!input().down(Gosu::KB_K)) { pressed = false; }

		if (input().down(Gosu::KB_F) && health <= 0) //Respawn
		{
			health = 3;			//Player heilen
			map_reset();	//Zurücksetzen der Objektpositionen und damit des Spielers auf Startwert
			
		}


		//Reine Test-Features, können bei working Player weg
		if (input().down(Gosu::KB_LEFT))
		{
			elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!
			while (elem_O_f->next != NULL)
			{
				elem_O_f->posx = elem_O_f->posx + 5;
				elem_O_f = elem_O_f->next;
				p1.player_x = p1.player_x - 5;
			}
		}
		if (input().down(Gosu::KB_RIGHT))
		{
			if (collision_rechts == false) 
			{
				elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!
				while (elem_O_f->next != NULL)
				{
					elem_O_f->posx = elem_O_f->posx - 5;
					elem_O_f = elem_O_f->next;
					p1.player_x = p1.player_x + 5;
				}
			}
			
		}
		if (input().down(Gosu::KB_UP))
		{
			elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!
			while (elem_O_f->next != NULL)
			{
				elem_O_f->posy = elem_O_f->posy + 5;
				elem_O_f = elem_O_f->next;
				p1.player_y = p1.player_y - 5;
			}
		}
		if (input().down(Gosu::KB_DOWN))
		{
			elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!
			while (elem_O_f->next != NULL)
			{
				elem_O_f->posy = elem_O_f->posy - 5;
				elem_O_f = elem_O_f->next;
				p1.player_y = p1.player_y + 5;
			}
		}

		//debug-Käse
		std::cout << p1.player_x << "	" << iWand.startx << "	" << collision_rechts << "	" << p1.player_y << "	" << iWand.starty << "\n";

		//Haupt-Map-Move-Funktionen                                            Diesen Teil entkommentieren sobald player fertig
		elem_O_f = &iWand; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			elem_O_f->posx = elem_O_f->startx - p1.player_x;
			elem_O_f->posy = elem_O_f->starty - p1.player_y;
			elem_O_f = elem_O_f->next;
		}

		//Player
		
		//sprungdauer
			// ist w gedrückt?
		if (input().down(Gosu::KB_W)) {
			w_pressed = true;
			p1.sprung_t = p1.sprung_t + 1;
			//debug
			std::cout << p1.sprung_t << std::endl;
		}
		else {
			w_pressed = false;
			p1.sprung_t = 0;
		}

		//rechtsdauer // bildschirm nach links
			// ist d gedrückt?
		if (input().down(Gosu::KB_D)) {
			d_pressed = true;
			p1.player_t_x_d = p1.player_t_x_d - 1;
			//debug
			//std::cout << "zeit taste d" << p1.player_t_x_d << std::endl;
		}
		else {
			d_pressed = false;
			p1.player_t_x_d = 0;
		}
		//linksdauer //Bildschirm nach rechts
			// ist a gedrückt?
		if (input().down(Gosu::KB_A)) {
			a_pressed = true;
			p1.player_t_x_a = p1.player_t_x_a - 1;
			//debug
			//std::cout << "Zeit taste a"<< p1.player_t_x_a << std::endl;
		}
		else {
			a_pressed = false;
			p1.player_t_x_a= 0;
		}
		//sprung
		
		//Beschleunigte bewegung x :D funktioniert 
		if (input().down(Gosu::KB_D)&& (p1.player_beschleunigung(1, p1.player_t_x_d, p1.player_v_xmax) < 10)) {
			//ibodenL.posx = ibodenL.posx + p1.player_beschleunigung(1, p1.player_t_x_d, p1.player_v_xmax);//bewegung x beschleunigt (tobis code kopiert und mit beschleunigung versehen)
			//ibodenR.posx = ibodenR.posx + p1.player_beschleunigung(1, p1.player_t_x_d, p1.player_v_xmax);
			p1.player_x = p1.player_x - p1.player_beschleunigung(1, p1.player_t_x_d, p1.player_v_xmax);
			// debug
			//std::cout << "beschleunigung:" << p1.player_beschleunigung(1, p1.player_t_x_d, p1.player_v_xmax) << std::endl;
			//std::cout << "Player´s x:" << p1.player_x << std::endl;
		}
		else if (input().down(Gosu::KB_A) && (p1.player_beschleunigung(1, p1.player_t_x_a, p1.player_v_xmax) <= 10)) {
			//ibodenL.posx = ibodenL.posx - p1.player_beschleunigung(1, p1.player_t_x_a, p1.player_v_xmax);
			//ibodenR.posx = ibodenR.posx - p1.player_beschleunigung(1, p1.player_t_x_a, p1.player_v_xmax);
			p1.player_x = p1.player_x + p1.player_beschleunigung(1, p1.player_t_x_a, p1.player_v_xmax);
			// debug
			//std::cout << "beschleunigung:" << p1.player_beschleunigung(1, p1.player_t_x_a, p1.player_v_xmax) << std::endl;
			//std::cout << "Player´s x:" << p1.player_x << std::endl;
		}
		else if (input().down(Gosu::KB_D) && (p1.player_beschleunigung(1, p1.player_t_x_d, p1.player_v_xmax) > 10)) {
			//ibodenL.posx = ibodenL.posx + 10;//bewegung x max beschleunigt (tobis code kopiert und mit beschleunigung versehen)
			//ibodenR.posx = ibodenR.posx + 10;
			p1.player_x = p1.player_x - 10; 
			//std::cout << "Player´s x:" << p1.player_x << std::endl;
		}
		else if (input().down(Gosu::KB_A) && (p1.player_beschleunigung(1, p1.player_t_x_a, p1.player_v_xmax)) > 10) {
			//ibodenL.posx = ibodenL.posx - 10;
			//ibodenR.posx = ibodenR.posx - 10;
			p1.player_x = p1.player_x + 10;
			//std::cout << "Player´s x:" << p1.player_x << std::endl;
		}
	}
};

// C++ Hauptprogramm
int main()
{
	/*std::vector<Objekt_fest> Objektliste;
	Objekt_fest ibodenR(575, 100, 600, 575);

	Objektliste.push_back(ibodenR);*/

	
	GameWindow window;
	window.show();
	
}
