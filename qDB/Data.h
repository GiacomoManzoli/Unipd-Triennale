#ifndef DATA_H
#define DATA_H

#include <string>

using std::string;

class Data{
private:
	int giorno;
	int mese;
    int anno;
public:
	Data(int g=1,int m=1,int a=0):giorno(g),mese(m),anno(a){}
	string toString() const;

    int getGiorno() const {return giorno;}
    int getMese() const {return mese;}
    int getAnno() const {return anno;}

	bool operator==(const Data&) const;
	bool operator!=(const Data&) const;
	bool operator<(const Data&) const;
	bool operator>(const Data&) const;

	

};

#endif
