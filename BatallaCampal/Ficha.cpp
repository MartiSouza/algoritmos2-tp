#include "Ficha.h"
#include <string>
#include <iostream>

Ficha::Ficha(char tipo, int posicionX, int posicionY, int posicionZ) {

	if (this->esPosicionValida(posicionX, posicionY, posicionZ)
			&& this->esTipoValido(tipo)) {

		this->posicionX = posicionX;
		this->posicionY = posicionY;
		this->posicionZ = posicionZ;
		this->tipo = tipo;

		if (!this->tipoConcuerdaConPosicion(posicionX, posicionY, posicionZ,
				tipo)) {
			this->tipo = SIN_DEFINIR;
		}
	} else {
		if (!this->esPosicionValida(posicionX, posicionY, posicionZ)) {
			throw "Error en coordenadas de la ficha.";
		}
		if (!this->esTipoValido(tipo)) {
			throw "Tipo inválido de ficha.";
		}
	}
}

bool Ficha::esPosicionValida(int x, int y, int z) {
	return (x > 0 && y > 0 && z > 0);
}

bool Ficha::esTipoValido(char tipo) {
	return (tipo == BARCO || tipo == MINA || tipo == SOLDADO || tipo == AVION);
}

//Esta función iría en batalla campal
bool Ficha::tipoConcuerdaConPosicion(int posicionX, int posicionY,
		int posicionZ, char tipo) {
	bool esValida = false;
	if (this->esPosicionValida(posicionX, posicionY, posicionZ)
			&& this->esTipoValido(tipo)) {
		if (this->getPosicionZ() == 1) {
			if (this->getTipo() == AVION) {
				esValida = false;
			} else {
				esValida = true;
			}
		} else {
			if (this->getTipo() == AVION) {
				esValida = true;
			} else {
				esValida = false;
			}
		}
	}
	return esValida;
}

char Ficha::getTipo() {
	return this->tipo;
}

int Ficha::getPosicionX() {
	return this->posicionX;
}

int Ficha::getPosicionY() {
	return this->posicionY;
}

int Ficha::getPosicionZ() {
	return this->posicionZ;
}

void Ficha::definirTipo(char tipo) {
	this->tipo = tipo;
	if (!this->esTipoValido(tipo)) {
		this->tipo = SIN_DEFINIR;
	}
}

void Ficha::setCoordenadasSoldado(int posicionX, int posicionY) {
	if (this->tipo != SOLDADO) {
		throw "No deberías cambiar la posición de esta ficha porque no es de soldado :)";
	} else {
		this->posicionX = posicionX;
		this->posicionY = posicionY;
	}
}
