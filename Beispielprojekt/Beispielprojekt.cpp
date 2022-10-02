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

const double MAX_SPEED = 15; //Maximale Geschwindikkeit Spieler x-Richtung

class GameWindow : public Gosu::Window
{
public:

	struct Objekt_fest
	{
		double posx, posy, startx, starty, posz;
		double breite, hoehe, scale_x, scale_y;
		Objekt_fest *next;
		Gosu::Image* image;
		void reset() //veraltet, löschen?
		{
			this->posx = startx;
			this->posy = starty;
		}
	};

	Objekt_fest erstelle_Objekt_fest(double breite, double hoehe, double posx, double posy, double posz, struct Objekt_fest* next, Gosu::Image* image, double scale_x = 1, double scale_y = 1)
	{
		Objekt_fest temp;
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
	Objekt_fest ibodenR = erstelle_Objekt_fest(474, 58, 400, 550, 100, &ilistenproblenloeser, &bodenR);	 
	Objekt_fest ibodenL = erstelle_Objekt_fest(474, 58, 0, 550, 100, &ibodenR, &bodenL);				 //Linked list über pointer
	Objekt_fest iWand = erstelle_Objekt_fest(474, 58, 700, 500, 100, &ibodenL, &Wand);

	Objekt_fest* elem_O_f;
	Objekt_fest* listenstart = &iWand;
	//Bei erstellung eines neuen Objektes immer die Listenschleifen anpassen!   Oder neues Objekt iwo zwischenreinpfuschen

	//Liste für Player
	Objekt_fest iplayertemp = erstelle_Objekt_fest(53, 94, 300, 466, 100, &ilistenproblenloeser, &Playertemp);

	void map_reset() //brauchen wir das noch? Glaub nicht...
	{	 
		p1.player_x = 0;         //Auskommentieren wenn Player fertig
		p1.player_y = 0;		
	}

	double distance_from_player(Objekt_fest* o2)
	{
		return sqrt(pow((p1.player_x - o2->startx), 2) + pow((p1.player_y - o2->starty), 2));
	}

	bool kollision_rechts()
	{
		bool tmp = false;
		elem_O_f = listenstart; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 1000)
			{
				if ((p1.player_x + iplayertemp.breite + 5) > elem_O_f->startx && (p1.player_x + iplayertemp.breite) < (elem_O_f->startx + elem_O_f->breite))
				{
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
		bool tmp = false;
		elem_O_f = listenstart; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 1000)
			{
				//debug-Käse
				//std::cout << p1.player_x << "	" << (iWand.startx + iWand.breite) << "	" << collision_links << "	" << p1.player_y << "	" << iWand.starty << "\n";
				if ((p1.player_x - 5) < (elem_O_f->startx + elem_O_f->breite) && (p1.player_x + iplayertemp.breite) > (elem_O_f->startx))
				{
					//std::cout << "Stufe 1" << "	";
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
	bool kollision_oben()
	{
		bool tmp = false;
		elem_O_f = listenstart; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 1000)
			{
				if (p1.player_x < (elem_O_f->startx + elem_O_f->breite) && (p1.player_x + iplayertemp.breite) >(elem_O_f->startx))
				{
					if ((p1.player_y + iplayertemp.hoehe) > elem_O_f->starty && (p1.player_y - 5) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}
	bool kollision_unten()
	{
		bool tmp = false;
		elem_O_f = listenstart; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 1000)
			{
				if (p1.player_x < (elem_O_f->startx + elem_O_f->breite) && (p1.player_x + iplayertemp.breite) >(elem_O_f->startx))
				{
					if ((p1.player_y + iplayertemp.hoehe + 5) > elem_O_f->starty && (p1.player_y) < (elem_O_f->starty + elem_O_f->hoehe))
					{
						tmp = true;
					}
				}
			}
			elem_O_f = elem_O_f->next;
		}
		return tmp;
	}

	
	void draw() override
	{
		//Level Design
		elem_O_f = listenstart; //Hier immer letztes Element hinschreiben!  (Weil wegen sonst wird der Player gerendert wo er net soll, weil der is ja starr)
		while (elem_O_f->next != NULL) 
		{
			if (distance_from_player(elem_O_f) < 5000)  //Objekte werden nur gerendert wenn Sie näher als 5k Pixel sind
			{
				elem_O_f->image->draw(elem_O_f->posx, elem_O_f->posy, elem_O_f->posz);
			}
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
		Playertemp.draw(p1.player_start_x, p1.player_start_y, 100, 0.2, 0.2);
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
			if (collision_links == false)
			{
				p1.player_x = p1.player_x - 5;
			}
		}
		if (input().down(Gosu::KB_RIGHT))
		{
			if (collision_rechts == false) 
			{
				p1.player_x = p1.player_x + 5;
			}
			
		}
		if (input().down(Gosu::KB_UP))
		{
			if (collision_oben == false)
			{
				p1.player_y = p1.player_y - 5;
			}
		}
		if (input().down(Gosu::KB_DOWN))
		{
			if (collision_unten == false)
			{
				p1.player_y = p1.player_y + 5;
			}
		}


		//Haupt-Map-Move-Funktionen                                            Diesen Teil entkommentieren sobald player fertig
		elem_O_f = listenstart; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			elem_O_f->posx = elem_O_f->startx - (p1.player_x - p1.player_start_x);
			elem_O_f->posy = elem_O_f->starty - (p1.player_y - p1.player_start_y);
			elem_O_f = elem_O_f->next;
		}

		//Player
		
		//sprungdauer
			// ist w gedrückt?
		if (input().down(Gosu::KB_W)) {
			w_pressed = true;
		}
		else {
			w_pressed = false;
			p1.sprung_t = 0;
		}

		//rechtsdauer // bildschirm nach links
			// ist d gedrückt?
		if (input().down(Gosu::KB_D)) {
			d_pressed = true;
		}
		else {
			d_pressed = false;
			p1.player_t_x_d = 0;
		}
		//linksdauer //Bildschirm nach rechts
			// ist a gedrückt?
		if (input().down(Gosu::KB_A)) {
			a_pressed = true;
		}
		else {
			a_pressed = false;
			p1.player_t_x_a= 0;
		}

		//sprung
		if (input().down(Gosu::KB_W)&& (p1.player_beschleunigung(1, p1.sprung_t) > 100)) {
			double yt = p1.player_beschleunigung(1, p1.sprung_t);
		p1.player_y = p1.player_y + p1.player_sprung_y(yt, p1.player_y, p1.sprung_t);
		p1.sprung_t = p1.sprung_t - 1;
		
		
		//std::cout << "beschleunigung:" << p1.player_beschleunigung(1, p1.sprung_t) << std::endl;
		//std::cout << "Player´s y:" << p1.player_y << std::endl;
		//std::cout << "zeit taste d" << p1.sprung_t << std::endl;
		}
		else if (input().down(Gosu::KB_W) && (p1.player_beschleunigung(1, p1.sprung_t) < 100)) {
			p1.player_y = p1.player_y - 10;
			
			
			//std::cout << "Player´s x:" << p1.player_x << std::endl;
		}

		//Beschleunigte bewegung x :D funktioniert, aber noch nicht begrenzt beschleunigt ( warum auch immer
		
		if (input().down(Gosu::KB_D)) {
			p1.speedPlayer = (p1.player_beschleunigung(1, p1.player_t_x_d) < MAX_SPEED) ? p1.player_beschleunigung(1, p1.player_t_x_d) : MAX_SPEED;// wenn beschl. kleiner als 10, dann beschleunigung, sonst 10 (schnellschreibweise 'x?x:x' (ternärer operator) danke Gabriel :D
			p1.player_x = p1.player_x + p1.speedPlayer; 
			p1.player_t_x_d = p1.player_t_x_d + 1;
			
			
			//std::cout << "beschleunigung:" << p1.player_beschleunigung(1, p1.player_t_x_d) << std::endl;
			//std::cout << "Player´s x:" << p1.player_x << std::endl;
			//std::cout << "zeit taste d" << p1.player_t_x_d << std::endl;
		}
		if (input().down(Gosu::KB_A)) {
			p1.speedPlayer = (p1.player_beschleunigung(1, p1.player_t_x_a) < MAX_SPEED) ? p1.player_beschleunigung(1, p1.player_t_x_a) : MAX_SPEED;
			p1.player_x = p1.player_x - p1.speedPlayer;
			p1.player_t_x_a = p1.player_t_x_a + 1;
			
			
			//std::cout << "beschleunigung:" << p1.player_beschleunigung(1, p1.player_t_x_a) << std::endl;
			//std::cout << "Player´s x:" << p1.player_x << std::endl;
			//std::cout << "Zeit taste a"<< p1.player_t_x_a << std::endl;
		}
		
	}
};

// C++ Hauptprogramm
int main()
{	
	GameWindow window;
	window.show();
	
}
