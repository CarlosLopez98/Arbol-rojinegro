#include<iostream>
#include"rojinegro.h"

using namespace std;

int main(){

	Rojinegro arbol;

	arbol.ins_arbol(100);
	arbol.ins_arbol(150);
	arbol.ins_arbol(100);
	arbol.ins_arbol(20);

	arbol.inorden(arbol.raiz_arbol());

	return 0;
}