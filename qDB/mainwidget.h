#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "listbollettawidget.h"
#include "widgetaggiungi.h"

#include "Bolletta.h"
#include "Telefonata.h"
#include "TrafficoDati.h"
#include "Orario.h"
#include "Data.h"
#include "widgetresoconto.h"
#include "widgetricerca.h"

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    ListBollettaWidget* listaVoci;
    QPushButton* btnAggiungi;
    QPushButton* btnElimina;
    QPushButton* btnModifica;
    QPushButton* btnSalva;
    QPushButton* btnCarica;
    QLabel* lblLista;
    QLabel* lblResoconto;
    WidgetResoconto* resocontoBolletta;
    QVBoxLayout* layoutBottoni;
    QVBoxLayout* layoutLista;
    QVBoxLayout* layoutBoxBolletta;
    QHBoxLayout* mainLayout;
    Bolletta* b;
    Bolletta* bollettaRisultato;
    WidgetRicerca* widgetRicerca;
    QLabel* lblRicerca;
    bool inRicerca;

public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:
    void btnAggiungi_click();
    void btnElimina_click();
    void btnModifica_click();
    void btnSalva_click();
    void btnCarica_click();

    void updateResoconto();

    void eseguiRicerca(const VoceBollettaPtr&, const Bolletta::FuntoreBolletta&);
    void pulisciRicerca();



};

#endif // MAINWIDGET_H
