#include "Orario.h"
#include "Helper.h"



Orario::Orario(int s){
	this->setSecondi(s % 86400);
}

Orario::Orario(int o,int m,int s){
    this->setSecondi(o*3600 + m*60 + s);
    if(Intervallo::secondi() >= 86400) setSecondi(Intervallo::secondi() % 86400);
}

int Orario::ore() const {
	int o=static_cast<int>(this->Intervallo::ore());
	return o%24; 
}
int Orario::minuti() const { 
	int m=static_cast<int>(this->Intervallo::minuti());
	return m%60; 
}

int Orario::secondi() const { 
	return this->Intervallo::secondi()%60;
}

string Orario::toString() const{
	string o,m,s;
	if (ore()<10) o="0";
	if (minuti()<10) m="0";
	if (secondi()<10) s="0";

	o+=Helper::toString(ore());
	m+=Helper::toString(minuti());
	s+=Helper::toString(secondi());

	return o + ":" + m +":"+s;
}

bool Orario::operator==(const Orario& o) const{
	return this->Intervallo::secondi() == o.Intervallo::secondi();
}
bool Orario::operator!=(const Orario& o) const{
	return this->Intervallo::secondi() != o.Intervallo::secondi();
}
bool Orario::operator<(const Orario& o) const{
	return this->Intervallo::secondi() < o.Intervallo::secondi();
}
bool Orario::operator>(const Orario& o) const{
	return this->Intervallo::secondi() > o.Intervallo::secondi();
}

Intervallo Orario::operator-(const Orario& o) const{
	const Orario& c = *this;
    int diff=0;

	if (c < o){
        diff = 86400 - o.Intervallo::secondi();
        diff += c.Intervallo::secondi();
	}
	else{
		diff = c.Intervallo::secondi() - o.Intervallo::secondi();
    }
	return diff;
}
