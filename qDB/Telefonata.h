#ifndef TELEFONATA_H
#define TELEFONATA_H

#include "VoceBolletta.h"
#include "Orario.h"
#include "numero.h"


class Telefonata : public VoceBolletta{
private:
    Numero destinatario;
	Orario inizio;
	Orario fine;
	static double costo_minuto;	
public:
    Telefonata(Numero dest,Data d, Orario i, Orario f): VoceBolletta(d), destinatario(dest), inizio(i),fine(f){}

    Intervallo durataTelefonata() const{ return fine - inizio; }
    Numero getNumero() const{return destinatario;}

    Orario getOrarioInizio() const{return inizio;}
    Orario getOrarioFine() const{return fine;}

    virtual ~Telefonata() {}
	virtual double costo() const;
	virtual string toString() const;
	virtual Telefonata* clone() const;

	bool operator==(const VoceBolletta&) const;
	bool operator!=(const VoceBolletta&) const;
	bool operator<(const VoceBolletta&) const;
	bool operator>(const VoceBolletta&) const;



};

#endif
