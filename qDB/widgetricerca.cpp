#include "widgetricerca.h"
#include <QDebug>
WidgetRicerca::WidgetRicerca(QWidget *parent) :
    QWidget(parent)
{
    mainLayout= new QVBoxLayout();
    lblData=new QLabel("<b>Data:</b>");
    lblData->setMinimumWidth(110);
    lblData->setMaximumWidth(110);
    lblNumero=new QLabel("<b>Telefono:</b>");
    lblNumero->setMinimumWidth(110);
    lblNumero->setMaximumWidth(110);
    editData = new QDateEdit(QDate::currentDate());
    editData->setDisplayFormat("dd/MM/yyyy");
    editData->setMinimumWidth(130);
    checkData=new QCheckBox("");
    checkData->setChecked(false);
    txtNumero=new QLineEdit();
    checkTel=new QCheckBox("");
    checkTel->setChecked(false);
    checkTelefonata=new QCheckBox("Telefonata");
    checkTelefonata->setChecked(true);
    checkTrafficoDati = new QCheckBox("Traffico Dati");
    checkTrafficoDati->setChecked(true);
    btnCerca=new QPushButton("Filtra");
    btnCerca->setMaximumWidth(120);
    btnAnnulla=new QPushButton("Pulisci");
    btnAnnulla->setMaximumWidth(120);

    QHBoxLayout *rigaData,*rigaNumero;
    QVBoxLayout *colonnaCampi,*colonnaCheck;

    rigaData=new QHBoxLayout();
    rigaData->addWidget(lblData);
    rigaData->addWidget(checkData);
    rigaData->addWidget(editData);
    //rigaData->addStretch();
    rigaNumero=new QHBoxLayout();
    rigaNumero->addWidget(lblNumero);
    rigaNumero->addWidget(checkTel);
    rigaNumero->addWidget(txtNumero);
    //rigaNumero->addStretch();

    colonnaCampi=new QVBoxLayout();
    colonnaCampi->addLayout(rigaData);
    colonnaCampi->addLayout(rigaNumero);;
    QGroupBox* boxCheck=new QGroupBox("Tipo:");
    colonnaCheck=new QVBoxLayout();
    colonnaCheck->addWidget(checkTelefonata);
    colonnaCheck->addWidget(checkTrafficoDati);
    boxCheck->setLayout(colonnaCheck);


    QHBoxLayout* rigaCerca=new QHBoxLayout();

    rigaCerca->addWidget(btnCerca);
    rigaCerca->addWidget(btnAnnulla);


    mainLayout->addLayout(colonnaCampi);
    mainLayout->addWidget(boxCheck);
    mainLayout->addLayout(rigaCerca);

    setLayout(mainLayout);

    connect(checkTrafficoDati,SIGNAL(toggled(bool)),this,SLOT(fixControlState()));
    connect(checkTelefonata,SIGNAL(toggled(bool)),this,SLOT(fixControlState()));

    connect(checkData,SIGNAL(toggled(bool)),editData,SLOT(setEnabled(bool)));
    connect(checkTel,SIGNAL(toggled(bool)),txtNumero,SLOT(setEnabled(bool)));

    connect(btnCerca,SIGNAL(clicked()),this,SLOT(btnCerca_click()));
    connect(btnAnnulla,SIGNAL(clicked()),this,SIGNAL(annulla()));

    fixControlState();
}



void WidgetRicerca::fixControlState(){
    bool tel = checkTelefonata->isChecked();
    bool dati = checkTrafficoDati->isChecked();

    checkTel->blockSignals(true);
    checkTel->setChecked(!dati);
    checkTel->setEnabled(!dati);
    checkTel->blockSignals(false);

    txtNumero->setEnabled(tel && checkTel->isChecked() && !dati);

    btnCerca->setEnabled(tel || dati);
}

void WidgetRicerca::btnCerca_click(){
    int t;
    if (checkTelefonata->isChecked() && checkTrafficoDati->isChecked()){
        t=Bolletta::FuntoreBolletta::TipoTutti;
    }else{
        //se ho premuto il tasto cerca, almeno uno dei due checkbox e' abilitato,altrimenti il bottone non sarebbe cliccabile
        //inolre uno dei due checkbox non e' selezionato
        t = (checkTelefonata->isChecked())? Bolletta::FuntoreBolletta::TipoTelefonata : Bolletta::FuntoreBolletta::TipoTrafficoDati;
    }

    int c=0;
    QDate data=editData->date();
    QString numero=txtNumero->text();

    if (checkData->isChecked()) c += Bolletta::FuntoreBolletta::RicercaCampoData;
    if (checkTel->isChecked()) c += Bolletta::FuntoreBolletta::RicercaCampoNumero;

    //se entra in tutti e due gli if, deve fare la ricerca per entrambi i campi, c vale 3 == Bolletta::FuntoreBolletta::RicercaDataNumero
    Bolletta::FuntoreBolletta tipoRicerca(c,t);

    VoceBollettaPtr x;
    if (t == Bolletta::FuntoreBolletta::TipoTutti || t == Bolletta::FuntoreBolletta::TipoTelefonata)
        x = new Telefonata(numero.toStdString(),Data(data.day(),data.month(),data.year()),0,0);
    else
        x = new TrafficoDati(Data(data.day(),data.month(),data.year()),0);

    emit parametriRicerca(x,tipoRicerca);
}

