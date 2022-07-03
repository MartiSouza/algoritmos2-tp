#ifndef _CASILLA_H
#define _CASILLA_H
#include <string>

#define VACIA "Vacia"
#define INACTIVA "Inactiva"
#define LLENA "Ocupada"

enum EstadoDelCasillero{
	VACIO,
	INACTIVO,
	LLENO,
	MINADO
};

enum TipoDeCasillero{
	AIRE,
	TIERRA,
	AGUA,
	GENERAL
};

class Casilla{

	private:

		unsigned int coordenadaX;
		unsigned int coordenadaY;
		unsigned int coordenadaZ;
		EstadoDelCasillero estadoCasilla;
		TipoDeCasillero tipoDeCasilla;
		std::string estadoActual;



	public:

		/*
		 * Pre: Recibe las coordenadas del tablero y una cantidad de tokens (fichas)
		 * Pos: Crea una casilla
		 */
		Casilla(unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ, TipoDeCasillero tipo);

		/*
		 *Pre: recibe una coordenada que se quiere inicializar y el valor al cual se lo quiere inicializar.
		 *Post: inicializa la coordenada.
		 */
		void setCoordenada(unsigned int &coordenadaAModificar, unsigned int coordenada);
		
		/*
		 * Pre: Recibe un tipo para la casilla (mar, tierra o aire)
		 * Pos: Inicializa el tipo de la casilla según su tipo
		 */
		void setTipoDeCasillero(TipoDeCasillero tipoDeCasilla);
		/*
		* Pos: Devuelve el tipo de casilla
		*/
		TipoDeCasillero getTipoDeCasilla();
		/*
		 * Pos: Devuelve la coordenada X/fila de la casilla
		 */
		unsigned int getCoordenadaX();

		/*
		 * Pos: Devuelve la coordenada Y/columna de la casilla
		 */
		unsigned int getCoordenadaY();

		/*
		 * Pos: Devuelve la coordenada Z/altura de la casilla
		 */
		unsigned int getCoordenadaZ();
		/*
		 * Pos: Devuelve el estado del casillero
		 */
		EstadoDelCasillero getEstado();
		/*
		 * Pre: Necesita un tipo de estado
		 * Pos: Setea el estado del casillero al tipo usado
		 */
		void setEstado(EstadoDelCasillero estado);
		/*
		 * Pos: Setea las coordenadas al casillero si estas son válidas
		 */
		void setCoordenadas ();

		/*
		 * Pre:
		 * Pos: devuelve el estado actual de la casilla
		 */
		std::string getEstadoActual();

};
#endif
