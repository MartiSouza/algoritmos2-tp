#include "BatallaCampal.h"

BatallaCampal::BatallaCampal(unsigned int cantidadJugadores,
		unsigned int cantidadSoldados, int dimensionTablero) {

	this->estadoDelJuegoActual = JUGANDO;
	this->turno = 0;
	this->eliminadoPorMina = false;
	this->huboCuerpoACuerpo = false;
	
	if (cantidadJugadores < MIN_JUGADORES || cantidadJugadores > MAX_JUGADORES) {
		throw "La cantidad de jugadores elegida es invalida.";
	} else {
		this->cantidadJugadores = cantidadJugadores;
	}
	if (cantidadSoldados < MIN_SOLDADOS || cantidadSoldados > MAX_SOLDADOS) {
		throw "La cantidad de soldados elegida es invalida.";
	} else {
		this->cantidadSoldados = cantidadSoldados;
	}
	if (dimensionTablero < MIN_DIMENSION || dimensionTablero > MAX_DIMENSION) {
		throw "La dimension elegida para el tablero es invalida.";
	} else {
		this->dimensionTablero = dimensionTablero;
	}

	this->jugadores = new Lista<Jugador*>();

	for (unsigned int i = 1; i <= cantidadJugadores; i++) {
		this->jugadores->add(new Jugador(i, cantidadSoldados));
	}

	this->tablero = new Tablero(this->dimensionTablero, this->dimensionTablero,
			this->dimensionTablero);

}

void BatallaCampal::estadoActualDelJuego() {
	if (this->jugadores) {

		int id = 0;

		this->jugadores->reiniciarCursor();
		while (this->jugadores->avanzarCursor()) {
			id++;
			if (this->jugadores->getCursor()->getCantidadDeSoldados() == 0) {
				this->jugadores->remover(id);
			}
		}
		if (this->jugadores->contarElementos() == 1) {
			this->estadoDelJuegoActual = FINALIZADO;

		} else {
			this->estadoDelJuegoActual = JUGANDO;
		}
	}
}

void BatallaCampal::siguienteTurno() {
	if (this->turno < this->jugadores->contarElementos()) {
		this->turno++;
	} else {
		this->turno = 1;
	}
}

bool BatallaCampal::esCoordenadaValida(int fila, int columna) {
	return (fila >= 0 && columna >= 0 && fila <= this->getDimensionDelTablero()
			&& columna <= this->getDimensionDelTablero());
}

bool BatallaCampal::esCoordenadaValida(int fila, int columna, int altura) {
	return (fila >= 0 && columna >= 0 && altura >= 0
			&& fila <= this->getDimensionDelTablero()
			&& columna <= this->getDimensionDelTablero()
			&& altura <= this->getDimensionDelTablero());
}

void BatallaCampal::realizarDisparo(int fila, int columna, int altura) {
	if (!esCoordenadaValida(fila, columna, altura)) {
		throw "Las magnitudes elegidas para realizar el disparo no son validas.";
	}

	this->tablero->getCasilla(fila, columna, altura)->setEstado(INACTIVO);

	this->jugadores->reiniciarCursor();
	while (this->jugadores->avanzarCursor()) {
		if (this->jugadores->getCursor()->buscarSoldado(fila, columna)) {
			this->jugadores->getCursor()->eliminarSoldado(fila, columna);
		}
		if (this->jugadores->getCursor()->buscarHerramienta(fila, columna)) {
			this->jugadores->getCursor()->eliminarHerramienta(
					this->jugadores->getCursor()->buscarIdHerramienta(fila,
							columna));
		}
	}
}

bool BatallaCampal::soldadosCoincidenDistinto(int fila, int columna) {
	if (!esCoordenadaValida(fila, columna)) {
		throw "Las magnitudes elegidas para comparar a los soldados no son validas.";
	}

	bool coinciden = false;
	bool corte = false;
	this->jugadores->reiniciarCursor();
	while (this->jugadores->avanzarCursor() && (!corte)) {
		if (this->jugadores->getCursor()->getId() != this->turno) {
			corte = true;
			this->jugadores->getCursor()->getSoldado()->reiniciarCursor();
			while (this->jugadores->getCursor()->getSoldado()->avanzarCursor()) {
				if (this->jugadores->getCursor()->getSoldado()->getCursor()->getPosicionX()
						== fila
						&& this->jugadores->getCursor()->getSoldado()->getCursor()->getPosicionY()
								== columna) {
					coinciden = true;
				}
			}
		}
	}
	return coinciden;
}

bool BatallaCampal::soldadosCoinciden(int fila, int columna) {
	if (!esCoordenadaValida(fila, columna)) {
		throw "Las magnitudes elegidas para comparar a los soldados no son validas.";
	}

	bool coinciden = false;
	bool corte = false;
	this->jugadores->reiniciarCursor();
	while (this->jugadores->avanzarCursor() && (!corte)) {
		if (this->jugadores->getCursor()->getId() == this->turno) {
			corte = true;
			this->jugadores->getCursor()->getSoldado()->reiniciarCursor();
			while (this->jugadores->getCursor()->getSoldado()->avanzarCursor()) {
				if (this->jugadores->getCursor()->getSoldado()->getCursor()->getPosicionX()
						== fila
						&& this->jugadores->getCursor()->getSoldado()->getCursor()->getPosicionY()
								== columna) {
					coinciden = true;
				}
			}
		}
	}
	return coinciden;
}

bool BatallaCampal::eliminarEnemigo(int fila, int columna) {
	if (!esCoordenadaValida(fila, columna)) {
		throw "Las magnitudes elegidas para eliminar al soldado enemigo no son validas.";
	}

	bool enemigoMuerto = false;
	this->jugadores->reiniciarCursor();
	while (this->jugadores->avanzarCursor()) {
		if (this->jugadores->getCursor()->getId() != this->turno) {
			this->jugadores->getCursor()->getSoldado()->reiniciarCursor();
			while (this->jugadores->getCursor()->getSoldado()->avanzarCursor()) {
				if (this->jugadores->getCursor()->getSoldado()->getCursor()->getPosicionX()
						== fila
						&& this->jugadores->getCursor()->getSoldado()->getCursor()->getPosicionY()
								== columna) {
					enemigoMuerto = true;
				}
			}
		}
	}
	return enemigoMuerto;
}

void BatallaCampal::realizarMovimiento(char movimiento, int fila, int columna,
		Ficha* soldadoAux) {

	switch (movimiento) {
	case ARRIBA:
		if (this->tablero->getCasilla(fila - 1, columna, 1)->getTipoDeCasilla()
				== TIERRA
				&& this->tablero->getCasilla(fila - 1, columna, 1)->getEstado()
						!= INACTIVO && (fila - 1) > 0
				&& fila < this->getDimensionDelTablero()) {

			soldadoAux->setCoordenadasSoldado(fila - 1, columna);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	case ABAJO:
		if (this->tablero->getCasilla(fila + 1, columna, 1)->getTipoDeCasilla()
				== TIERRA
				&& this->tablero->getCasilla(fila + 1, columna, 1)->getEstado()
						!= INACTIVO && (fila + 1) > 0
				&& fila < this->getDimensionDelTablero()) {

			soldadoAux->setCoordenadasSoldado(fila + 1, columna);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	case IZQUIERDA:
		if (this->tablero->getCasilla(fila, columna - 1, 1)->getTipoDeCasilla()
				== TIERRA
				&& this->tablero->getCasilla(fila, columna - 1, 1)->getEstado()
						!= INACTIVO && (columna - 1) > 0
				&& columna < this->getDimensionDelTablero()) {

			soldadoAux->setCoordenadasSoldado(fila, columna - 1);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	case DERECHA:
		if (this->tablero->getCasilla(fila, columna + 1, 1)->getTipoDeCasilla()
				== TIERRA
				&& this->tablero->getCasilla(fila, columna + 1, 1)->getEstado()
						!= INACTIVO && (columna + 1) > 0
				&& columna < this->getDimensionDelTablero()) {

			soldadoAux->setCoordenadasSoldado(fila, columna + 1);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	case DIAGONAL_SUP_IZQ:
		if ((this->tablero->getCasilla(fila - 1, columna - 1, 1)->getTipoDeCasilla()
				== TIERRA)
				&& (this->tablero->getCasilla(fila - 1, columna - 1, 1)->getEstado()
						!= INACTIVO) && ((columna - 1) > 0)
				&& ((columna - 1) < this->getDimensionDelTablero())
				&& ((fila - 1) > 0)
				&& ((fila - 1) < this->getDimensionDelTablero())) {

			soldadoAux->setCoordenadasSoldado(fila - 1, columna - 1);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	case DIAGONAL_SUP_DER:
		if (this->tablero->getCasilla(fila + 1, columna - 1, 1)->getTipoDeCasilla()
				== TIERRA
				&& this->tablero->getCasilla(fila + 1, columna - 1, 1)->getEstado()
						!= INACTIVO && (columna - 1) > 0
				&& columna - 1 < this->getDimensionDelTablero()
				&& (fila + 1 > 0)
				&& (fila + 1) < this->getDimensionDelTablero()) {

			soldadoAux->setCoordenadasSoldado(fila + 1, columna - 1);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	case DIAGONAL_INF_IZQ:
		if (this->tablero->getCasilla(fila - 1, columna + 1, 1)->getTipoDeCasilla()
				== TIERRA
				&& this->tablero->getCasilla(fila - 1, columna + 1, 1)->getEstado()
						!= INACTIVO && (columna + 1) > 0
				&& columna + 1 < this->getDimensionDelTablero()
				&& (fila - 1 > 0)
				&& (fila - 1) < this->getDimensionDelTablero()) {

			soldadoAux->setCoordenadasSoldado(fila - 1, columna + 1);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	case DIAGONAL_INF_DER:
		if (this->tablero->getCasilla(fila + 1, columna + 1, 1)->getTipoDeCasilla()
				== TIERRA
				&& this->tablero->getCasilla(fila + 1, columna + 1, 1)->getEstado()
						!= INACTIVO && (columna + 1) > 0
				&& columna + 1 < this->getDimensionDelTablero()
				&& (fila + 1 > 0)
				&& (fila + 1) < this->getDimensionDelTablero()) {

			soldadoAux->setCoordenadasSoldado(fila + 1, columna + 1);
		} else {
			throw "Movimiento invalido.";
		}
		break;
	}
}
Ficha* BatallaCampal::moverSoldado(char movimiento, int fila, int columna,
		Jugador* jugador) {
	if (!esCoordenadaValida(fila, columna)) {
		throw "Las magnitudes elegidas para mover al soldado no son validas.";
	}
	if (movimiento != ARRIBA && movimiento != ABAJO && movimiento != IZQUIERDA
			&& movimiento != DERECHA && movimiento != DIAGONAL_SUP_IZQ
			&& movimiento != DIAGONAL_SUP_DER && movimiento != DIAGONAL_INF_IZQ
			&& movimiento != DIAGONAL_INF_DER) {
		throw "El movimiento elegido no es valido";
	}

	Ficha* soldadoAux = NULL;

	jugador->getSoldado()->reiniciarCursor();
	while (jugador->getSoldado()->avanzarCursor()) {
		if (jugador->getSoldado()->getCursor()->getPosicionX() == fila
				&& jugador->getSoldado()->getCursor()->getPosicionY()
						== columna) {
			soldadoAux = jugador->getSoldado()->getCursor();

			realizarMovimiento(movimiento, fila, columna, soldadoAux);

			if (this->soldadosCoincidenDistinto(soldadoAux->getPosicionX(),
					soldadoAux->getPosicionY())) {

				this->tablero->getCasilla(soldadoAux->getPosicionX(),
						soldadoAux->getPosicionY(), 1)->setEstado(INACTIVO);
				this->realizarDisparo(soldadoAux->getPosicionX(),
						soldadoAux->getPosicionY(), 1);
				this->huboCuerpoACuerpo = true;
			}

			if (this->tablero->getCasilla(soldadoAux->getPosicionX(),
					soldadoAux->getPosicionY(), 1)->getEstado() == MINADO) {
				this->tablero->getCasilla(soldadoAux->getPosicionX(),
						soldadoAux->getPosicionY(), 1)->setEstado(INACTIVO);
				this->realizarDisparo(soldadoAux->getPosicionX(),
						soldadoAux->getPosicionY(), 1);
				this->eliminadoPorMina = true;
			}

			return soldadoAux;
		} 
			
	}
	return soldadoAux;
}

void BatallaCampal::dispararMisil(int fila, int columna, int altura) {
	if (!esCoordenadaValida(fila, columna, altura)) {
		throw "Las magnitudes elegidas para disparar el misil no son validas.";
	}
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if ((fila + i) > 0 && (columna + j) > 0 && (altura + k) > 0
						&& (fila + i) <= this->getDimensionDelTablero()
						&& (columna + j) <= this->getDimensionDelTablero()
						&& (altura + k) <= this->getDimensionDelTablero()) {
					this->tablero->getCasilla(fila + i, columna + j, altura + k)->setEstado(
							INACTIVO);
					this->realizarDisparo(fila + i, columna + j, altura + k);
				}
			}
		}
	}
}

int BatallaCampal::usarRadar(int fila, int columna, int altura) {
	if (!esCoordenadaValida(fila, columna, altura)) {
		throw "Las magnitudes elegidas para usar el radar no son validas.";
	}

	int contador = 0;
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			for (int k = -2; k <= 2; k++) {
				if ((fila + i) > 0 && (columna + j) > 0 && (altura + k) > 0
						&& (fila + i) <= this->getDimensionDelTablero()
						&& (columna + j) <= this->getDimensionDelTablero()
						&& (altura + k) <= this->getDimensionDelTablero()) {
					if (this->tablero->getCasilla(fila + i, columna + j,
							altura + k)->getEstado() == LLENO) {
						contador++;
					}
				}
			}
		}
	}
	return contador;
}

void BatallaCampal::dispararSuperMisil(int filaOcolumna, char tipoDeCasilla) {
	if (filaOcolumna < 1 || filaOcolumna > this->dimensionTablero) {
		throw "La fila o columna elegida para disparar el super misil no es valida.";
	}
	if (tipoDeCasilla == 'C') {
		for (int i = 1; i <= this->getDimensionDelTablero(); i++) {
			for (int k = 1; k <= this->getDimensionDelTablero(); k++) {
				this->tablero->getCasilla(i, filaOcolumna, k)->setEstado(
						INACTIVO);
				this->realizarDisparo(i, filaOcolumna, k);
			}
		}
	} else if (tipoDeCasilla == 'F') {
		for (int i = 1; i <= this->getDimensionDelTablero(); i++) {
			for (int k = 1; k <= this->getDimensionDelTablero(); k++) {
				this->tablero->getCasilla(filaOcolumna, i, k)->setEstado(
						INACTIVO);
				this->realizarDisparo(filaOcolumna, i, k);
			}
		}
	}
}

void BatallaCampal::iniciarEscenarioUno() {
	for (int x = 1; x <= this->getDimensionDelTablero(); x++) {
		for (int y = 1; y <= this->getDimensionDelTablero(); y++) {
			for (int z = 1; z <= this->getDimensionDelTablero(); z++) {

				if (z == 1) {

					if (x < y) {
						this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
								TIERRA);
					} else {
						this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
								AGUA);
					}
				} else {
					this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
							AIRE);
				}
			}
		}
	}
}

void BatallaCampal::iniciarEscenarioDos() {
	for (int x = 1; x <= this->getDimensionDelTablero(); x++) {
		for (int y = 1; y <= this->getDimensionDelTablero(); y++) {
			for (int z = 1; z <= this->getDimensionDelTablero(); z++) {

				if (z == 1) {

					if (x > y) {
						this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
								TIERRA);
					} else {
						this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
								AGUA);
					}
				} else {
					this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
							AIRE);
				}
			}
		}
	}
}

void BatallaCampal::iniciarEscenarioTres() {
	for (int x = 1; x <= this->getDimensionDelTablero(); x++) {
		for (int y = 1; y <= this->getDimensionDelTablero(); y++) {
			for (int z = 1; z <= this->getDimensionDelTablero(); z++) {

				if (z == 1) {

					if (x != y && (x - y) != 2 && (x - y) != 1 && (y - x) != 1
							&& (y - x) != 2) {
						this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
								TIERRA);
					} else {
						this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
								AGUA);
					}
				} else {
					this->tablero->getCasilla(x, y, z)->setTipoDeCasillero(
							AIRE);
				}
			}
		}
	}
}

void BatallaCampal::cargarMapa(int opcion) {
	if (opcion == 1) {
		this->iniciarEscenarioUno();
	} else if (opcion == 2) {
		this->iniciarEscenarioDos();
	} else {
		this->iniciarEscenarioTres();
	}
}

void BatallaCampal::usarCarta(Jugador* jugador, int numero, int x, int y, int z,
		char filaOColumna) {
	if (!esCoordenadaValida(x, y, z)) {
		throw "Las magnitudes elegidas para usar la carta elegida no son validas.";
	}
	if (jugador->getCarta()->get(numero)->getTipoDeCarta() == AVIONES) {
		if (this->tablero->getCasilla(x, y, z)->getTipoDeCasilla() != AIRE) {
			throw "Avion debe estar en el aire";
		} else if (esCoordenadaValida(x, y, z)) {
			jugador->nuevaHerramienta(AVION, x, y, z);
			this->tablero->getCasilla(x, y, z)->setEstado(LLENO);
		}
	}
	if (jugador->getCarta()->get(numero)->getTipoDeCarta() == BARCOS) {
		if (this->tablero->getCasilla(x, y, z)->getTipoDeCasilla() != AGUA) {
			throw "Barco debe estar en el agua";
		} else if (esCoordenadaValida(x, y, z)) {
			jugador->nuevaHerramienta(BARCO, x, y, 1);
			this->tablero->getCasilla(x, y, z)->setEstado(LLENO);
		}
	}
	if (jugador->getCarta()->get(numero)->getTipoDeCarta() == MINAS) {
		if (this->tablero->getCasilla(x, y, z)->getTipoDeCasilla() != TIERRA) {
			throw "Mina debe estar en la tierra";
		} else if (esCoordenadaValida(x, y, 1)) {
			jugador->nuevaHerramienta(MINA, x, y, 1);
			this->tablero->getCasilla(x, y, 1)->setEstado(MINADO);
		}
	}
	if (jugador->getCarta()->get(numero)->getTipoDeCarta() == MISIL) {
		if (esCoordenadaValida(x, y, z)
				&& esCoordenadaValida(x + 1, y + 1, z + 1)
				&& esCoordenadaValida(x - 1, y - 1, z - 1)) {
			dispararMisil(x, y, z);
		}
	}
	if (jugador->getCarta()->get(numero)->getTipoDeCarta() == SUPER) {
		if ((filaOColumna != 'C') && (filaOColumna != 'F')) {
			throw "se ingreso una letra distinta de C o F";
		}

		if (filaOColumna == 'C') {
			dispararSuperMisil(y, filaOColumna);
		} else if (filaOColumna == 'F') {
			dispararSuperMisil(x, filaOColumna);
		}
	}
}

Tablero* BatallaCampal::getTablero() {
	return this->tablero;
}

int BatallaCampal::getCantidadDeJugadores() {
	return this->cantidadJugadores;
}

int BatallaCampal::getCantidadDeSoldados() {
	return this->cantidadSoldados;
}

int BatallaCampal::getDimensionDelTablero() {
	return this->dimensionTablero;
}

estadoDelJuego BatallaCampal::getEstadoDelJuego() {
	return this->estadoDelJuegoActual;
}

unsigned int BatallaCampal::getTurno() {
	return this->turno;
}

Lista<Jugador*>* BatallaCampal::getJugador() {
	return this->jugadores;
}

BatallaCampal::~BatallaCampal() {
	if (this->jugadores) {
		for (unsigned int i = 1; i <= this->jugadores->contarElementos(); i++) {
			if (this->jugadores->get(i) != NULL) {
				this->jugadores->remover(i);
			}
		}
		delete this->jugadores;
	}
	if (tablero) {
		delete tablero;
	}
}

bool BatallaCampal::seEliminoPorMina() {
	return this->eliminadoPorMina;
}

bool BatallaCampal::seEncontraronRivales(){
	return this->huboCuerpoACuerpo;
}
