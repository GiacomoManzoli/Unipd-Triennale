#include "TrafficoDati.h"

#include <string>
#include "Helper.h"
using std::string;

double TrafficoDati::costo_megabyte = 0.002; //1Gb ~ 2€

double TrafficoDati::costo() const {
	return megabyte * costo_megabyte;
}

string TrafficoDati::toString() const {
	return this->VoceBolletta::toString() +" Megabyte: "+Helper::toString(megabyte)+" Costo totale: "+Helper::toString(this->costo()) +
				   "€ ";
}

TrafficoDati* TrafficoDati::clone() const{
	return new TrafficoDati(*this);
}


bool TrafficoDati::operator==(const VoceBolletta& v) const{
	const TrafficoDati* t = dynamic_cast<const TrafficoDati*>(&v);
	return  t && (VoceBolletta::operator==(v)) &&
			megabyte == t->megabyte;

}
bool TrafficoDati::operator!=(const VoceBolletta& v) const{
	const TrafficoDati* t = dynamic_cast<const TrafficoDati*>(&v);
	return  !t || (VoceBolletta::operator!=(v)) ||
			megabyte != t->megabyte;
}
bool TrafficoDati::operator<(const VoceBolletta& v) const{
	const TrafficoDati* t = dynamic_cast<const TrafficoDati*>(&v);
	return  t && (VoceBolletta::operator<(v)) &&
			megabyte < t->megabyte;
}
bool TrafficoDati::operator>(const VoceBolletta& v) const{
	const TrafficoDati* t = dynamic_cast<const TrafficoDati*>(&v);
	return  t && (VoceBolletta::operator>(v)) &&
			megabyte > t->megabyte;
}
