#ifndef VOCE_BOLL_PTR
#define VOCE_BOLL_PTR

#include "VoceBolletta.h"
#include <ostream>

using std::ostream;

class VoceBollettaPtr
{
private:
	VoceBolletta* punt;
public:
	VoceBollettaPtr(VoceBolletta* p=0): punt(p){}

	VoceBollettaPtr(const VoceBollettaPtr&);
	~VoceBollettaPtr();
	VoceBollettaPtr& operator=(const VoceBollettaPtr&);

	/*
		isEqual() -> confronta il campo puntatore
		operator== -> confronta gli oggetti puntati dal puntatore

		è necessario perchè nella funzione di Container<K>::ricerca(const K&) non è possibile distinguere
		se K è un oggetto o un puntatore smart.
		Dovendo tenere Container<K> il più generico possibile è necessario definire così l'operator==
	*/

	bool isEqual(const VoceBollettaPtr&) const;
	bool operator==(const VoceBollettaPtr&) const;
	bool operator!=(const VoceBollettaPtr&) const;
	bool operator<(const VoceBollettaPtr&) const;
	bool operator>(const VoceBollettaPtr&) const;


    const VoceBolletta& operator*() const;
    const VoceBolletta* operator->() const;

    VoceBolletta& operator*();
    VoceBolletta* operator->();

	operator bool() const;

};

ostream& operator<<(ostream&,const VoceBollettaPtr& );


#endif
