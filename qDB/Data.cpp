#include "Data.h"
#include "Helper.h"

string Data::toString() const {
	string g,m,a;
	
	if(giorno<10) g = "0";
	g+=Helper::toString(giorno);
	
	if(mese < 10) m = "0";
	m+=Helper::toString(mese);

	a="0000";
	a+=Helper::toString(anno);
	int start = a.length()-4;
	a = a.substr(start,4);
	return g + "/" + m + "/" + a;
}

bool Data::operator==(const Data& d) const{
	return  giorno==d.giorno && 
			mese == d.mese && 
			anno == d.anno;
}
bool Data::operator!=(const Data& d) const{
	return  giorno!=d.giorno || 
			mese != d.mese || 
			anno != d.anno;
}
bool Data::operator<(const Data& d) const{
	return anno < d.anno && mese < d.mese && giorno < d.giorno;

}
bool Data::operator>(const Data& d) const{
	return anno > d.anno && mese > d.mese && giorno > d.giorno;
}



/*
	void avanzaUnGiorno(){
		giorno++;
		// 30 giorni ha novembre con aprile giugno e settembre
		// 11 4 6 9
		// di 28 ce n'è uno
		// tutti gli altri ne han 31 (marzo maggio luglio agosto ottobre dicembre)
		// 3 5 7 8 10 12
		if (giorno == 31 && (mese == 4 || mese == 6 || mese == 9 || mese == 11)){
			mese++;
			giorno=1;
		}
		if (giorno == 32 && (mese == 3 || mese == 5 || mese == 7 || mese == 8 || mese == 10 || mese == 12)){
			mese++;
			giorno=1;
            if (mese==13){
				anno++;
				mese=1;
			}
		}
		if (mese == 2){
			if (this->bisestile()){
				if (giorno==30){ mese++; giorno=1; }
			}
			else
			{
				if (giorno == 29){ mese++; giorno=1;}
			}

		}
	}*/
