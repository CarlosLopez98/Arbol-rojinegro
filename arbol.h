#ifndef ARBOL_H
#define ARBOL_H

using namespace std;

struct NODO{ 
	int info;
	bool color; // 0 rojo - 1 negro
	NODO *padre, *izq, *der;
};

class Arbol{
	NODO *raiz;

	public:
		Arbol(){
			raiz=NULL;
		}	
		NODO *raiz_arbol(){
			return raiz;
		}
		int ins_arbol (int);
		NODO *buscar_arbol (int, NODO *, NODO *);
		void borrar_nodo(NODO *, NODO *);
		NODO *buscar(int, NODO **, NODO *);
		int retira_arbol(int);
		void inorden(NODO *);
		void preorden(NODO *);
		void posorden(NODO *);
		void destruir (NODO *p);
		~Arbol();
};

NODO *Arbol::buscar_arbol(int dato, NODO *p, NODO *q){
	if (p==NULL) return q;
	if (dato < p->info){
		q=p;
		q=buscar_arbol(dato,p->izq,q);
		return q;
	}else if (dato > p->info){
		q=p;
		q=buscar_arbol(dato,p->der,q);
		return q;
	}else{
		return NULL;
	}
}

int Arbol::ins_arbol(int n){
	NODO *q;
	if(raiz == NULL){
		raiz= new NODO;
		raiz->info =n;
		raiz->izq=raiz->der=raiz->padreNULL;
		return 0;
	}

	q =buscar_arbol(n,raiz,NULL);
	if(q==NULL) return -1;
	NODO *nuevo;
	nuevo= new NODO;
	nuevo->info = n;
	nuevo->izq=nuevo->der=NULL;
	nuevo->padre = q;
	if(n<q->info)
         q->izq=nuevo;
    else
     	q->der=nuevo;

    return 0;
}

void Arbol::borrar_nodo(NODO *q, NODO *p){
	NODO  *r, *s,*t;
	if (p->izq==NULL) r=p->der;
	else if (p->der==NULL) r=p->izq;
	else{
		s =p;
		r=p->der;
		t=r->izq;
		while(t!=NULL){
			s=r;
			r=t;
			t=t->izq;
		}
		if(p!=s){
	    	s->izq=r->der;
    		r->der=p->der;
    	}
		r->izq =p->izq;
	}

	if (q==NULL) raiz= r;
	else if (p==q->izq) q->izq =r;
	else q->der = r;

	delete p;
}

NODO *Arbol::buscar(int n, NODO **p, NODO *q){
	if(*p==NULL) return NULL;
	if (n <(*p)->info){
		q=*p;
		*p=(*p)->izq;
		q=buscar(n,p,q);
		return q;
	}else if (n>(*p)->info){
		q=*p;
		*p=(*p)->der;
		q =buscar(n,p,q);
		return q;
	}else return q;

}

int Arbol::retira_arbol(int n){
	NODO *q, *p=raiz;
	q=buscar(n,&p,NULL);
	if(p==NULL) return -1;
	borrar_nodo(q,p);
	return 0;
}

void Arbol::inorden(NODO *p){
	if(p!=NULL){
		inorden(p->izq);
		cout<<p->info<<endl;
        inorden(p->der);
    }
}

void Arbol::preorden(NODO *p){
	if (p!=NULL){
       cout<<p->info<<endl;
       preorden(p->izq);
       preorden(p->der);
   }
}

void Arbol::posorden(NODO *p){
	if (p!=NULL){
       posorden(p->izq);
       posorden(p->der);
      cout<<p->info<<endl;
  }
}

void Arbol::destruir(NODO *p){
	if (p!=NULL){
    	destruir(p->izq);
    	destruir(p->der);
    	delete p;
    	cout<<"Nodo destruido..."<< endl;
    }
}

Arbol::~Arbol( ) {
	destruir(raiz);
}

#endif