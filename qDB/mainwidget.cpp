#include "mainwidget.h"
#include <QMessageBox>
#include "widgetmodifica.h"

#include <QFileDialog>
#include <QFile>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    inRicerca=false;
    b= new Bolletta();
    bollettaRisultato = new Bolletta();

    // Parte dedicata ai bottoni
    btnAggiungi = new QPushButton("Aggiungi");
    btnAggiungi->setMinimumHeight(30);
    btnElimina = new QPushButton("Elimina");
    btnElimina->setMinimumHeight(30);
    btnElimina->setEnabled(false);
    btnModifica = new QPushButton("Modifica");
    btnModifica->setMinimumHeight(30);
    btnModifica->setEnabled(false);
    btnSalva = new QPushButton("Salva");
    btnSalva->setMinimumHeight(30);
    btnSalva->setMaximumWidth(120);
    btnCarica = new QPushButton("Carica");
    btnCarica->setMinimumHeight(30);
    btnCarica->setMaximumWidth(120);

    widgetRicerca=new WidgetRicerca();

    QHBoxLayout* layoutSalvaCarica=new QHBoxLayout();
    layoutSalvaCarica->addWidget(btnSalva);
    layoutSalvaCarica->addWidget(btnCarica);


    layoutBottoni= new QVBoxLayout();

    layoutBottoni->addWidget(btnAggiungi);
    layoutBottoni->addWidget(btnModifica);
    layoutBottoni->addWidget(btnElimina);
    layoutBottoni->addSpacing(20);
    layoutBottoni->addLayout(layoutSalvaCarica);
    layoutBottoni->addSpacing(20);
    layoutBottoni->addWidget(new QLabel("<h3>Filtra:</h3>"));
    layoutBottoni->addWidget(widgetRicerca);

    resocontoBolletta=new WidgetResoconto();
    lblResoconto=new QLabel("<h3>Resoconto bolletta:</h3>");
    layoutBottoni->addWidget(lblResoconto);
    layoutBottoni->addWidget(resocontoBolletta);
    layoutBottoni->addStretch();

    QWidget* colonnaSinistra= new QWidget();
    colonnaSinistra->setLayout(layoutBottoni);
    colonnaSinistra->setMaximumWidth(300);


    // Parte dedicata alla lista
    listaVoci= new ListBollettaWidget();
    listaVoci->setMinimumWidth(660);
    listaVoci->setMinimumHeight(400);
    lblLista=new QLabel("<h3>Voci bolletta:</h3>");
    lblRicerca= new QLabel("<i>Filtro attivo</i>");
    lblRicerca->setVisible(false);

    layoutLista = new QVBoxLayout();
    QHBoxLayout* layoutLabelLista=new QHBoxLayout();
    layoutLabelLista->addWidget(lblLista);
    layoutLabelLista->addSpacing(20);
    layoutLabelLista->addWidget(lblRicerca);
    layoutLabelLista->addStretch();
    layoutLista->addLayout(layoutLabelLista);
    layoutLista->addWidget(listaVoci);

    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(colonnaSinistra);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(layoutLista);

    setLayout(mainLayout);

    //connect per Widget-Widget
    connect(btnAggiungi,SIGNAL(clicked()),this,SLOT(btnAggiungi_click()));
    connect(btnElimina,SIGNAL(clicked()),this,SLOT(btnElimina_click()));
    connect(btnModifica,SIGNAL(clicked()),this,SLOT(btnModifica_click()));
    connect(btnSalva,SIGNAL(clicked()),this,SLOT(btnSalva_click()));
    connect(btnCarica,SIGNAL(clicked()),this,SLOT(btnCarica_click()));

    connect(widgetRicerca,SIGNAL(parametriRicerca(VoceBollettaPtr,Bolletta::FuntoreBolletta)),this,SLOT(eseguiRicerca(VoceBollettaPtr,Bolletta::FuntoreBolletta)));
    connect(widgetRicerca,SIGNAL(annulla()),this,SLOT(pulisciRicerca()));

    connect(listaVoci,SIGNAL(itemSelected(bool)),btnElimina,SLOT(setEnabled(bool)));
    connect(listaVoci,SIGNAL(itemSelected(bool)),btnModifica,SLOT(setEnabled(bool)));
    connect(listaVoci,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(btnModifica_click()));

    //connect per Dati-Widget
    connect(b,SIGNAL(itemAdded(VoceBollettaPtr)),listaVoci,SLOT(addNewItem(VoceBollettaPtr)));
    connect(b,SIGNAL(itemRemoved(int)),listaVoci,SLOT(removeIndex(int)));
    connect(b,SIGNAL(itemUpdated(int,VoceBollettaPtr)),listaVoci,SLOT(updateIndex(int,VoceBollettaPtr)));
    connect(b,SIGNAL(dataChanged()),this,SLOT(updateResoconto()));
    connect(b,SIGNAL(destroyed()),listaVoci,SLOT(clear()));

    connect(bollettaRisultato,SIGNAL(itemAdded(VoceBollettaPtr)),listaVoci,SLOT(addNewItem(VoceBollettaPtr)));
    connect(bollettaRisultato,SIGNAL(itemRemoved(int)),listaVoci,SLOT(removeIndex(int)));
    connect(bollettaRisultato,SIGNAL(itemUpdated(int,VoceBollettaPtr)),listaVoci,SLOT(updateIndex(int,VoceBollettaPtr)));
    connect(bollettaRisultato,SIGNAL(destroyed()),listaVoci,SLOT(clear()));


    //DebugData
/*
    b->inserisci(new Telefonata(Numero("123"),Data(12,12,2012),123,321));
    b->inserisci(new Telefonata(Numero("111"),Data(12,12,2012),123,333));
    b->inserisci(new Telefonata(Numero("123"),Data(11,12,2012),123,666));*/
}

#include <QDebug>

void MainWidget::btnAggiungi_click(){
    WidgetAggiungi add;
    if (add.exec()){
        VoceBollettaPtr p = add.getNuovaVoce();
        if (!p.isEqual(0)){
            b->inserisci(p);
        }
    }
}

void MainWidget::btnElimina_click(){
    QMessageBox msgBox;
    msgBox.setText("Sei sicuro di voler cancellare la voce?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Ok){
        if (!inRicerca){
            int i=listaVoci->selectedIndex();
            b->elimina(i);
        }
        else{
            int i=listaVoci->selectedIndex();
            VoceBollettaPtr daEliminare=bollettaRisultato->itemAtIndex(i);
            Bolletta::Iteratore it=b->ricerca(daEliminare);

            b->blockSignals(true);  //Blocco il segnale itemRemoved per evitare un aggiornamento inutile della GUI
            b->elimina(it);         //viene bloccato anche dataChanged che era necessario per tenere aggiornata la parte del resoconto che, di conseguenza, deve essere aggiornata manualmente
            b->blockSignals(false);
            updateResoconto();
            bollettaRisultato->elimina(i);

        }
    }
}

void MainWidget::btnModifica_click(){
    int i=listaVoci->selectedIndex();
    VoceBollettaPtr vecchiaVoce=(inRicerca)?bollettaRisultato->itemAtIndex(i):b->itemAtIndex(i);
    WidgetModifica wEdit(vecchiaVoce);
    if (wEdit.exec()){
        VoceBollettaPtr nuovaVoce = wEdit.getNuovaVoce();
        if (!inRicerca){
            b->modifica(i,nuovaVoce);
        }
        else{
            VoceBollettaPtr daModificare=bollettaRisultato->itemAtIndex(i);
            Bolletta::Iteratore it=b->ricerca(daModificare);
            *it=nuovaVoce; //Non genera segnali da bloccare
            this->updateResoconto(); //Devo aggiornare la schermata di resoconto manualmente
            bollettaRisultato->modifica(i,nuovaVoce);
        }
    }
}



void MainWidget::btnSalva_click(){
    QString fileName=QFileDialog::getSaveFileName(this,"Salva","","Bolletta (*.bol)");
    if (!fileName.endsWith(".bol")) fileName.append(".bol");
    QFile file(fileName);

    if (file.open(QFile::WriteOnly)){
        QTextStream stream(&file);
        b->salva(stream);
    }
}

void MainWidget::btnCarica_click(){
    QString fileName=QFileDialog::getOpenFileName(this,"Carica","","Bolletta (*.bol)");

    QFile file(fileName);

    if (file.open(QFile::ReadOnly)){
        inRicerca=false;
        lblRicerca->setVisible(false);
        QTextStream stream(&file);
        b->svuota();
        b->carica(stream);
    }
}

void MainWidget::eseguiRicerca(const VoceBollettaPtr& x, const Bolletta::FuntoreBolletta& r){
    inRicerca=true;
    lblRicerca->setVisible(true);
    bollettaRisultato->svuota();
    listaVoci->clear();
    Bolletta* temp=b->cerca(x,r);
    bollettaRisultato->inserisciBolletta(*temp);
    if (bollettaRisultato->count()==0){
        QMessageBox msgBox;
        msgBox.setText("Nessun risultato trovato");
        msgBox.exec();
    }
    delete temp;


}
void MainWidget::pulisciRicerca(){
    bollettaRisultato->svuota();
    b->resync();
    inRicerca=false;
    lblRicerca->setVisible(false);
}




void MainWidget::updateResoconto(){
    resocontoBolletta->setQtaDati(b->quantitaDatiTot());
    resocontoBolletta->setCostoDati(b->costoDatiTot());
    resocontoBolletta->setQtaTelefonate(b->durataTelefonateTot());
    resocontoBolletta->setCostoTelefonate(b->costoTelefonateTot());
    resocontoBolletta->setTotale(b->costoTotale());
}
