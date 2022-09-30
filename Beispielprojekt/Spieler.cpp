class Spieler // Doris ding Anfang :D
{
public:
	double player_x;// Bewegung x-Achse
	int player_t_x; // zeit, die in x beschleunigt wird
	double player_y;// Bewegung y-achse
	int player_t_y; // zeit, die in y beschleunigt wird 
	double player_a_x;// Geschwindigkeit x-richtung
	const double player_v_xmax = 10; // max geschwindigket x
	double player_a_y;// Geschwindigkeit y-richtung
	const double player_v_ymax = 3; // max geschwindigkeit y
	const double player_g = 9.81;// gravitationskonstante


	int sprung_t; // zählt die zeit des sprungs

	//Konstruktor
	Spieler(){
		this->player_x = 0;
		this->player_y = 0;
	}
		//player Bewegung
		// bewegung in x richtung 
	
	
	double player_beschleunigung(double bx,double tx, double txm) {
		if (tx < txm) {
			tx = tx * 1;
		}
		else {
			tx = txm;
		}
		return this->player_a_x = bx * tx;
	};

	// sprung timer - zählt, wie lange der player springt.
	int sprung_dauer(bool y) {
		while (y = true) {
			switch (y) {
			case true:
				return this->sprung_t = this->sprung_t + 1;;
				break;
			case false:
				return this->sprung_t = 0;
				break;
			default:
				break;
			};

		}
	};
	// bewegug in y richtung
	double player_sprung(double x, double y, double v, double t, bool xx) {
		double zeit_sprung = t;

		for (double u; u < zeit_sprung; u++) { // berechnen von x-Koordinaten derPunkte der Wurfparabel 
			switch (xx) {
			case true:
				return this->player_a_x == 0;//this->beschleunigung()  ;// berechnen der x-Geschwinigkeit -> koordinate = vx(t) / t
				break;
			case false:
				return this->player_a_x == 0;
				break;
			default:
				break;
			};
		};
	};
}; // Doris ding ende :D