#include "widgetresoconto.h"

WidgetResoconto::WidgetResoconto(QWidget *parent) :
    QWidget(parent)
{
    lblTelefonate= new QLabel("<b>Telefonate:</b>");
    lblTelefonate->setAlignment(Qt::AlignRight);
    lblDati= new QLabel("<b>Dati:</b>");
    lblDati->setAlignment(Qt::AlignRight);
    lblQuantita= new QLabel("<b>Quantita':</b>");
    lblCosto= new QLabel("<b>Costo:</b>");
    lblCostoTotale= new QLabel("<b>Totale:</b>");
    lblCostoTotale->setAlignment(Qt::AlignRight);

    lblQtaTelefonate= new QLabel("-");
    lblCostoTelefonate= new QLabel("-");
    lblQtaDati= new QLabel("-");
    lblCostoDati= new QLabel("-");
    lblTotale= new QLabel("-");

    QHBoxLayout* layoutAusiliario=new QHBoxLayout();
    mainLayout= new QGridLayout();
    mainLayout->addWidget(lblQuantita,0,1);
    mainLayout->addWidget(lblCosto,0,2);
    //
    mainLayout->addWidget(lblTelefonate,1,0);
    mainLayout->addWidget(lblQtaTelefonate,1,1);
    mainLayout->addWidget(lblCostoTelefonate,1,2);
    //
    mainLayout->addWidget(lblDati,2,0);
    mainLayout->addWidget(lblQtaDati,2,1);
    mainLayout->addWidget(lblCostoDati,2,2);
    mainLayout->addWidget(lblCostoTotale,3,1);
    mainLayout->addWidget(lblTotale,3,2);
    mainLayout->setHorizontalSpacing(30);

    layoutAusiliario->addLayout(mainLayout);
    layoutAusiliario->addStretch();
    setLayout(layoutAusiliario);


}


void WidgetResoconto::setQtaTelefonate(const Intervallo& i){
    lblQtaTelefonate->setText(QString::fromStdString(i.toString()));
}
void WidgetResoconto::setCostoTelefonate(double c){
    lblCostoTelefonate->setText(QString::number(c));
}
void WidgetResoconto::setQtaDati(long int d){
    lblQtaDati->setText(QString::number(d));
}
void WidgetResoconto::setCostoDati(double c){
    lblCostoDati->setText(QString::number(c));
}
void WidgetResoconto::setTotale(double c){
    lblTotale->setText(QString::number(c));
}
