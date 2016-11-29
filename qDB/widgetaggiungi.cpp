#include "widgetaggiungi.h"

#include "QMessageBox"

WidgetAggiungi::WidgetAggiungi(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Aggiungi voce...");


    //Data
    lblData = new QLabel("Data:");
    editData = new QDateEdit(QDate::currentDate());
    editData->setDisplayFormat("dd/MM/yyyy");
    layoutData = new QHBoxLayout();

    layoutData->addWidget(lblData);
    layoutData->addWidget(editData);

    //RadioButton
    radioTelefonata = new QRadioButton("Telefonata");
    radioTelefonata->setChecked(true);
    radioTrafficoDati = new QRadioButton("Traffico Dati");
    layoutRadio = new QHBoxLayout();
    layoutRadio->addWidget(radioTelefonata);
    layoutRadio->addWidget(radioTrafficoDati);

    //Telefonata
    lblOrarioInizio= new QLabel("Orario inizio:");
    lblOrarioFine= new QLabel("Orario Fine:");
    lblNumero= new QLabel("Numero:");
    timeEditInizio = new QTimeEdit();
    timeEditFine= new QTimeEdit();
    txtNumero= new QLineEdit();

    lblAvvisoOrario=new QLabel("<i>La telefonata finisce il giorno successivo</i>");
    lblAvvisoOrario->setVisible(false);
    layoutTelefonata= new QGridLayout();

    layoutTelefonata->addWidget(lblNumero,0,0);
    layoutTelefonata->addWidget(txtNumero,0,1);
    layoutTelefonata->addWidget(lblOrarioInizio,1,0);
    layoutTelefonata->addWidget(timeEditInizio,1,1);
    layoutTelefonata->addWidget(lblOrarioFine,2,0);
    layoutTelefonata->addWidget(timeEditFine,2,1);;
    layoutTelefonata->addWidget(lblAvvisoOrario,3,0,1,2);

    widgetTelefonata = new QWidget();
    widgetTelefonata->setLayout(layoutTelefonata);


    //TrafficoDati
    lblMega=new QLabel("Megabyte:");
    txtMega= new QLineEdit();
    layoutTrafficoDati=new QGridLayout();
    layoutTrafficoDati->addWidget(lblMega,0,0);
    layoutTrafficoDati->addWidget(txtMega,0,1);

    widgetTrafficoDati = new QWidget();
    widgetTrafficoDati->setLayout(layoutTrafficoDati);
    widgetTrafficoDati->setVisible(false);

    //Bottoni
    btnAggiungi = new QPushButton("Aggiungi");
    btnAnnulla = new QPushButton("Annulla");

    layoutBottoni = new QHBoxLayout();
    layoutBottoni->addWidget(btnAggiungi);
    layoutBottoni->addWidget(btnAnnulla);

    //Layout Principale
    mainLayout=new QVBoxLayout();
    mainLayout->addLayout(layoutData);
    mainLayout->addLayout(layoutRadio);
    mainLayout->addWidget(widgetTelefonata);
    mainLayout->addWidget(widgetTrafficoDati);
    mainLayout->addStretch();
    mainLayout->addLayout(layoutBottoni);

    setLayout(mainLayout);

    //Connessioni

    connect(radioTelefonata,SIGNAL(toggled(bool)),widgetTelefonata,SLOT(setVisible(bool)));
    connect(radioTrafficoDati,SIGNAL(toggled(bool)),widgetTrafficoDati,SLOT(setVisible(bool)));

    connect(timeEditInizio,SIGNAL(timeChanged(QTime)),this,SLOT(orarioChanged()));
    connect(timeEditFine,SIGNAL(timeChanged(QTime)),this,SLOT(orarioChanged()));

    connect(btnAggiungi,SIGNAL(clicked()),this,SLOT(btnAggiungi_click()));
    connect(btnAnnulla,SIGNAL(clicked()),this,SLOT(reject()));

}
#include <QDebug>

void WidgetAggiungi::btnAggiungi_click(){
    QDate data=editData->date();
    Data dataVoce(data.day(),data.month(),data.year());

    if (radioTelefonata->isChecked()){
        QString numTemp=txtNumero->text();
        string num = numTemp.toStdString();
        QTime tInizio=timeEditInizio->time();
        QTime tFine=timeEditFine->time();
        int sec=tInizio.hour()*3600+tInizio.minute()*60+tInizio.second();
        Orario inizio(sec);
        sec=tFine.hour()*3600+tFine.minute()*60+tFine.second();
        Orario fine(sec);

        Numero n(num);
        if (n.isValid()){
            if (tInizio==tFine){
                QMessageBox msgBox;
                msgBox.setText("L'orario d'inizio coincide con l'orario di fine");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();
            }
            else{
                nuovaVoce = new Telefonata(n,dataVoce,inizio,fine);
                this->accept();
            }
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Numero di telefono non valido");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
    }
    if (radioTrafficoDati->isChecked()){
        int mb=txtMega->text().toInt();
        if (mb > 0){
            nuovaVoce=new TrafficoDati(dataVoce,mb);
            this->accept();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Hai inserito un traffico dati negativo o nullo");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
    }
}

void WidgetAggiungi::orarioChanged(){
    QTime inizio=timeEditInizio->time();
    QTime fine=timeEditFine->time();
    if (inizio<=fine) lblAvvisoOrario->setVisible(false);
    else lblAvvisoOrario->setVisible(true);
}

VoceBollettaPtr WidgetAggiungi::getNuovaVoce()const{
    return nuovaVoce;
}
