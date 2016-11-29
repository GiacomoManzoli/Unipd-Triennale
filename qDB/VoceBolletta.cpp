#include "VoceBolletta.h"

void VoceBolletta::setData(Data d){
	giorno=d;
}

string VoceBolletta::toString() const { 
	return "Data: "+giorno.toString(); 
}
Data VoceBolletta::getData() const {
	return giorno;
}

bool VoceBolletta::operator==(const VoceBolletta& v) const{
	return giorno == v.giorno;
}
bool VoceBolletta::operator!=(const VoceBolletta& v) const{
	return giorno != v.giorno;
}
bool VoceBolletta::operator<(const VoceBolletta& v) const{
	return giorno < v.giorno;
}
bool VoceBolletta::operator>(const VoceBolletta& v) const{
	return giorno > v.giorno;
}
