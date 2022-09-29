#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>


class GameWindow : public Gosu::Window
{
public:
	int health = 3;
	//Level Design
	Gosu::Image bodenR;
	Gosu::Image bodenL;
	Gosu::Image hintergrund;
	//HUD
	Gosu::Image hudHP;
	Gosu::Image hudHP2;
	Gosu::Image hudHP1;
	Gosu::Image hudHP0;
	Gosu::Image GameOver;
	bool pressed = false;
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
		bodenR.draw_rot(600, 575, 100.0,
			0.0,
			0.5, 0.5);
		bodenL.draw_rot(200, 575, 100.0,
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

	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
