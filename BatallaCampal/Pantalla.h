#ifndef SRC_PANTALLA_H_
#define SRC_PANTALLA_H_
#include <stdlib.h>
#include "BatallaCampal.h"
   
class Pantalla{

	private:

		int opcionUsuario;
		int cantidadJugadores;
		int cantidadSoldados;
		int dimensionDelTablero;
		int mapaOpcion;
		Lista<BMP*>* Window;

	public:

		/*
		 * PRE:
		 * POS: Establece las configuraciones iniciales de una partida, donde la cantidad de jugadores será 2, la cantidad de soldados por jugador 3,
		 * la dimension del tablero 20. Genera un numero aleatorio entre 1 y 3.
		 */
		Pantalla();
		/*
		 * PRE:
		 * POS: Se le pregunta por pantalla al usuario el tipo de partida
		 */
		void nuevaPartida();
		/*
		 * PRE:
		 * POS: devuelve el numero de mapa
		 */
		int mapaElegido();
		/*
		 * PRE:
		 * POS: devuelve la cantidad de jugadores
		 */
		int getCantidadJugadores();
		/*
		 * PRE:
		 * POS: devuelve la cantidad de soldados por jugador
		 */
		int getCantidadSoldados();
		/*
		 * PRE:
		 * POS: devuelve la dimension del tablero
		 */
		int getDimensionDelTablero();
		/*
		 * PRE: Batalla previamente inicializado
		 * POS: pregunta por pantalla al usuario coordenadas de disparo y efectua el mismo
		 */
		void solicitarDisparo(BatallaCampal* batalla);
		/*
		 * PRE: Batalla previamente inicializado y un jugador.
		 * POS: pregunta por pantalla al usuario si quiere mover un soldado y efectua el movimiento
		 */
		void solicitarMovimiento(BatallaCampal* batalla, Jugador* jugador);
		/*
		 * PRE: Batalla previamente inicializado y un jugador.
		 * POS:pregunta al usuario por pantalla si quiere usar una carta
		 */
		void solicitarCarta(BatallaCampal* batalla, Jugador* jugador);
		/*
		 * PRE: Batalla previamente inicializado, una ficha de herramientas y un jugador.
		 * POS: efectua el uso de una herramienta del jugador
		 */
		void usarHerramienta(BatallaCampal* batalla, Ficha* herramientaAux, Jugador* jugador);
		/*
		 * PRE: Batalla previamente inicializado, una carta, un jugador y el numero de carta.
		 * POS: efectua el uso de una carta del jugador
		 */
		void usarUnaCarta(BatallaCampal* batalla, Jugador* jugador);
		/*
		 * PRE: Batalla previamente inicializado y un jugador.
		 * POS: pregunta por pantalla al usuario las coordenadas de un nuevo soldado, si son validas lo agrega.
		 */
		void solicitarSoldados(BatallaCampal* batalla, Jugador* jugador);
		/*
		 * PRE: Batalla previamente inicializado y un puntero a pantalla.
		 * POS: genera la imagen BitMap
		 */
		void generarMapa(BatallaCampal* batalla, Pantalla* pantalla);
		/*
		 * PRE: valores mayores a 0 y menores a la dimension del tablero, el tipo de casillero.
		 * POS: genera un cuadrado en la imagen BitMap
		 */
		void pintarCuadrado(int xi,int yi, int xf, int yf, int z, TipoDeCasillero tipo);
		/*
		 * PRE: tamanio valor mayor a 0
		 * POS: genera Lineas en la imagen BitMap
		 */
		void pintarLineas(int tamanio);
		/*
		 * PRE: valores mayores a 0 y menores a la dimension del tablero
		 * POS: genera un circulo en la imagen BitMap
		 */
		void pintarCirculo(int centerX, int centerY, int z);
		/*
		 * PRE: valores mayores a 0 y menores a la dimension del tablero
		 * POS: genera un circulo rojo en la imagen BitMap
		 */
		void pintarCirculoRojo(int centerX, int centerY, int z);
		/*
		 * PRE:
		 * POS: crea la imagen del BitMap
		 */
		void creacionImagen();

};




#endif /* SRC_PANTALLA_H_ */
