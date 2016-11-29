#ifndef BOLLETTA_H
#define BOLLETTA_H

#include <QObject>
#include <QTextStream>

#include "container.h"
#include "VoceBolletta.h"
#include "VoceBollettaPtr.h"
#include "Intervallo.h"
#include "Telefonata.h"
#include "TrafficoDati.h"

class Bolletta : public QObject, public Container<VoceBollettaPtr>
{
    Q_OBJECT
private:
public:
    class FuntoreBolletta{
    private:
        int tipoRicerca;
        int tipoDato;
    public:
        enum {RicercaStandard=-1,RicercaTipo=0, RicercaCampoData=1, RicercaCampoNumero=2,RicercaCampiDataNumero=3};
        enum {TipoTelefonata=0,TipoTrafficoDati,TipoTutti};
        FuntoreBolletta(int r=0,int t=0) : tipoRicerca(r), tipoDato(t){}
        bool operator()(const VoceBollettaPtr&,const VoceBollettaPtr&) const;
    };

    Bolletta(QObject* parent=0):QObject(parent) {}
    Bolletta(Container<VoceBollettaPtr> c,QObject* parent=0):QObject(parent),Container<VoceBollettaPtr>(c){}
    Bolletta(const Bolletta& b):QObject(b.parent()),Container<VoceBollettaPtr>(b){}
    ~Bolletta(){ emit destroyed();}

    Intervallo durataTelefonateTot()const;
    long int quantitaDatiTot() const; //vmax = 2 alla 31 -1
    double costoTelefonateTot() const;
    double costoDatiTot() const;
    double costoTotale() const;

signals:
    void itemAdded(const VoceBollettaPtr&) const; //Marcato const per poter essere emesso da resync()
    void itemRemoved(int);
    void itemUpdated(int,const VoceBollettaPtr&);
    void dataChanged()const;
    void destroyed() const;

public slots:
    void inserisci(const VoceBollettaPtr&); //Inserimento in coda
    void inserisciBolletta(const Bolletta&);

    void elimina(int);  //Nasconde elimina(iteratore)
    void elimina(const Iteratore&);
    void modifica(int,const VoceBollettaPtr&); //Posizione, Nuovo valore, nasconde modifica(K,K)
    Bolletta* cerca(const VoceBollettaPtr&,const FuntoreBolletta&) const;

    const VoceBollettaPtr itemAtIndex(int) const; //Nascondono le funzioni itemAtIndex di Container
    VoceBollettaPtr itemAtIndex(int);

    void salva(QTextStream&) const;
    void carica(QTextStream&);
    void svuota();

    void resync()const; //emette un segnale destroyed() seguito da tanti itemAdded()

};
#endif
