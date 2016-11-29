
#include "Helper.h"

string Helper::toString(int v){
	stringstream ss;
	ss << v;
	string str = ss.str();
	return str;
}
string Helper::toString(double v){
	stringstream ss;
	ss << v;
	string str = ss.str();
	return str;
}