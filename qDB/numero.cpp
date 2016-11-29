#include "numero.h"

Numero::Numero(string s)
{
    valid=(s!="");
    string cifre="0123456789";
    for (int i=0; i < s.length() && valid;i++){
        if (cifre.find(s[i])!=-1)
            num += s[i];
        else
            valid=false;
    }
}

bool Numero::operator==(const Numero& n)const{
    return n.isValid() && valid && num == n.num;
}


bool Numero::operator!=(const Numero& n)const{
    return n.isValid() && valid && num != n.num;
}
bool Numero::operator<(const Numero& n)const{
    return n.isValid() && valid && num < n.num;
}
bool Numero::operator>(const Numero& n)const{
    return n.isValid() && valid && num > n.num;
}
