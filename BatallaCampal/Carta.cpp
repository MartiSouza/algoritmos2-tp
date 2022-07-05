#include "Carta.h"
#include "Jugador.h"

Carta::Carta(int aleatorio) {
	if (aleatorio < 1 || aleatorio > 6) {
		throw "No se puede crear una carta cuyo identificador no esté entre 1 y 6 inclusive.";
	}

	switch (aleatorio) {
	case 1:
		this->tipoDeCarta = AVIONES;
		this->descripcion = "Avion";
		break;
	case 2:
		this->tipoDeCarta = BARCOS;
		this->descripcion = "Barco";
		break;
	case 3:
		this->tipoDeCarta = MINAS;
		this->descripcion = "Mina";
		break;
	case 4:
		this->tipoDeCarta = RADAR;
		this->descripcion = "Radar";
		break;
	case 5:
		this->tipoDeCarta = SUPER;
		this->descripcion = "Super Bomba";
		break;
	case 6:
		this->tipoDeCarta = MISIL;
		this->descripcion = "Misil";
		break;
	}
}

char Carta::getTipoDeCarta() {

	return this->tipoDeCarta;
}

std::string Carta::getDescripcion() {

	return this->descripcion;
}

Carta::~Carta() {
}

