#ifndef SRC_CARTA_H_
#define SRC_CARTA_H_
#include <string>
#include "Ficha.h"

class Carta {

private:

	char tipoDeCarta;
	std::string descripcion;

public:

	/*
	 * Pre: Necesita un numero para el tipo de carta
	 * Pos: Crea un tipo de carta
	 */
	Carta(int aleatorio);

	/*
	 * Pos: Devuelve el tipo de carta
	 */
	char getTipoDeCarta();
	/*
	 * Pos: Devuelve la descripcion de la carta
	 */
	std::string getDescripcion();
	/*
	 * Pos: Destruye la carta
	 */
	~Carta();

};

#endif
