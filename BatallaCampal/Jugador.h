#ifndef JUGADOR_H
#define JUGADOR_H
#include "Lista.h"
#include "Ficha.h"
#include "Carta.h"
#define MAX_CARTAS 5
#define MAX_HERRAMIENTAS 7

enum EstadoJugador {
	ELIMINADO, EN_BATALLA
};

class Jugador {

private:
	unsigned int id;
	unsigned int cantidadSoldados;
	unsigned int cantidadHerramientas;
	Lista<Ficha*>* herramientas;
	Lista<Ficha*>* soldados;
	Lista<Carta*>* cartas;
	EstadoJugador estado;
	int color[3];
	int claros[3] = {0, 102, 51};
	int oscuros[3] = {0, 255, 127};

public:
	/*
	 *Pre: -
	 *Post: crea un jugador con su respectivo id, la cantidad de soldados que posee y las cartas en su mazo.
	 */
	Jugador(unsigned int id, int cantidadSoldados);
	/*
	 *Pre: -
	 *Post: destruye la instancia de jugador.
	 */
	virtual ~Jugador();
	/*
	 *Pre: -
	 *Post: devuelve el numero rojo del RGB.
	 */
	int getColorR();
	/*
	 *Pre: -
	 *Post: devuelve el numero verde del RGB.
	 */
	int getColorG();
	/*
	 *Pre: -
	 *Post: devuelve el numero azul del RGB.
	 */
	int getColorB();
	/*
	 *Pre: -
	 *Post: devuelve la cantidad de herramientas.
	 */	
	unsigned int getCantidadDeHerramientas();
	/*
	 *Pre: -
	 *Post: devuelve la cantidad de soldados.
	 */
	int getCantidadDeSoldados();
	/*
	 *Pre: -
	 *Post: devuelve la cantidad de cartas.
	 */
	unsigned int getCantidadDeCartas();
	/*
	 *Pre: recibe un id de ficha
	 *Post: devuelve la ficha.
	 */
	Lista<Ficha*>* getHerramienta();
	/*
	 *Pre: -
	 *Post: devuelve un soldado de la lista de soldados.
	 */
	Lista<Ficha*>* getSoldado();
	/*
	 *Pre:
	 *Post: devuelve una carta de la lista de cartas.
	 */
	Lista<Carta*>* getCarta();
	/*
	 *Pre: recibe un id de una herramienta
	 *Post: elimina la herramienta de la lista de herramientas del jugador.
	 */
	void eliminarHerramienta(int id);
	/*
	 *Pre: recibe un estado
	 *Post: cambiar el estado al jugador
	 */
	void setEstado(EstadoJugador estado);
	/*
	 *Pre:
	 *Post: devuelve el estado actual del jugador
	 */
	EstadoJugador getEstadoJugador();
	/*
	 *Pre: recibe un numero aleatorio
	 *Post: agrega una carta a la lista de cartas
	 */
	void nuevaCarta(int aleatorio);
	/*
	 *Pre:
	 *Post: devuelve el id del jugador
	 */
	unsigned int getId();
	/*
	 *Pre: recibe una coordenada en X e Y
	 *Post: agrega un nuevo soldado a la lista
	 */
	void nuevoSoldado(int fila, int columna);
	/*
	 *Pre: recibe posicion de ficha y columna
	 *Post: elimina un soldado de la lista
	 */
	void eliminarSoldado(int fila, int columna);
	/*
	 *Pre: recibe una ficha y su posicion en fila,columna y altura
	 *Post: agrega una nueva herramienta a la lista de herramienta del jugador
	 */
	void nuevaHerramienta(char FICHA, int fila, int columna, int altura);
	/*
	 *Pre: recibe un id
	 *Post: elimina una carta de la lista de cartas
	 */
	void eliminarCarta(int id);
	/*
	 *Pre: recibe posicion de fila y columna
	 *Post: si encuentra un soldado coincidente con las coordenadas devuelve true
	 */
	bool buscarSoldado(int fila, int columna);
	/*
	 *Pre: recibe posicion de fila y columna
	 *Post: si encuentra un id coincidente con las coordenadas devuelve unsigned int
	 */
	unsigned int buscarIdSoldado(int fila, int columna);

	/*
	 *Pre: recibe posicion de fila y columna
	 *Post: devuelve si encuentra una herramienta en las coordenadas
	 */
	bool buscarHerramienta(int fila, int columna);

	/*
	 *Pre: recibe posicion de fila y columna
	 *Post: devuelve el numero si coincide la herramienta con las coordenadas
	 */
	int buscarIdHerramienta(int fila, int columna);
};

#endif
