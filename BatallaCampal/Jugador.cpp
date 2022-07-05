#include "Jugador.h"

using namespace std;

Jugador::Jugador(unsigned int id, int cantidadSoldados) {
	if (id < 1) {
		throw "El id de jugador debe ser un número mayor o igual que uno.";
	}
	if (cantidadSoldados < 1) {
		throw "Cantidad inválida de soldados para el jugador.";
	}

	this->id = id;
	this->cantidadSoldados = cantidadSoldados;
	this->cantidadHerramientas = 0;
	this->herramientas = new Lista<Ficha*>();
	this->soldados = new Lista<Ficha*>();
	this->cartas = new Lista<Carta*>();
	this->estado = EN_BATALLA;
	this->color[0] = 0;
	this->color[1] = 0;
	this->color[2] = 0;
	int randomAux = rand()%2;
		if (randomAux == 0){
			this->color[0] = oscuros[rand()%3];
			this->color[1] = oscuros[rand()%3];
			this->color[2] = oscuros[rand()%3];
		}else if (randomAux == 1){
			this->color[0] = claros[rand()%3];
			this->color[1] = claros[rand()%3];
			this->color[2] = claros[rand()%3];
		}
	if (color [0] == 0 && color [1] == 0 && color [2] == 255){
		color[2] = 0;
	}
}

unsigned int Jugador::getCantidadDeHerramientas() {
	return this->herramientas->contarElementos();
}

int Jugador::getCantidadDeSoldados() {
	return this->soldados->contarElementos();
}

unsigned int Jugador::getCantidadDeCartas() {
	return this->cartas->contarElementos();
}

Lista<Ficha*>* Jugador::getHerramienta() {
	return this->herramientas;
}

Lista<Ficha*>* Jugador::getSoldado() {
	return this->soldados;
}

Lista<Carta*>* Jugador::getCarta() {
	return this->cartas;
}

unsigned int Jugador::buscarIdSoldado(int fila, int columna) {
	if (fila < 1 || columna < 1) {
		throw "No se puede buscar un soldado en una fila o columna que no tenga valor al menos 1.";
	}

	bool encontrado = false;
	this->soldados->reiniciarCursor();
	int id = 0;
	while (this->soldados->avanzarCursor() && (!encontrado)) {
		id++;
		if (this->soldados->getCursor()->getPosicionX() == fila
				&& this->soldados->getCursor()->getPosicionY() == columna) {
			encontrado = true;

		}
	}
	return id;
}

int Jugador::buscarIdHerramienta(int fila, int columna) {
	if (fila < 1 || columna < 1) {
		throw "No se puede buscar un soldado en una fila o columna que no tenga valor al menos 1.";
	}
	bool herramientaEncontrada = false;
	int idHerramienta = 0;
	while (this->herramientas->avanzarCursor() && (!herramientaEncontrada)) {
		idHerramienta++;
		if (this->herramientas->getCursor()->getPosicionX() == fila
				&& this->herramientas->getCursor()->getPosicionY() == columna) {

			herramientaEncontrada = true;
		}
	}
	return idHerramienta;
}

bool Jugador::buscarSoldado(int fila, int columna) {
	bool encontrado = false;
	this->soldados->reiniciarCursor();
	while (this->soldados->avanzarCursor() && (!encontrado)) {
		if (this->soldados->getCursor()->getPosicionX() == fila
				&& this->soldados->getCursor()->getPosicionY() == columna) {
			return this->soldados->getCursor();
			encontrado = true;
		}
	}
	return encontrado;
}

bool Jugador::buscarHerramienta(int fila, int columna) {
	bool HerramientaEncontrada = false;
	this->herramientas->reiniciarCursor();
	while (this->herramientas->avanzarCursor() && (!HerramientaEncontrada)) {
		if (this->herramientas->getCursor()->getPosicionX() == fila
				&& this->herramientas->getCursor()->getPosicionY() == columna) {
			return this->herramientas->getCursor();
			HerramientaEncontrada = true;
		}
	}
	return HerramientaEncontrada;

}

void Jugador::setEstado(EstadoJugador estado) {
	if (estado != EN_BATALLA && estado != ELIMINADO) {
		throw "El estado del jugador ingresado es inválido";
	}
	this->estado = estado;
}

EstadoJugador Jugador::getEstadoJugador() {
	return this->estado;
}

void Jugador::nuevaCarta(int aleatorio) {
	if (aleatorio < 0) {
		throw "El número de carta no puede ser negativo";
	}

	if (this->cartas->contarElementos() < MAX_CARTAS) {
		this->cartas->add(new Carta(aleatorio));
	}
}

unsigned int Jugador::getId() {
	return this->id;
}

void Jugador::nuevoSoldado(int fila, int columna) {
	if (fila < 1 || columna < 1) {
		throw "No se puede agregar un soldado en una fila o columna que no tenga valor al menos 1.";
	}

	this->soldados->add(new Ficha(SOLDADO, fila, columna, 1));
}

void Jugador::nuevaHerramienta(char ficha, int fila, int columna, int altura) {
	if (fila < 1 || columna < 1 || altura < 1) {
		throw "No se puede agregar una herramienta en coordenadas inválidas.";
	}

	if (this->cartas->contarElementos() < MAX_HERRAMIENTAS) {
		this->herramientas->add(new Ficha(ficha, fila, columna, altura));
	} else {
		throw "No se pueden poner mas herramientas";
	}
}

void Jugador::eliminarSoldado(int fila, int columna) {
	if (fila < 1 || columna < 1) {
		throw "No se puede eliminar un soldado en una posición inválida. La fila y la columna deben ser mayor o igual a 1.";
	}

	this->soldados->remover(this->buscarIdSoldado(fila, columna));
	this->cantidadSoldados--;
}

void Jugador::eliminarCarta(int id) {
	if (id < 0) {
		throw "No se pudo eliminar la carta, el id ingresado es inválido.";
	}
	this->cartas->remover(id);
}

void Jugador::eliminarHerramienta(int id) {
	if (id < 0) {
		throw "No se pudo eliminar la herramientas, el id ingresado es inválido.";
	}
	this->herramientas->remover(id);
}

Jugador::~Jugador() {
	if (this->soldados) {
		for (int i = 1; i < this->getCantidadDeSoldados(); i++) {
			this->soldados->remover(i);
		}
		delete[] this->soldados;
	}
	if (this->herramientas) {
		for (unsigned int i = 1; i < this->getCantidadDeHerramientas(); i++) {
			this->herramientas->remover(i);
		}
		delete[] this->herramientas;
	}
	if (this->cartas) {
		for (unsigned int i = 0; i < this->getCantidadDeCartas(); i++) {
			this->cartas->remover(i);
		}
		delete[] this->cartas;
	}
}

