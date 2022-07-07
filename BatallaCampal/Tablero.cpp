#include "Tablero.h"

#include <iostream>
#include <stdlib.h>
using namespace std;

Tablero::Tablero(int maxFila, int maxColumna, int maxAltura) {
	if (maxFila < 1 || maxColumna < 1 || maxAltura < 1) {
		throw "Las coordenadas ingresadas para crear el tablero son inválidas";
	} else {
		this->maxFila = maxFila;
		this->maxColumna = maxColumna;
		this->maxAltura = maxAltura;

		this->casilleros = new Lista<Lista<Lista<Casilla *> *> *>();

		for (int x = 1; x <= maxFila; x++) {
			this->casilleros->add(new Lista<Lista<Casilla *> *>());
			for (int y = 1; y <= maxColumna; y++) {
				this->casilleros->get(x)->add(new Lista<Casilla *>());
				for (int z = 1; z <= maxAltura; z++) {
					this->casilleros->get(x)->get(y)->add(
							new Casilla(x, y, z, GENERAL));
				}
			}
		}
	}
}
Tablero::~Tablero() {
	for (int x = 1; x <= this->maxFila; x++) {
		for (int y = 1; y <= this->maxColumna; y++) {
			for (int z = 1; z <= this->maxAltura; z++) {
				delete this->casilleros->get(x)->get(y)->get(z);
			}
			delete this->casilleros->get(x)->get(y);
		}
		delete this->casilleros->get(x);
	}
	delete[] this->casilleros;
}

bool Tablero::esRangoValido(int fila, int columna, int altura) {
	return (fila >= 1 && columna >= 1 && altura >= 1 && fila <= this->maxFila
			&& columna <= this->maxColumna && altura <= this->maxAltura);
}

Casilla* Tablero::getCasilla(int fila, int columna, int altura) {
	return this->casilleros->get(fila)->get(columna)->get(altura);
}
