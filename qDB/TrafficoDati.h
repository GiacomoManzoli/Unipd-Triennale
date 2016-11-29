#ifndef TRAFIICO_DATI_H
#define TRAFIICO_DATI_H

#include "VoceBolletta.h"

class TrafficoDati : public VoceBolletta{
private:
	int megabyte;
	static double costo_megabyte;
public:
	TrafficoDati(Data d,int m): VoceBolletta(d), megabyte(m){}

    int getDati() const {return megabyte;}

	virtual double costo() const;
	virtual string toString() const;
	virtual ~TrafficoDati(){}
	virtual TrafficoDati* clone() const;

	bool operator==(const VoceBolletta&) const;
	bool operator!=(const VoceBolletta&) const;
	bool operator<(const VoceBolletta&) const;
	bool operator>(const VoceBolletta&) const;

};

#endif
