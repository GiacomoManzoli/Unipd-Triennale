#include "widgetmodifica.h"

WidgetModifica::WidgetModifica(VoceBollettaPtr t, QWidget* parent):WidgetAggiungi(parent)
{
    this->setWindowTitle("Modifica");
    this->mainLayout->removeItem(layoutRadio); //tolgo la parte dei radiobutton

    this->btnAggiungi->setText("Modifica");

    //Imposto la data
    Data d= t->getData();
    QDate dataTemp(d.getAnno(),d.getMese(),d.getGiorno());
    editData->setDate(dataTemp);

    Telefonata* p = dynamic_cast<Telefonata*>(&(*t));
    if (p){//l'oggetto da modificare e' una telefonata o un suo sottotipo
        widgetTrafficoDati->setVisible(false);
        widgetTelefonata->setVisible(true);
        //Anche se non sono visibili, influenzano quando devo costruire il nuovo oggetto modificato
        radioTrafficoDati->setChecked(false);
        radioTelefonata->setChecked(true);
        txtNumero->setText(QString::fromStdString(p->getNumero()));

        QTime time;
        Orario t2=p->getOrarioInizio();
        time.setHMS(t2.ore(),t2.minuti(),t2.secondi());
        timeEditInizio->setTime(time);
        t2=p->getOrarioFine();
        time.setHMS(t2.ore(),t2.minuti(),t2.secondi());
        timeEditFine->setTime(time);
    }
    TrafficoDati* traf=dynamic_cast<TrafficoDati*>(&(*t));
    if (traf){
        widgetTrafficoDati->setVisible(true);
        widgetTelefonata->setVisible(false);
        txtMega->setText(QString::number(traf->getDati()));
        //Anche se non sono visibili, influenzano quando devo costruire il nuovo oggetto modificato
        radioTrafficoDati->setChecked(true);
        radioTelefonata->setChecked(false);
    }
}
