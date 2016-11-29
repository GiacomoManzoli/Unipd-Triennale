#ifndef INTERVALLO_H
#define INTERVALLO_H

#include <string>
#include "Helper.h"

using std::string;

class Intervallo{
private:
	int sec;
protected:
	void setSecondi(int s){ sec=s; }
public:
	Intervallo(int s=0):sec(s){}
	double ore() const { return static_cast<double>(sec)/3600; }
	double minuti() const { return static_cast<double>(sec)/60; }
	int secondi() const { return sec;}

	string toString()const;

	operator int() const{ return sec;}
};

#endif