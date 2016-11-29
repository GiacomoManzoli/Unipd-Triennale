#ifndef NUMERO_H
#define NUMERO_H

#include <string>
using std::string;

class Numero
{
private:
    string num;
    bool valid;
public:
    Numero(string s="");
    string getNumero() const {return num;}
    bool isValid() const {return valid;}
    operator string() const {return num;}

    bool operator==(const Numero& n)const;
    bool operator!=(const Numero& n)const;
    bool operator<(const Numero& n)const;
    bool operator>(const Numero& n)const;
};

#endif // NUMERO_H
