#ifndef WIDGETRESOCONTO_H
#define WIDGETRESOCONTO_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QGroupBox>

#include "Intervallo.h"

class WidgetResoconto : public QWidget
{
    Q_OBJECT
private:
    QLabel* lblTelefonate;
    QLabel* lblDati;
    QLabel* lblQuantita;
    QLabel* lblCosto;
    QLabel* lblCostoTotale;

    QLabel* lblQtaTelefonate;
    QLabel* lblCostoTelefonate;
    QLabel* lblQtaDati;
    QLabel* lblCostoDati;
    QLabel* lblTotale;

    QGridLayout* mainLayout;

public:
    explicit WidgetResoconto(QWidget *parent = 0);

signals:

public slots:
    void setQtaTelefonate(const Intervallo&);
    void setCostoTelefonate(double);
    void setQtaDati(long int);
    void setCostoDati(double);
    void setTotale(double);
};

#endif // WIDGETRESOCONTO_H
