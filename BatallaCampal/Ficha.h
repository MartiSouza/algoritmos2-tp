#ifndef FICHA_H
#define FICHA_H

enum tipoDeFicha {
	AVION, BARCO, MINA, SOLDADO, SIN_DEFINIR
};

enum tipoCarta {
	MISIL, RADAR, SUPER, BARCOS, AVIONES, MINAS
};

class Ficha {

private:

	int posicionX;
	int posicionY;
	int posicionZ;
	char tipo;

public:

	/*
	 *  Pre:
	 *  Post: crea una ficha con el tipo sin definir.
	 */
	Ficha();

	/*
	 * Pre: Recibe un tipo de ficha, con valores válidos: SOLDADO, AVIÓN, BARCO, MINAS.
	 * Post: Se crea una ficha del tipo dado si el valor es válido, sino deja el tipo sin definir.
	 * Las posiciones iniciales estarán seteadas en -1, deben actualizarse.
	 */
	Ficha(char tipo, int x, int y, int z);

	/*
	 *  Pos: Devuelve la posicion X/fila
	 */
	int getPosicionY();

	/*
	 *  Pos: Devuelve la posicion Y/columna
	 */
	int getPosicionX();

	/*
	 *  Pos: Devuelve la posicion Z/altura
	 */
	int getPosicionZ();
	/*
	 * pre: -
	 * pos: devuelve el tipo de ficha
	 */
	char getTipo();
	/*
	 * pre: el tipo tiene que ser soldado, avion, barco o mina.
	 * post: setea el tipo de la ficha actual según el tipo recibido.
	 */
	void setTipo(char tipo);
	/*
	 *  Pre: Necesita las coordenadas de la fila y la columna
	 *  Pos: Si es soldado, cambia su posicion
	 */
	void setCoordenadasSoldado(int posicionX, int posicionY);
	/*
	 *  Pre: Necesita las coordenadas de la casilla
	 *  Pos: Devuelve true si la casilla es valida
	 */
	bool esPosicionValida(int x, int y, int z);
	/*
	 *  Pre: Necesita un tipo de ficha
	 *  Pos: Devuelve true si el tipo de ficha es valido
	 */
	bool esTipoValido(char tipo);
	/*
	 *  Pre: Necesita las coordenadas y un tipo de ficha
	 *  Pos: Si el tipo y la posicion concuerdan, devuelve true. Sino, devuelve false.
	 */
	bool tipoConcuerdaConPosicion(int x, int y, int z, char tipo);
	/*
	 *  Pre: Necesita un tipo de ficha
	 *  Pos: Setea la ficha al tipo dado
	 */
	void definirTipo(char tipo);
};

#endif
