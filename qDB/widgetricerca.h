#ifndef WIDGETRICERCA_H
#define WIDGETRICERCA_H

#include <QWidget>
#include <QDialog>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QDateEdit>

#include "listbollettawidget.h"

#include "Bolletta.h"


class WidgetRicerca : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;


    QLabel* lblData;
    QLabel* lblNumero;
    QDateEdit* editData;
    QLineEdit* txtNumero;

    QCheckBox* checkData;
    QCheckBox* checkTel;
    QCheckBox* checkTelefonata;
    QCheckBox* checkTrafficoDati;

    QPushButton* btnCerca;
    QPushButton* btnAnnulla;

public:
    explicit WidgetRicerca(QWidget *parent = 0);
signals:
    void parametriRicerca(const VoceBollettaPtr&, const Bolletta::FuntoreBolletta&);
    void annulla();
private slots:
    void fixControlState();
    void btnCerca_click();
public slots:

};

#endif // WIDGETRICERCA_H
