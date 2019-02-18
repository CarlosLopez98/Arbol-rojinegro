#ifndef ROJINEGRO_H
#define ROJINEGRO_H

using namespace std;

struct nodo{ 
	int dato;
	bool color; // 0 rojo - 1 negro
	nodo *padre, *izq, *der;
};

class Rojinegro{
	nodo *raiz, *centinela;

	public:
		Rojinegro(){
			raiz = NULL;
			centinela = new nodo;
			centinela->dato = 0;
			centinela->color = 1;
			centinela->izq = centinela->der = centinela->padre = NULL;
		}
		~Rojinegro();

		nodo* raiz_arbol(){
			return raiz;
		}

		int ins_arbol (int);
		nodo* buscar_arbol (int, nodo*, nodo*);
		void borrar_nodo(nodo*, nodo*);
		nodo* buscar(int, nodo**, nodo*);
		int retira_arbol(int);
		void inorden(nodo*);
		void preorden(nodo*);
		void posorden(nodo*);
		void destruir (nodo*);

		void rotar_izq(nodo*);
		void rotar_der(nodo*);

		void ajustarInsercion(nodo*);
		void ajustarSupresion(nodo*);

		nodo* abuelo(nodo*);
		nodo* tio(nodo*);
};

nodo* Rojinegro::buscar_arbol(int dato, nodo *hijo, nodo *padre){
	if(hijo == NULL) return padre;
	if(dato < hijo->dato){
		padre = hijo;
		padre = buscar_arbol(dato, hijo->izq, padre);
		return padre;
	}else if(dato > hijo->dato){
		padre = hijo;
		padre = buscar_arbol(dato, hijo->der, padre);
		return padre;
	}else{
		return NULL;
	}
}

int Rojinegro::ins_arbol(int dato){
	nodo *padre;
	if(raiz == NULL){
		raiz = new nodo;
		raiz->dato = dato;
		raiz->color = 1;
		raiz->izq = raiz->der = raiz->padre = NULL;
		return 0;
	}

	padre = buscar_arbol(dato, raiz, NULL);
	if(padre == NULL) return -1;
	nodo *nuevo;
	nuevo = new nodo;
	nuevo->dato = dato;
	nuevo->color = 0;
	nuevo->izq = nuevo->der = NULL;
	nuevo->padre = padre;

	if(dato<padre->dato)
        padre->izq = nuevo;
    else
     	padre->der = nuevo;

    // Correccion
    if(padre->color == 0) ajustarInsercion(nuevo);

    return 0;
}

void Rojinegro::borrar_nodo(nodo *padre, nodo *hijo){
	nodo *r, *s, *t;
	if (hijo->izq==NULL) r=hijo->der;
	else if (hijo->der==NULL) r=hijo->izq;
	else{
		s =hijo;
		r=hijo->der;
		t=r->izq;
		while(t!=NULL){
			s=r;
			r=t;
			t=t->izq;
		}
		if(hijo!=s){
	    	s->izq=r->der;
    		r->der=hijo->der;
    	}
		r->izq =hijo->izq;
	}

	if (padre==NULL) raiz= r;
	else if (hijo==padre->izq) padre->izq =r;
	else padre->der = r;

	if(hijo->color == 1) ajustarSupresion(hijo);

	delete hijo;
}

nodo *Rojinegro::buscar(int n, nodo **hijo, nodo *padre){
	if(*hijo==NULL) return NULL;
	if (n <(*hijo)->dato){
		padre=*hijo;
		*hijo=(*hijo)->izq;
		padre=buscar(n,hijo,padre);
		return padre;
	}else if (n>(*hijo)->dato){
		padre=*hijo;
		*hijo=(*hijo)->der;
		padre =buscar(n,hijo,padre);
		return padre;
	}else return padre;

}

int Rojinegro::retira_arbol(int n){
	nodo *padre, *hijo=raiz;
	padre = buscar(n,&hijo,NULL);
	if(hijo==NULL) return -1;
	borrar_nodo(padre,hijo);
	return 0;
}

void Rojinegro::inorden(nodo *hijo){
	if(hijo!=NULL){
		inorden(hijo->izq);
		cout<<hijo->dato<<endl;
        inorden(hijo->der);
    }
}

void Rojinegro::preorden(nodo *hijo){
	if (hijo!=NULL){
       cout<<hijo->dato<<endl;
       preorden(hijo->izq);
       preorden(hijo->der);
   }
}

void Rojinegro::posorden(nodo *hijo){
	if (hijo!=NULL){
       posorden(hijo->izq);
       posorden(hijo->der);
      cout<<hijo->dato<<endl;
  }
}

void Rojinegro::destruir(nodo *hijo){
	if (hijo!=NULL){
    	destruir(hijo->izq);
    	destruir(hijo->der);
    	delete hijo;
    	//cout<<"nodo destruido..."<< endl;
    }
}

Rojinegro::~Rojinegro( ) {
	destruir(raiz);
}

void Rojinegro::rotar_izq(nodo* pivote){
	nodo *aux = raiz;
	if(pivote->padre != NULL && pivote->padre->der == pivote){
		aux = pivote->padre->der;
		pivote->padre->der = aux->der;
	}else if(pivote->padre != NULL && pivote->padre->izq == pivote){
		aux = pivote->padre->izq;
		pivote->padre->izq = aux->der;
	}

	aux = pivote->der;
	aux->padre = pivote->padre;
	pivote->padre = aux;
	pivote->der = aux->izq;
	aux->izq = pivote;

	if(pivote->der != NULL) pivote->der->padre = pivote;
	if(aux->padre == NULL) raiz = aux;
}

void Rojinegro::rotar_der(nodo* pivote){
	nodo *aux = raiz;
	if(pivote->padre != NULL && pivote->padre->izq == pivote){
		aux = pivote->padre->izq;
		pivote->padre->der = aux->der;
	}else if(pivote->padre != NULL && pivote->padre->der == pivote){
		aux = pivote->padre->der;
		pivote->padre->izq = aux->der;
	}

	aux = pivote->izq;
	aux->padre = pivote->padre;
	pivote->padre = aux;
	pivote->izq = aux->der;
	aux->der = pivote;

	if(pivote->izq != NULL) pivote->izq->padre = pivote;
	if(aux->padre == NULL) raiz = aux;
}

void Rojinegro::ajustarInsercion(nodo* x){
	nodo *tio;
	while(x != raiz && x->padre->color == 0){
		if(x->padre == x->padre->padre->izq){
			tio = x->padre->padre->der;
			if(tio == NULL) tio = centinela;
			if(tio->color == 0){
				// Caso 1
				x->padre->color = 1;
				tio->color = 1;
				x->padre->padre->color = 0;
				x = x->padre->padre;
			}else{
				if(x == x->padre->der){
					// Caso 2
					x = x->padre;
					rotar_izq(x);
				}
				// Caso 3
				x->padre->color = 1;
				x->padre->padre->color = 0;
				rotar_der(x->padre->padre);

			}
		}else{
			tio = x->padre->padre->izq;
			if(tio == NULL) tio = centinela;
			if(tio->color == 0){
				// Caso 1
				x->padre->color = 1;
				tio->color = 1;
				x->padre->padre->color = 0;
				x = x->padre->padre;
			}else{
				if(x == x->padre->izq){
					// Caso 2
					x = x->padre;
					rotar_der(x);
				}
				// Caso 3
				x->padre->color = 1;
				x->padre->padre->color = 0;
				rotar_izq(x->padre->padre);

			}	
		}
	}
	raiz->color = 1;
}

void Rojinegro::ajustarSupresion(nodo* x){
	nodo *hermano;
	while(x != raiz && x->color == 1){
		if(x == x->padre->izq){
			hermano = x->padre->der;
			if(hermano == NULL) hermano = centinela;
			if(hermano->color = 0){
				// Caso 1
				hermano->color = 1;
				x->padre->color = 0;
				rotar_izq(x->padre);
				hermano = x->padre->der;
			}
			if(hermano->izq->color == 1 && hermano->der->color == 1){
				// Caso 2
				hermano->color = 0;
				x = x->padre;
			}else{
				if(hermano->der->color == 1){
					// Caso 3
					hermano->izq->color = 1;
					hermano->color = 0;
					rotar_der(hermano);
					hermano = x->padre->der;
				}
				// Caso 4
				hermano->color = x->padre->color;
				x->padre->color = 1;
				hermano->der->color = 1;
				rotar_izq(x->padre);
				x = raiz;
			}
		}else{
			hermano = x->padre->izq;
			if(hermano->color = 0){
				// Caso 1
				hermano->color = 1;
				x->padre->color = 0;
				rotar_der(x->padre);
				hermano = x->padre->izq;
			}
			if(hermano->izq->color == 1 && hermano->der->color == 1){
				// Caso 2
				hermano->color = 0;
				x = x->padre;
			}else{
				if(hermano->izq->color == 1){
					// Caso 3
					hermano->der->color = 1;
					hermano->color = 0;
					rotar_izq(hermano);
					hermano = x->padre->izq;
				}
				// Caso 4
				hermano->color = x->padre->color;
				x->padre->color = 1;
				hermano->izq->color = 1;
				rotar_der(x->padre);
				x = raiz;
			}
		}
	}
	x->color = 1;
}

nodo* Rojinegro::abuelo(nodo *hijo){
	if((hijo != NULL) && (hijo->padre != NULL))
		return hijo->padre->padre;
	else
		return NULL;
}

nodo* Rojinegro::tio(nodo *hijo){
	nodo *aux = abuelo(hijo);
	if(hijo->padre == aux->izq)
		return aux->der;
	else
		return aux->izq;
}

#endif