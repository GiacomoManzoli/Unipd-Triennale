#include "Bolletta.h"

#include "Telefonata.h"
#include "TrafficoDati.h"

#include <QStringList>

void Bolletta::inserisci(const VoceBollettaPtr& p){
    inserisciInCoda(p);
    emit itemAdded(p);
    emit dataChanged();
}

void Bolletta::inserisciBolletta(const Bolletta& b){
    IteratoreCostante it=b.begin();
    while (it != b.end()){
        inserisciEsistente(last(),it);
        emit itemAdded(*it);
        it++;
    }
    emit dataChanged();
}

void Bolletta::elimina(int k){ //Nuova funzione
    Iteratore it = Container<VoceBollettaPtr>::itemAtIndex(k);
    if (it!= end()){
        Container<VoceBollettaPtr>::elimina(it);
        emit itemRemoved(k);
        emit dataChanged();
    }
}

void Bolletta::elimina(const Iteratore& k){

    Container<VoceBollettaPtr>::elimina(k);
    resync();
}

void Bolletta::modifica(int i,const VoceBollettaPtr& n){
    Iteratore it = Container<VoceBollettaPtr>::itemAtIndex(i);
    *it=n;
    emit itemUpdated(i,n);
    emit dataChanged();
}

const VoceBollettaPtr Bolletta::itemAtIndex(int k) const{//Copre Container::itemAtIndex(int) const
    IteratoreCostante it = Container<VoceBollettaPtr>::itemAtIndex(k);
    if (it!=end())
        return *it;
    return 0;
}
VoceBollettaPtr Bolletta::itemAtIndex(int k){//Copre Container::itemAtIndex(int)
    Iteratore it = Container<VoceBollettaPtr>::itemAtIndex(k);
    if (it!=end())
        return *it;
    return 0;
}


Bolletta* Bolletta::cerca(const VoceBollettaPtr& p,const FuntoreBolletta& funt) const{
    return new Bolletta(ricerca(p,funt));
}


Intervallo Bolletta::durataTelefonateTot() const{//Nuova funzione
    Intervallo ris;
    for (IteratoreCostante it = begin(); it!= end();it++){
        const Telefonata* p = dynamic_cast<const Telefonata*>(&(*(*it)));//*it e' un VoceBollettaPtr, **it e' una VoceBolletta, per fare il dynamic_cast ho bisogno di un puntatore, quindi &**it
        if (p) ris = ris + p->durataTelefonata();//vengono fatte un po' di conversioni di tipo, pero' riesce a fare la somma di intervalli con operator+(int,int)
    }
    return ris;
}
long int Bolletta::quantitaDatiTot() const{//Nuova funzione
    long int ris=0;
    for (IteratoreCostante it = begin(); it!= end();it++){
        const TrafficoDati* p = dynamic_cast<const TrafficoDati*>(&(*(*it)));//*it e' un VoceBollettaPtr, **it e' una VoceBolletta, per fare il dynamic_cast ho bisogno di un puntatore, quindi &**it
       if (p) ris = ris + p->getDati();
    }
    return ris;
}
double Bolletta::costoTelefonateTot()const{//Nuova funzione
    double ris=0;
    for (IteratoreCostante it = begin(); it!= end();it++){
        const Telefonata* p = dynamic_cast<const Telefonata*>(&(*(*it)));//*it e' un VoceBollettaPtr, **it e' una VoceBolletta, per fare il dynamic_cast ho bisogno di un puntatore, quindi &**it
        if (p) ris = ris + p->costo();
    }
    return ris;
}
double Bolletta::costoDatiTot()const {//Nuova funzione
    double ris=0;
    for (IteratoreCostante it = begin(); it!= end();it++){
        const TrafficoDati* p = dynamic_cast<const TrafficoDati*>(&(*(*it)));//*it e' un VoceBollettaPtr, **it e' una VoceBolletta, per fare il dynamic_cast ho bisogno di un puntatore, quindi &**it
        if (p) ris = ris + p->costo();
    }
    return ris;
}
double Bolletta::costoTotale()const {//Nuova funzione
    double ris=0;
    for (IteratoreCostante it = begin(); it!= end();it++){
        ris +=(*it)->costo();
    }
    return ris;
}

void Bolletta::resync()const{//Nuova funzione
    emit destroyed();
    IteratoreCostante it = begin();
    while (it!= end()){
        emit itemAdded(*it);
        it++;
    }
    emit dataChanged();
}

void Bolletta::salva(QTextStream& stream) const{
    IteratoreCostante it=begin();
    while (it != end()){
        const Telefonata* t=dynamic_cast<const Telefonata*>(&(**it));
        if (t){
            stream << "TELEFONATA" << "@";
            stream << QString::fromStdString(t->getData().toString())<< "@";
            stream << QString::fromStdString(t->getNumero()) <<"@";
            stream << QString::fromStdString(t->getOrarioInizio().toString())<<"@";
            stream << QString::fromStdString(t->getOrarioFine().toString())<<"\n";
        }
        const TrafficoDati* d = dynamic_cast<const TrafficoDati*>(&**it);
        if (d){
            stream << "DATI"<<"@";
            stream << QString::fromStdString(d->getData().toString())<<"@";
            stream<< QString::number(d->getDati())<<"\n";
        }

        it++;
    }
}

void Bolletta::carica(QTextStream & stream){
    while (!stream.atEnd()){

        QString s=stream.readLine().trimmed(); //Leggo una riga del file, se e' valida ha formato TELEFONATA@Data@Numero... oppure DATI@Data@MB

        QStringList parti=s.split("@");
        if (parti.length() >1){    //se non c'e' neache una @ la riga non e' valida, parti ha un solo elemento.

            //Creo la data
            QString temp=parti.at(1).trimmed();
            QStringList partiTemp=temp.split("/");
            if (partiTemp.length()!=3) continue; //Data non valida
            Data d(partiTemp.at(0).toInt(),partiTemp.at(1).toInt(),partiTemp.at(2).toInt());

            if (parti.first() == "TELEFONATA"){
                //Data,Numero,Inizio,Fine
                Numero num(parti.at(2).toStdString());

                //Orario inizio
                temp=parti.at(3).trimmed();
                partiTemp=temp.split(":");
                if (partiTemp.length()!=3) continue; //Orario non valido
                Orario ini(partiTemp.at(0).toInt(),partiTemp.at(1).toInt(),partiTemp.at(2).toInt());

                //Orario fine
                temp=parti.at(4).trimmed();
                partiTemp=temp.split(":");
                if (partiTemp.length()!=3) continue; //Data non valido
                Orario fin(partiTemp.at(0).toInt(),partiTemp.at(1).toInt(),partiTemp.at(2).toInt());

                this->inserisci(new Telefonata(num,d,ini,fin));
            }
            if (parti.first() == "DATI"){
                //Data,Traffico
                temp=parti.at(2).trimmed();
                if (temp=="")continue; //Traffico dati nullo
                this->inserisci(new TrafficoDati(d,temp.toInt()));

            }
        }
    }
}

void Bolletta::svuota(){
    clear(); //Cancella la lista
    emit destroyed();
}



bool Bolletta::FuntoreBolletta::operator()(const VoceBollettaPtr& a, const VoceBollettaPtr& b) const{
    const Telefonata* t1,*t2;
    const TrafficoDati* d1,*d2;

    if (tipoRicerca == RicercaStandard) return a == b;

    if (tipoRicerca == RicercaTipo){
        if (tipoDato==TipoTutti) return true; //Se il parametro di ricerca e' il tipo e mi va bene qualsiati tipo, c'e' sempre un match.
        if (tipoDato== TipoTelefonata){
            t1=dynamic_cast<const Telefonata*>(&*a);
            t2=dynamic_cast<const Telefonata*>(&*b);
            return t1 && t2;
        }
        if (tipoDato== TipoTrafficoDati){
            d1=dynamic_cast<const TrafficoDati*>(&*a);
            d2=dynamic_cast<const TrafficoDati*>(&*b);
            return d1 && d2;
        }

    }

    if (tipoRicerca == RicercaCampoData){
        if (tipoDato == TipoTutti) return a->getData() == b->getData();

        if (tipoDato== TipoTelefonata){
            t1=dynamic_cast<const Telefonata*>(&*a);
            t2=dynamic_cast<const Telefonata*>(&*b);
            return t1 && t2 && t1->getData() == t2->getData();
        }
        if (tipoDato== TipoTrafficoDati){
            d1=dynamic_cast<const TrafficoDati*>(&*a);
            d2=dynamic_cast<const TrafficoDati*>(&*b);
            return d1 && d2 && d1->getData() == d2->getData();
        }
    }

    if (tipoRicerca==RicercaCampoNumero){
        t1=dynamic_cast<const Telefonata*>(&*a);
        t2=dynamic_cast<const Telefonata*>(&*b);
        return t1 && t2 && t1->getNumero() == t2->getNumero();
    }

    if (tipoRicerca==RicercaCampiDataNumero){
        t1=dynamic_cast<const Telefonata*>(&*a);
        t2=dynamic_cast<const Telefonata*>(&*b);
        return t1 && t2 && t1->getData() == t2->getData() && t1->getNumero() == t2->getNumero();

    }
    //Arrivo qui se l'oggetto creato e' stato creato in modo inconsistente
    return false;
}


