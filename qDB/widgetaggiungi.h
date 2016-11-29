#ifndef WIDGETAGGUNGI_H
#define WIDGETAGGUNGI_H

#include <QDialog>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QLabel>

#include "VoceBollettaPtr.h"
#include "Telefonata.h"
#include "TrafficoDati.h"

class WidgetAggiungi : public QDialog
{
    Q_OBJECT
private:
    VoceBollettaPtr nuovaVoce;
protected:
    QPushButton* btnAggiungi;
    QPushButton* btnAnnulla;

    QLabel* lblData;
    QDateEdit* editData;

    QRadioButton* radioTelefonata;
    QRadioButton* radioTrafficoDati;


    QLabel* lblOrarioInizio;
    QLabel* lblOrarioFine;
    QLabel* lblNumero;
    QTimeEdit* timeEditInizio;
    QTimeEdit* timeEditFine;
    QLineEdit* txtNumero;
    QWidget* widgetTelefonata;


    QLabel* lblMega;
    QLineEdit* txtMega;
    QWidget* widgetTrafficoDati;


    QHBoxLayout* layoutBottoni;
    QHBoxLayout* layoutData;
    QHBoxLayout* layoutRadio;

    QGridLayout* layoutTelefonata;
    QGridLayout* layoutTrafficoDati;
    QVBoxLayout* mainLayout;

    QLabel* lblAvvisoOrario;

private slots:
    void btnAggiungi_click();
    void orarioChanged();
public:
    WidgetAggiungi(QWidget *parent = 0);
    VoceBollettaPtr getNuovaVoce() const;
signals:

public slots:

};

#endif // WIDGETAGGUNGI_H
