#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "BatallaCampal.h"
#include "Pantalla.h"

using namespace std;

int main() {

	try {
		cout << "--BATALLA CAMPAL--" << endl;

		srand(time(NULL));
		bool encontrado;
		Pantalla* pantalla = new Pantalla();
		pantalla->nuevaPartida();
		BatallaCampal* batalla = new BatallaCampal(
				pantalla->getCantidadJugadores(),
				pantalla->getCantidadSoldados(),
				pantalla->getDimensionDelTablero());

		cout << "Se estableció la siguiente configuracion: ("
				<< batalla->getCantidadDeJugadores() << ")jugadores | ("
				<< batalla->getCantidadDeSoldados()
				<< ")soldados por jugador | ("
				<< batalla->getDimensionDelTablero() << ")dimension del tablero"
				<< endl;

		batalla->cargarMapa(pantalla->mapaElegido());
		cout << "Cargando mapa..." << endl;
		pantalla->generarMapa(batalla, pantalla);
		cout << "Mapa cargado" << endl;

		batalla->getJugador()->reiniciarCursor();
		while (batalla->getJugador()->avanzarCursor()) {
			Jugador* jugadorAux = batalla->getJugador()->getCursor();
			pantalla->solicitarSoldados(batalla, jugadorAux);
		}
		cout << "--COMIENZA EL JUEGO--" << endl;

		while (batalla->getEstadoDelJuego() == JUGANDO) {
			cout << "---SIGUIENTE TURNO---" << endl;
			encontrado = false;
			batalla->siguienteTurno();
			batalla->getJugador()->reiniciarCursor();
			while (batalla->getJugador()->avanzarCursor() && (!encontrado)) {
				if (batalla->getJugador()->getCursor()->getId()
						== batalla->getTurno()) {
					encontrado = true;
					Jugador* jugadorAux = batalla->getJugador()->getCursor();

					cout << "Turno del jugador: " << jugadorAux->getId()
							<< endl;
					pantalla->solicitarMovimiento(batalla, jugadorAux);
					pantalla->solicitarDisparo(batalla);
					pantalla->solicitarCarta(batalla, jugadorAux);
				}
			}
			cout << "-----FIN DE TURNO----" << endl;
			batalla->estadoActualDelJuego();
		}
		cout << "-----FIN DEL JUEGO----" << endl;
		cout << "Gana el jugador: " << batalla->getTurno() << endl;

		return 0;

	} catch (const char* X) {
		cout << "ERROR: " << X << endl;
	}
}
