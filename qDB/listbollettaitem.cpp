#include "listbollettaitem.h"

#include <QGridLayout>

ListBollettaItem::ListBollettaItem(VoceBollettaPtr ptr, QWidget *parent) :
    QWidget(parent)
{
    mainLayout= new QHBoxLayout();
    /*Main layout viene diviso in 3 slot, il primo e l'ultimo in comune per la data e il costo, quello centrale per i campi specifici
     */
    QVBoxLayout* layoutSlot1 = new QVBoxLayout();
    QVBoxLayout* layoutSlot2 = new QVBoxLayout();
    QVBoxLayout* layoutSlot3 = new QVBoxLayout();
    mainLayout->addLayout(layoutSlot1);
    mainLayout->addLayout(layoutSlot2);
    mainLayout->addStretch();
    mainLayout->addLayout(layoutSlot3);

    QHBoxLayout* layoutGiorno= new QHBoxLayout();
    layoutGiorno->addWidget(new QLabel("<b>Giorno:</b>"));
    layoutGiorno->addWidget(new QLabel(QString::fromStdString(ptr->getData().toString())));
    layoutSlot1->addLayout(layoutGiorno);


    Telefonata* p = dynamic_cast<Telefonata*>(&(*ptr));
    if (p){
        //numero
        QHBoxLayout* rigaTelefono= new QHBoxLayout();
        rigaTelefono->addWidget(new QLabel("<b>Telefono #:</b>"));
        rigaTelefono->addWidget(new QLabel(QString::fromStdString(p->getNumero())));
        rigaTelefono->addStretch();
        //orari
        QHBoxLayout* rigaOrari = new QHBoxLayout();
        rigaOrari->addWidget(new QLabel("<b>Durata:</b>"));
        rigaOrari->addWidget(new QLabel(QString::fromStdString(p->durataTelefonata().toString())));
        rigaOrari->addWidget(new QLabel("<b>Inizio:</b>"));
        rigaOrari->addWidget(new QLabel(QString::fromStdString(p->getOrarioInizio().toString())));
        rigaOrari->addWidget(new QLabel("<b>Fine:</b>"));
        rigaOrari->addWidget(new QLabel(QString::fromStdString(p->getOrarioFine().toString())));
        layoutSlot2->addLayout(rigaTelefono);
        layoutSlot2->addLayout(rigaOrari);
    }
    TrafficoDati* traf=dynamic_cast<TrafficoDati*>(&(*ptr));
    if (traf){
        QHBoxLayout* rigaMb= new QHBoxLayout();
        rigaMb->addWidget(new QLabel("<b>MB:</b>"));
        rigaMb->addWidget(new QLabel(QString::number(traf->getDati())));
        layoutSlot2->addLayout(rigaMb);
    }
    QHBoxLayout* layoutCosto=new QHBoxLayout();
    layoutCosto->addWidget(new QLabel("<b>Costo:</b>"));
    layoutCosto->addWidget(new QLabel(QString::number(ptr->costo())));
    layoutSlot3->addLayout(layoutCosto);
    setLayout(mainLayout);

}
