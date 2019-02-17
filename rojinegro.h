#include"arbol.h"

#ifndef ROJINEGRO_H
#define ROJINEGRO_H

class Rojinegro : public Arbol {

	private:

	public:
		Rojinegro();
		~Rojinegro();

		void rotarDerecha(NODO);
		void rotarIzquierda(NODO);
		void insertar(int);
		void eliminar(int);

};

Rojinegro::Rojinegro(){}
Rojinegro::~Rojinegro(){}

void Rojinegro::insertar(int dato){
	this->ins_arbol(dato);

	// Correccion
	if (raiz->der==raiz->izq==NULL){
		raiz->color = true;
	}
}

void Rojinegro::rotarIzquierda(NODO padre){
	NODO **aux = &raiz;
    if(p->padre!=NULL && p->padre->dcho==p)
        aux=&(p->padre->dcho);
    else if(p->padre!=NULL && p->padre->izdo==p)
        aux=&(p->padre->izdo);

    *aux=p->dcho;
    (*aux)->padre=p->padre;
    p->padre=*aux;
    p->dcho=(*aux)->izdo;
    (*aux)->izdo=p;

    if(p->dcho!=NULL) p->dcho->padre=p;
}

#endif