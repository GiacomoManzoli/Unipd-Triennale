#include "VoceBollettaPtr.h"

VoceBollettaPtr::VoceBollettaPtr(const VoceBollettaPtr& v){
	punt = v.punt->clone();
}

VoceBollettaPtr::~VoceBollettaPtr(){
	if (punt){ delete punt;	}
}

VoceBollettaPtr& VoceBollettaPtr::operator=(const VoceBollettaPtr& p){
	if (this != &p){
		if (punt) delete punt;
		punt=p.punt->clone();
	}
	return *this;
}

VoceBollettaPtr::operator bool() const{
	return punt != 0;
}

const VoceBolletta& VoceBollettaPtr::operator*()const{
    return *punt;
}

const VoceBolletta* VoceBollettaPtr::operator->()const{
    return punt;
}

VoceBolletta& VoceBollettaPtr::operator*(){
    return *punt;
}

VoceBolletta* VoceBollettaPtr::operator->(){
    return punt;
}


bool VoceBollettaPtr::isEqual(const VoceBollettaPtr& p)const{
    return punt == p.punt;
}

// Confronti

bool VoceBollettaPtr::operator==(const VoceBollettaPtr& p) const{
	return *punt == *(p.punt);

}

bool VoceBollettaPtr::operator!=(const VoceBollettaPtr& p) const{
	return *punt != *(p.punt);
}

bool VoceBollettaPtr::operator<(const VoceBollettaPtr& p) const{
	return *punt < *p.punt;
}
bool VoceBollettaPtr::operator>(const VoceBollettaPtr& p) const{
	return *punt > *p.punt;
}

ostream& operator<<(ostream& os,const VoceBollettaPtr& p){
	return os << p->toString();
}
