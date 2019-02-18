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
	arbol.ins_arbol(130);
	arbol.ins_arbol(135);

	cout << arbol.raiz_arbol()->color << endl;
	cout << arbol.raiz_arbol()->izq->color << endl;
	cout << arbol.raiz_arbol()->der->color << endl;
	cout << arbol.raiz_arbol()->der->izq->color << endl;
	cout << arbol.raiz_arbol()->der->izq->izq->color << endl;
	cout << arbol.raiz_arbol()->der->izq->der->color << endl;
	cout << arbol.raiz_arbol()->der->der->color << endl;

	return 0;
}