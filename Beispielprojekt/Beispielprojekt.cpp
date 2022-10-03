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

class GameWindow;
class GameState {
public:
	GameState()
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
	{};

	struct Objekt_fest
	{
		double posx, posy, startx, starty, posz;
		double breite, hoehe, scale_x, scale_y;
		std::shared_ptr<Objekt_fest> next;
		std::shared_ptr<Gosu::Image> image;
	};
	Objekt_fest erstelle_Objekt_fest(double breite, double hoehe, double posx, double posy, double posz, std::shared_ptr<Objekt_fest> next, std::shared_ptr<Gosu::Image> image, double scale_x = 1, double scale_y = 1)
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
	struct Player_data
	{
		bool active;
		double breite, hoehe, scale_x, scale_y;
		Player_data* next;
		Gosu::Image* image;
	};
	Player_data erstelle_Player_data(double breite, double hoehe, struct Player_data* next, Gosu::Image* image, bool active, double scale_x = 1, double scale_y = 1)
	{
		Player_data temp;
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

	int health = 3;

	bool pressed = false;
	bool w_pressed = false;// player sprung
	bool a_pressed = false;// player links
	bool d_pressed = false;// player rechts

	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image Wand;
	Gosu::Image hintergrund;
	Gosu::Image Kiste;
	Gosu::Image Plattform1;
	//HUD
	Gosu::Image hudHP;
	Gosu::Image hudHP2;
	Gosu::Image hudHP1;
	Gosu::Image hudHP0;
	Gosu::Image GameOver;
	//Player, temp
	Gosu::Image rPlayertemp1;
	Gosu::Image rPlayertemp2;
	Gosu::Image rPlayertempA1;
	Gosu::Image rPlayertempA2;
	Gosu::Image lPlayertemp1;
	Gosu::Image lPlayertemp2;
	Gosu::Image lPlayertempA1;
	Gosu::Image lPlayertempA2;

	//Game Window

	Objekt_fest ilistenproblenloeser = erstelle_Objekt_fest(0, 0, 0, 0, 0, NULL, NULL);					 //Einfach nicht hinterfragen
	Objekt_fest ibodenR = erstelle_Objekt_fest(474, 58, 400, 550, 100, &ilistenproblenloeser, &bodenR);
	Objekt_fest ibodenL = erstelle_Objekt_fest(474, 58, 0, 550, 100, &ibodenR, &bodenL);				 //Linked list über pointer
	Objekt_fest iKiste = erstelle_Objekt_fest(168, 168, 730, 300, 100, &ibodenL, &Kiste);
	Objekt_fest iPlattform1 = erstelle_Objekt_fest(1075, 233, 300, 200, 100, &iKiste, &Plattform1);
	Objekt_fest iWand = erstelle_Objekt_fest(474, 58, 700, 500, 100, &iPlattform1, &Wand);

	Objekt_fest* elem_O_f;
	Objekt_fest* listenstart_O_f = &iWand; //Hier immer letztes Element hinschreiben

	//Liste für Player
	Player_data ilistenproblenloeserplayer = erstelle_Player_data(0, 0, NULL, NULL, false);
	Player_data iplayertemp = erstelle_Player_data(53, 94, &ilistenproblenloeserplayer, &rPlayertemp1, true);

	Player_data* elem_P_d;
	Player_data* listenstart_P_d = &iplayertemp; //Hier immer letztes Element hinschreiben


#pragma region 1 //Kollsionskäse
	double distance_from_player(Objekt_fest * o2)
	{
		return sqrt(pow((p1.player_x - o2->startx), 2) + pow((p1.player_y - o2->starty), 2));
	}
	bool kollision_rechts()
	{
		bool tmp = false;
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
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
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
			{
				//debug-Käse
				//std::cout << p1.player_x << "	" << (iWand.startx + iWand.breite) << "	" << collision_links << "	" << p1.player_y << "	" << iWand.starty << "\n";
				if ((p1.player_x - 5) < (elem_O_f->startx + elem_O_f->breite) && (p1.player_x + iplayertemp.breite) > (elem_O_f->startx))
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
	bool kollision_oben()
	{
		bool tmp = false;
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
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
		elem_O_f = listenstart_O_f; //Hier immer letztes Element hinschreiben!
		while (elem_O_f->next != NULL)
		{
			if (distance_from_player(elem_O_f) < 5000)
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
#pragma endregion	
};

class GameWindow : public Gosu::Window
{
public:
	GameState game;
	GameWindow()
		: Window(800, 600)
		, game()
	{
		set_caption("Dr. Salzig und Mister Coco");
	};
	void draw() override
	{
		//Level Design
		game.elem_O_f = game.listenstart_O_f; //Hier immer letztes Element hinschreiben!  (Weil wegen sonst wird der Player gerendert wo er net soll, weil der is ja starr)
		while (game.elem_O_f->next != NULL) 
		{
			if (game.distance_from_player(game.elem_O_f) < 5000)  //Objekte werden nur gerendert wenn Sie näher als 5k Pixel sind
			{
				game.elem_O_f->image->draw(game.elem_O_f->posx, game.elem_O_f->posy, game.elem_O_f->posz);
			}
			game.elem_O_f = game.elem_O_f->next;
		}
		game.hintergrund.draw_rot(400, 320, 10.0,
			0.0,
			0.5, 0.5);
		//HUD
		if (game.health == 3)
		{
			game.hudHP.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
		}
		else if (game.health == 2)
		{
			game.hudHP2.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
		}
		else if (game.health == 1)
		{
			game.hudHP1.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
		}
		else if (game.health <= 0)
		{
			game.hudHP0.draw_rot(120, 40, 100.0,
				0.0,
				0.5, 0.5);
			game.GameOver.draw_rot(400, 300, 100.0,
				0.0,
				0.5, 0.5);


		}
		//game.rPlayertemp1.draw(p1.player_start_x, p1.player_start_y, 100, 1, 1);
		//game.rPlayertemp2.draw(p1.player_start_x, p1.player_start_y, 100, 1, 1);    //Veraltet
		//Player rendering
		game.elem_P_d = game.listenstart_P_d;
		while (game.elem_P_d->next != NULL)
		{
			if (game.elem_P_d->active == true)  //Nur Playerbild rendern, welches aktiv ist
			{
				game.elem_P_d->image->draw(p1.player_start_x, p1.player_start_y, 100, 1, 1);
				break;
			}
			game.elem_P_d = game.elem_P_d->next;
		}
	}
	
	void update() override
	{
		collision_rechts = game.kollision_rechts();
		collision_links = game.kollision_links();
		collision_oben = game.kollision_oben();
		collision_unten = game.kollision_unten();

		//HUD
		if (input().down(Gosu::KB_K)&& !game.pressed)
		{
			game.pressed = true;
			game.health = game.health - 1;
			
		}
		else if (!input().down(Gosu::KB_K)) { game.pressed = false; }

		if (input().down(Gosu::KB_F) && game.health <= 0) //Respawn
		{
			game = GameState(); //Neues Spiel erzeugen
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


		//Haupt-Map-Move-Funktionen
		game.elem_O_f = game.listenstart_O_f;
		while (game.elem_O_f->next != NULL)
		{
			//Renderdistanz wieder adden
			game.elem_O_f->posx = game.elem_O_f->startx - (p1.player_x - p1.player_start_x);
			game.elem_O_f->posy = game.elem_O_f->starty - (p1.player_y - p1.player_start_y);
			game.elem_O_f = game.elem_O_f->next;
		}

		//Player
		
		//sprungdauer
			// ist w gedrückt?
		if (input().down(Gosu::KB_W)) {
			game.w_pressed = true;
		}
		else {
			game.w_pressed = false;
			p1.sprung_t = 0;
		}

		//rechtsdauer // bildschirm nach links
			// ist d gedrückt?
		if (input().down(Gosu::KB_D)) {
			game.d_pressed = true;
		}
		else {
			game.d_pressed = false;
			p1.player_t_x_d = 0;
		}
		//linksdauer //Bildschirm nach rechts
			// ist a gedrückt?
		if (input().down(Gosu::KB_A)) {
			game.a_pressed = true;
		}
		else {
			game.a_pressed = false;
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
