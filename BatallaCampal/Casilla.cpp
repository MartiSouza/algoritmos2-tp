#include "Casilla.h"
#include "Ficha.h"

Casilla::Casilla(unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ, TipoDeCasillero tipo){

	setCoordenada(this->coordenadaX,coordenadaX);
	setCoordenada(this->coordenadaY,coordenadaY);
	setCoordenada(this->coordenadaZ,coordenadaZ);

	setTipoDeCasillero(tipo);
	setEstado(VACIO);
}

void Casilla::setCoordenada(unsigned int &coordenadaAModificar, unsigned int coordenada){
		if(coordenada > 0){
			coordenadaAModificar = coordenada;
		}
		else{
			throw "Las coordenadas de un casillero no pueden ser negativas.";
		}
	}

void Casilla::setTipoDeCasillero(TipoDeCasillero tipo){
	if(tipo == TIERRA || tipo == AGUA || tipo == AIRE || tipo == GENERAL){
		this->tipoDeCasilla = tipo;
	}
	else{
		throw "El tipo de casilla ingresado es inválida. Puede ser: AVION, BARCO, SOLDADO o de tipo uso GENERAL.";
	}
	
}

void Casilla::setEstado(EstadoDelCasillero estadoCasilla){
    if(estadoCasilla == VACIO || estadoCasilla == LLENO || estadoCasilla == INACTIVO){
        this->estadoCasilla = estadoCasilla;
        if(estadoCasilla == VACIO){
        	this->estadoActual = VACIA;
        }else if(estadoCasilla == LLENO){
        	this->estadoActual = LLENA;
        }else if(estadoCasilla == INACTIVO){
        	this->estadoActual = INACTIVA;
        }else if(estadoCasilla == MINADO){
		this->estadoActual == MINADO;
	}
    }
    else{
        throw "El contenido es invalido, debe ser: VACIO, FULL, INACTIVO o MINADO";
    }
}

EstadoDelCasillero Casilla::getEstado(){
	return this->estadoCasilla;
}

TipoDeCasillero Casilla::getTipoDeCasilla(){
    return this->tipoDeCasilla;
}

unsigned int Casilla::getCoordenadaX(){
    return this->coordenadaX;
}

unsigned int Casilla::getCoordenadaY(){
    return this->coordenadaY;
}


unsigned int Casilla::getCoordenadaZ(){
    return this->coordenadaZ;
}

std::string Casilla::getEstadoActual(){
	return this->estadoActual;
}

