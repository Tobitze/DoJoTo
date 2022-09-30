#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include "Spieler.cpp"

bool y_down = false; // sprung?
bool x_down = false; // ist waagerecht gedrückt ?
Spieler p1;

class GameWindow : public Gosu::Window
{
public:
	
	

	struct Objekt_fest
	{
		double breite, hoehe, posx, posy, startx, starty;
		void reset() 
		{
			this->posx = startx;
			this->posy = starty;
		}
	};
	Objekt_fest erstelle_Objekt_fest(double breite, double hoehe, double posx, double posy)
	{
		Objekt_fest temp;
		temp.breite = breite;
		temp.hoehe = hoehe;
		temp.posx = posx;
		temp.posy = posy;
		temp.startx = posx;
		temp.starty = posy;
		return temp;
	}

	int health = 3;

	bool pressed = false;

	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image hintergrund;
	//HUD
	Gosu::Image hudHP;
	Gosu::Image hudHP2;
	Gosu::Image hudHP1;
	Gosu::Image hudHP0;
	Gosu::Image GameOver;

	Objekt_fest ibodenR = erstelle_Objekt_fest(575, 100, 600, 575); //breite und höhe müssen noch an reale pixel angepasst werden
	Objekt_fest ibodenL = erstelle_Objekt_fest(575, 100, 200, 575);  //Todo: Linked list über pointer

	//Game Window
	GameWindow()
		: Window(800, 600)
		//Level Design
		, bodenR("boden1.jpg")
		, bodenL("boden1.jpg")
		, hintergrund("hintergrund.jfif")
		//HUD
		, hudHP("hud_hp.png")
		, hudHP2("hud_hp-1.png")
		, hudHP1("hud_hp-2.png")
		, hudHP0("hud_hp-3.png")
		, GameOver("GameOver.png")
	{
		set_caption("Dr. Salzig und Mister Coco");
	}

	
	void draw() override
	{
		//Level Design
		hintergrund.draw_rot(400, 320, 100.0,
			0.0,
			0.5, 0.5);
		bodenR.draw_rot(ibodenR.posx , ibodenR.posy, 100.0,
			0.0,
			0.5, 0.5);
		bodenL.draw_rot(ibodenL.posx, ibodenL.posy, 100.0,
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
	}

	
	void update() override
	{
		//HUD
		if (input().down(Gosu::KB_SPACE)&& !pressed)
		{
			pressed = true;
			health = health - 1;
			
		}
		else if (!input().down(Gosu::KB_SPACE)) { pressed = false; }

		if (input().down(Gosu::KB_F) && health <= 0) //Respawn
		{
			health = 3;			//Player heilen
			ibodenL.reset();	//Zurücksetzen der Objektpositionen und damit des Spielers auf Startwert
			ibodenR.reset();
		}

		if (input().down(Gosu::KB_LEFT))
		{
			ibodenL.posx = ibodenL.posx + 5;
			ibodenR.posx = ibodenR.posx + 5;
		}
		if (input().down(Gosu::KB_RIGHT))
		{
			ibodenL.posx = ibodenL.posx - 5;
			ibodenR.posx = ibodenR.posx - 5;
		}

		/*Player
		//sprungdauer
			// ist up gedrückt?
		while (true) {
			bool platzh;
			if (input().down(Gosu::KB_W)) {
				bool platzh = true;
			}
			else { platzh = false; }
			switch (platzh) {
			case true:
				y_down = true;
				p1.sprung_dauer(y_down);
				break;
			case false:
				y_down = false;
				p1.sprung_dauer(y_down);
				break;
			default: 
				break;
			};
			std::cout << p1.sprung_t << std::endl;
		}*/
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
