#include "Telefonata.h"

#include <cmath>
#include "Helper.h"

#include <iostream>
using std::cout;

double Telefonata::costo_minuto = 0.19;

double Telefonata::costo() const{
	return ceil(this->durataTelefonata().minuti()) * costo_minuto;
}

string Telefonata::toString() const {
	string temp =  this->VoceBolletta::toString() + 
                   " Numero: " + destinatario.getNumero() +
				   " Inizio: " + inizio.toString() +
				   " Fine: " + fine.toString() +
				   " Durata: " + this->durataTelefonata().toString() +
				   " Costo: "+ Helper::toString(this->costo()) +
				   "€ ";
	return temp;
}

Telefonata* Telefonata::clone() const{
	return new Telefonata(*this);
}

bool Telefonata::operator==(const VoceBolletta& v) const{
	const Telefonata* t = dynamic_cast<const Telefonata*>(&v);

	return  t && (VoceBolletta::operator==(v)) &&
			destinatario == t->destinatario &&
			inizio == t->inizio &&
			fine == t->fine;

}
bool Telefonata::operator!=(const VoceBolletta& v) const{
	const Telefonata* t = dynamic_cast<const Telefonata*>(&v);
	return  !t || (VoceBolletta::operator!=(v)) ||
			destinatario != t->destinatario ||
			inizio != t->inizio ||
			fine != t->fine;
}
bool Telefonata::operator<(const VoceBolletta& v) const{
	const Telefonata* t = dynamic_cast<const Telefonata*>(&v);

	return  t && (VoceBolletta::operator<(v)) &&
			destinatario < t->destinatario &&
			inizio < t->inizio &&
			fine < t->fine;
}
bool Telefonata::operator>(const VoceBolletta& v) const{
	const Telefonata* t = dynamic_cast<const Telefonata*>(&v);

	return  t && (VoceBolletta::operator>(v)) &&
			destinatario > t->destinatario &&
			inizio > t->inizio &&
			fine > t->fine;
}
