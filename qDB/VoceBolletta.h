#ifndef VOCEBOLLETTA_H
#define VOCEBOLLETTA_H

#include <string>

#include "Data.h"
using std::string;

class VoceBolletta{
private:
	Data giorno;
protected:
	void setData(Data);
public:
	VoceBolletta(Data d):giorno(d){}
	virtual double costo() const=0;
	virtual string toString() const;
	virtual VoceBolletta* clone() const=0;
	virtual ~VoceBolletta() {}

	Data getData() const;

	virtual bool operator==(const VoceBolletta&) const;
	virtual bool operator!=(const VoceBolletta&) const;
	virtual bool operator<(const VoceBolletta&) const;
	virtual bool operator>(const VoceBolletta&) const;
	
};






#endif
