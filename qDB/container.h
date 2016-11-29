#ifndef CONTAINER_H
#define CONTAINER_H

#include <QDebug>


#include <iostream>

/*
	requisiti di K:
	>operatore di output
	>operatori di confronto
*/

using namespace std;


/*
>Smartp si occupa della gestione dei riferimenti per la parte condivisa della memoria (oggetti Item).
>ContainerItem implementa la logica della lista con doppio link.

>Container si occupa della gestione delle memoria condivisa mediante copia/distruzione profonda
*/
template<class K>
class Container{
	//la funzione di output non necessita dell'amicizia, sfrutta IteratoreCostante
	//necessita che K implementi operator<<
private: //Per rendere estendibile la classe
	class Item{ //Contiente l'informazione effettiva e i riferimenti, fa parte della memoria condivisa
	public:
		K dati;
		int rif;

        Item() : rif(0) {qDebug()<< "Costruito item "<<dati<<"";}
        Item(const K& i): dati(i), rif(0) {qDebug()<< "Costruito item "<<dati<<"";}
        ~Item() {qDebug() << "dealloc "<<dati<<"";}
		//deve gestire la logica del confronto

		bool operator==(const Item&) const; //Richiede che anche K li implementi
		bool operator!=(const Item&) const;
		bool operator>(const Item&) const;
		bool operator<(const Item&) const;
	};
	class Smartp{//puntatore che gestise i riferimenti
	public:
		Item* punt;

		Smartp(Item* =0); //Fa anche da costruttore di default e convertitore da Item*
		Smartp(const K&);

		Smartp(const Smartp&);
		~Smartp();
		
		Item& operator*() const;
		Item* operator->() const;
		
		Smartp& operator=(const Smartp&);
		
		operator bool() const;

		bool operator==(const Smartp&) const;
		bool operator!=(const Smartp&) const; 
	}; 
	class ContainerItem{ //gestisce la logica della lista, questa parte non è condivisa
	public:
		Smartp info; //informazione
		ContainerItem* prev;
		ContainerItem* next;

		//Va bene il distruttore standard, la distruzione ricorsiva viene fatta da Container
		ContainerItem():prev(0),next(0){}
        ContainerItem(const K& i, ContainerItem* p=0, ContainerItem* n=0)
            : info(i),prev(p),next(n){qDebug() <<"Costruisco CI creando l'item";}
        ContainerItem(const Smartp& i, ContainerItem* p=0, ContainerItem* n=0)
            : info(i),prev(p),next(n){qDebug() <<"Costruisco CI copiando lo smartp";}
        ~ContainerItem(){qDebug()<<"~CI";}
		bool operator==(const ContainerItem&) const; //Richiede che anche K li implementi
		bool operator!=(const ContainerItem&) const;
		bool operator>(const ContainerItem&) const;
		bool operator<(const ContainerItem&) const;
	};


	//Campi privati di container
	ContainerItem* _first;
	ContainerItem* _last;
	int _count;

	//Funzioni private di container
	static void copia(ContainerItem*,ContainerItem*&,ContainerItem*&); //PRE: viene chiamato sul primo nodo della lista
	static void distruggi(ContainerItem*); //PRE: viene chiamato sul primo nodo della lista
	/* Per il metodo copia è necessario usare il passaggio di parametri per riferimento in modo da poter
	inizializzare correnttamente sia il campo first, sia il campo last*/

public:
	//Iteratore e IteratoreCostante "iterano" su ContainerItem quindi usano un puntatore standard
	class Iteratore;
	class IteratoreCostante{
		friend class Container<K>;
 	private:
 		const Container::ContainerItem* punt;
 	public:
 		IteratoreCostante():punt(0){}
 		IteratoreCostante(const Iteratore& i) : punt(i.punt){}
 		bool operator==(const IteratoreCostante&) const;
		bool operator!=(const IteratoreCostante&) const;
		const K& operator*() const;
		IteratoreCostante& operator++();
		IteratoreCostante operator++(int); //Versione POSTFISSA
		IteratoreCostante& operator--();
		IteratoreCostante operator--(int); //Versione POSTFISSA
	};
	class Iteratore{
		friend class Container<K>; //in questo modo, da container, posso accedere a punt. (Necessaria per la funzione elimina)
 	private:
        Container::ContainerItem* punt;
 	public:
 		bool operator==(const Iteratore&) const;
		bool operator!=(const Iteratore&) const;
		K& operator*();
		Iteratore& operator++();
		Iteratore operator++(int); //Versione POSTFISSA
		Iteratore& operator--();
		Iteratore operator--(int); //Versione POSTFISSA
	};

	//first/last -> ContainerItem*
	Container():_first(0), _last(0), _count(0) {}

	Container(const Container&);
	~Container();
	Container<K>& operator=(const Container<K>&);

	void inserisciInCoda(const K&); //Inserimento in coda
	void inserisciInTesta(const K&); //Inserimento in testa
	void inserisci(const Iteratore&,const K&);
    void inserisciEsistente(const Iteratore&, const IteratoreCostante&); //posizione,valore



	void elimina(const K&); //Elimina la prima occorrenza
	void elimina(const Iteratore&);

    void clear();

	IteratoreCostante ricerca(const K&) const; //Ritorna un iteratoreCostante relativo alla prima occorrenza
	Iteratore ricerca(const K&); //Ritorna un iteratore relativo alla prima occorrenza

    template <class F>
    Container<K> ricerca(const K&, const F&) const;

    void modifica(const K&, const K&); //Sostituisce al valore del primo parametro il valore del secondo parametro

    Iteratore itemAtIndex(int);
    IteratoreCostante itemAtIndex(int) const;

    int count() const {return _count;} //Ritorna il numero di elementi presenti nel container

	Iteratore begin(); //Container ->First
	Iteratore last(); //Container ->Last
	Iteratore end(); //Container ->0

	IteratoreCostante begin() const;
	IteratoreCostante last() const;
	IteratoreCostante end() const;

};

//ImplementazioneSmartp ------------------------

template <class K>
Container<K>::Smartp::Smartp(Item* p) : punt(p){
	if (punt) punt->rif++;
}

template <class K>
Container<K>::Smartp::Smartp(const K& i){
    punt = new Item(i);
    punt->rif++;
}

template <class K> //Costruttore di copia
Container<K>::Smartp::Smartp(const Container<K>::Smartp& p) : punt(p.punt){
	if (punt) punt->rif++;
}


template <class K>
Container<K>::Smartp::~Smartp(){
	if (punt){
		punt->rif--;
        qDebug() << "~Smartp / nuovo rif "<<punt->rif<<"";
		if (punt->rif==0){
            delete punt;
		}
	}
}

template <class K>
typename Container<K>::Smartp& Container<K>::Smartp::operator=(const Container<K>::Smartp& p){
	if (this != &p){
		Container<K>::Item* t=punt;
		//t->rif++
		//punt->rif--;
		punt=p.punt;
		if (punt) punt->rif++;
		if (t){
			t->rif--;
			if (t->rif==0){
				delete t;
			}
		}
	}
	return *this;
}
template <class K>
Container<K>::Smartp::operator bool() const{
	return (punt != 0)? true:false;
}

template<class K>
typename Container<K>::Item& Container<K>::Smartp::operator*() const{
	return const_cast<Container<K>::Item&>(*punt);
}

template<class K>
typename Container<K>::Item* Container<K>::Smartp::operator->() const{
	return const_cast<Container<K>::Item*>(punt);
}

template<class K>
bool Container<K>::Smartp::operator==(const Container<K>::Smartp& p) const{
	return punt == p.punt;
}

template<class K>
bool Container<K>::Smartp::operator!=(const Container<K>::Smartp& p) const{
	return punt != p.punt;
}

//Implementazione Item ---------------------------------------------------------------

template <class K>
bool Container<K>::Item::operator==(const Item& i) const{
	return dati == i.dati;
}

template <class K>
bool Container<K>::Item::operator!=(const Item& i) const{
	return dati != i.dati;
}

template <class K>
bool Container<K>::Item::operator>(const Item& i) const{
	return dati > i.dati;
}

template <class K>
bool Container<K>::Item::operator<(const Item& i) const{
	return dati < i.dati;
}

//ImplementazioneIteratore ---------------------------------------------------------------
//Recap: Iteratore ha un membro punt di tipo ContainerItem*

template <class K>
K& Container<K>::Iteratore::operator*(){
	//punt->info è di tipo smartp,
	//Il dato può essere modificato, se era un dato condiviso ne faccio una copia visto che può essere modificata
	if (punt->info->rif > 1)
		punt->info = new Item(punt->info->dati); //è un assegnazione tra smartp, si occupano loro di lasciare garbage
	return punt->info->dati;
}

template <class K>
typename Container<K>::Iteratore& Container<K>::Iteratore::operator++(){
	if (punt) punt=punt->next;
	return *this;
}

template <class K>
typename Container<K>::Iteratore Container<K>::Iteratore::operator++(int){
	Iteratore aux=*this; 
    qDebug() <<"Sposto l'iteratore";
	if (punt) punt=punt->next;
	return aux;
}

template <class K>
typename Container<K>::Iteratore& Container<K>::Iteratore::operator--(){
	if (punt) punt=punt->prev;
	return *this;
}

template <class K>
typename Container<K>::Iteratore Container<K>::Iteratore::operator--(int){
	Iteratore aux=*this; 
	if (punt) punt=punt->prev;
	return aux;
}

template <class K>
bool Container<K>::Iteratore::operator==(const Container<K>::Iteratore& it) const{
	return punt == it.punt; //uguaglianza tra puntatori standard
}

template <class K>
bool Container<K>::Iteratore::operator!=(const Container<K>::Iteratore& it) const{
	return punt != it.punt;
}

//ImplementazioneIteratoreCostante ---------------------------------------------------------------


template <class K>
const K& Container<K>::IteratoreCostante::operator*() const{
	return punt->info->dati; //Cast implicito da K a K& e da K& a const K&
}

template <class K>
typename Container<K>::IteratoreCostante& Container<K>::IteratoreCostante::operator++(){
	if (punt) punt=punt->next;
	return *this;
}

template <class K>
typename Container<K>::IteratoreCostante Container<K>::IteratoreCostante::operator++(int){
	IteratoreCostante aux=*this; 
	if (punt) punt=punt->next;
	return aux;
}

template <class K>
typename Container<K>::IteratoreCostante& Container<K>::IteratoreCostante::operator--(){
	if (punt) punt=punt->prev;
	return *this;
}

template <class K>
typename Container<K>::IteratoreCostante Container<K>::IteratoreCostante::operator--(int){
	IteratoreCostante aux=*this; 
	if (punt) punt=punt->prev;
	return aux;
}

template <class K>
bool Container<K>::IteratoreCostante::operator==(const Container<K>::IteratoreCostante& it) const{
	return punt == it.punt;
}

template <class K>
bool Container<K>::IteratoreCostante::operator!=(const Container<K>::IteratoreCostante& it) const{
	return punt != it.punt;
}

//Implementazione container

//Funzioni ausiliaree

template <class K>
void Container<K>::copia(Container<K>::ContainerItem* i, Container<K>::ContainerItem*& newFirst, Container<K>::ContainerItem*& newLast){
	//PRE: i è il primo nodo di una lista a concatenazione doppia
	//		newFirst,newLast dovranno contenere rispettivamente il puntatore alla teste a alla coda della nuova lista creata

    newFirst=newLast=0; //Per evitare problemi quando vado a copiare una lista vuota.
	if (i){
		Container<K>::ContainerItem *prec=0,*current=i->next;
		newFirst=new ContainerItem(i->info,0,0);//Creo il primo nodo della lista, e mi salvo il puntatore
		prec=newFirst;

		while (current){
			prec->next=new ContainerItem(current->info, prec,0);
			prec=prec->next;
			current=current->next;
		}
		//Current punta a NULL
		//prec punta all'ultimo nodo creato, cioè newLast
        newLast=prec;
	}

}

template <class K>
void Container<K>::distruggi(Container<K>::ContainerItem* i){
	//PRE: viene chiamato sul primo nodo della lista
	if (i){
        //qDebug() << "d";
		distruggi(i->next);
		delete i;
		//Invoca il distruttore standard che distrugge ogni membro dell'oggetto, in particolare viene chiamato
		//il distruttore di Smartp che si occupa della gestione dei riferimenti per la parte condivisa della memoria
	}
}

//Regola dei 3
template <class K>
Container<K>::Container(const Container<K>& c){
    copia(c._first, _first, _last);
	_count=c._count;
}

template <class K>
Container<K>::~Container(){
    qDebug()<< "Chiamata al distruttore";
	if (_first != 0) distruggi(_first);
    qDebug() <<"Uscita dal distruttore";
}

template <class K>
Container<K>& Container<K>::operator=(const Container<K>& c){
	if (this != &c){
		ContainerItem* t=_first;
		copia(c._first,_first,_last);
		distruggi(t);
		_count=c._count;
	}
	return *this;
}

//Funzioni pubbliche
/*Recap:
	void InserisciInCoda(const K&); //Inserimento in coda
	void InserisciInTesta(const K&); //Inserimento in testa
	void Inserisci(const Iteratore&,const K&);

	void Elimina(const K&); //Elimina la prima occorrenza
	void Elimina(const Iteratore&);
c
	Iteratore Ricerca(const K&) const; //Ritorna un iteratore relativo alla prima occorrenza
	
	void Modifica(const K&, const K&); //Sostituisce al valore del primo parametro il valore del secondo parametro

	Iteratore Begin(); //Container ->First
	Iteratore Last(); //Container ->Last
	Iteratore Null(); //Container ->0

	IteratoreCostante Begin() const;
	IteratoreCostante Last() const;
	IteratoreCostante Null() const;*/

template <class K>
void Container<K>::inserisciEsistente(const Container<K>::Iteratore &pos, const Container<K>::IteratoreCostante & it){
    //Inserisce nella posizione precedente a quella puntata da pos il valore referenziato da it, se pos è NULL inserisce in coda
    if (pos.punt == 0){ //inerimento in coda
        _last = new ContainerItem(it.punt->info,_last,0);
        if (_last->prev) _last->prev->next=_last;
        if (_count == 0) {
            _first=_last;
            //qDebug() <<"Inserimento a lista vuota"<<endl;
            } //caso con lista vuota
    }
    else{
        ContainerItem* prec= pos.punt->prev;
        if (prec==0){ //inserimento in testa
            _first = new ContainerItem(it.punt->info, 0, _first);
            _first->next->prev=_first;

        }
        else{ //inserimento prima di it
            prec->next=new ContainerItem(it.punt->info,prec,pos.punt);
            pos.punt->prev=prec->next;
        }
    }
    _count++;
}

template <class K>
void Container<K>::inserisci(const Container<K>::Iteratore& it, const K& val){
    Container<K>::IteratoreCostante aux;
    aux.punt=new ContainerItem(val,0,0);
    inserisciEsistente(it,aux); //viene creato un nuovo ContainerItem con uno Smartp che punta allo stesso valore.
    delete aux.punt; //Gli iteratori non si occupano di deallocare la memoria, dato che non ne alloccano mai
}

template <class K>
void Container<K>::inserisciInTesta(const K& val){
	this->inserisci(this->Begin(),val); //Inserisci inserisce il nuovo elemento prima del first, cioè in testa
}

template <class K>
void Container<K>::inserisciInCoda(const K& val){
    //qDebug() << "chiamata a iniserisci in coda"<<endl;
	this->inserisci(this->end(),val); //Inserisci invocata con l'iteratore nullo inserisce in coda
}

template <class K>
void Container<K>::elimina(const Iteratore& it){
    if (it.punt==0) return; //controllo che non sia l'iteratore nullo
    //può essere che venga chiamato elimina sul primo o ultimo nodo, devo quindi controllare di non andare in segmentation fault
    if (it.punt->prev){
		//L'elemento da cancellare ha un elemento precedente, potrebbe essere il last
		it.punt->prev->next=it.punt->next;
		if (it.punt == _last){ 
			//Se cancello l'ultimo elemento, quello precendete è il nuovo ultimo
			_last = it.punt->prev;
		}
	}
	if (it.punt->next){
		it.punt->next->prev=it.punt->prev; //se it.punt == first, prev=0, 
		if (it.punt == _first){ 
			//Se cancello il primo elemento, quello successivo è il nuovo primo
			_first = it.punt->next;
		}
	}
    //Se la lista e' composta da un solo nodo
    if (it.punt == _last && it.punt == _first){
        _first=_last=0;
    }
	delete it.punt;
    _count--;
}

template <class K>
void Container<K>::elimina(const K& val){
	Iteratore it= this->ricerca(val); //Sfrutto l'amicizia per "convertire" un IteratoreCostante in un Iteratore
	if (it != this->end()) this->elimina(it);
}

template <class K>
void Container<K>::clear(){
    distruggi(_first);
    _first=_last=0;
    _count=0;
}

template <class K>
typename Container<K>::IteratoreCostante Container<K>::ricerca(const K& val) const{
	IteratoreCostante it = this->begin();
    const IteratoreCostante fine = this->end();
    while (it != fine && *it != val){
		it++;
    }
	return it;
}
template <class K>
typename Container<K>::Iteratore Container<K>::ricerca(const K& val){
	Iteratore it = this->begin();
	const Iteratore fine = this->end();
	while (it != fine && *it != val){
		it++;
	}
	// it == fine || *it == val
	return it;
}

template <class K>
template <class F>
Container<K> Container<K>::ricerca(const K& x, const F& equals) const{
    /* Con questo codice viene costruito un nuovo ContainerItem con un nuovo Item, dato che
     * la funzione inserisci e' stata progettata per inserire un nuovo elemento.
    Container<K> aux;
    Container<K>::IteratoreCostante it=begin();
    while (it != end()){
        if (equals(x,*it)){
            aux.inserisciInCoda(*it);
        }
        it++;
    }
    return aux;*/

    /*
     * In questo modo viene costruita una copia di tutti i ContainerItem che come Item hanno lo Smartp
     * che si riferisce allo stesso oggetto nell heap.
    */
    qDebug() << "Costruisco di copia aux";
    Container<K> aux(*this);
    Container<K>::Iteratore it = aux.begin();
    while (it != aux.end()){
        if (!equals(x,(it.punt)->info->dati)){   //Per evitare uno spreco di memoria devo accedere all'elemento sfruttando l'amicizia.
            aux.elimina(it);                        //Infatti, se mi limitassi a dereferenziare l'Iteratore mi si creerebbe una copia che in questo caso e' inutile
        }
        it++;
    }
    return aux;

}



template <class K>
void Container<K>::modifica(const K& oval, const K& nval){
	Iteratore it = this->ricerca(oval);
	if (it != this->end()) *it=nval; //Si occupa la dereferenzazione di iteratore a gestire la parte della memoria condivisa
} 

template <class K>
typename Container<K>::Iteratore Container<K>::itemAtIndex(int k){
    Container<K>::Iteratore it=begin();
    int i=0;
    while (it != end() && i<k){it++; i++;}
    if (i==k && it!= end())
        return it;
    else
        return end();
}

template <class K>
typename Container<K>::IteratoreCostante Container<K>::itemAtIndex(int k) const{
    Container<K>::IteratoreCostante it=begin();
    int i=0;
    while (it != end() && i<k){it++; i++;}
    if (i==k && it!= end())
        return it;
    else
        return end();
}


template <class K>
ostream& operator<<(ostream& os,const Container<K>& c){
	for (typename Container<K>::IteratoreCostante it=c.begin(); it != c.end(); it++){
        //qDebug()qDebug()<<endl<<"Stampooooo stampooooo stampooooo ";

		os << *it <<"\n";
	}
	return os;
}



template <class K>
typename Container<K>::Iteratore Container<K>::begin(){
	Iteratore aux;
	aux.punt = _first;
	return aux;
} //Container ->First
template <class K>
typename Container<K>::Iteratore Container<K>::last(){
	Iteratore aux;
	aux.punt = _last;
	return aux;
} //Container ->Last
template <class K>
typename Container<K>::Iteratore Container<K>::end(){
	Iteratore aux;
	aux.punt = 0;
	return aux;
}//Container ->0
template <class K>
typename Container<K>::IteratoreCostante Container<K>::begin() const{
	IteratoreCostante aux;
	aux.punt = _first;
	return aux;
}
template <class K>
typename Container<K>::IteratoreCostante Container<K>::last() const{
	IteratoreCostante aux;
	aux.punt = _last;
	return aux;
}
template <class K>
typename Container<K>::IteratoreCostante Container<K>::end() const{
	IteratoreCostante aux;
	aux.punt = 0;
	return aux;
}




#endif
