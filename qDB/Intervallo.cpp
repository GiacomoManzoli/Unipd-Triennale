#include "Intervallo.h"

string Intervallo::toString() const{

	string m,s;
	if (sec/60<10) m="0";
	if (sec%60<10) s="0";

	m+=Helper::toString(sec/60);
	s+=Helper::toString(sec%60);

	return m +":"+s;
}
