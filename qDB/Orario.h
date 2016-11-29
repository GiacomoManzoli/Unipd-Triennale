#ifndef ORARIO_H
#define ORARIO_H

#include "Intervallo.h"
#include <string>
using std::string;

class Orario: public Intervallo{
public:
	Orario(int s=0);
    Orario(int o,int m,int s);

	int ore() const;
	int minuti() const;
	int secondi() const;

	string toString() const; 

	bool operator==(const Orario&) const;
	bool operator!=(const Orario&) const;
	bool operator<(const Orario&) const;
	bool operator>(const Orario&) const;
	
	Intervallo operator-(const Orario&) const;
};
#endif
