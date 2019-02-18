#include<iostream>
#include"rojinegro.h"

using namespace std;

int main(){

	Rojinegro arbol;

	arbol.ins_arbol(100);
	arbol.ins_arbol(150);
	arbol.ins_arbol(50);
	arbol.ins_arbol(120);
	arbol.ins_arbol(170);

	arbol.rotar_izq(arbol.raiz_arbol()->der);

	return 0;
}