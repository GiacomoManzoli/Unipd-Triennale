#ifndef WIDGETMODIFICA_H
#define WIDGETMODIFICA_H

#include "widgetaggiungi.h"
#include "VoceBollettaPtr.h"
#include "VoceBolletta.h"
#include "Telefonata.h"
#include "TrafficoDati.h"


/*
 * Cambia leggermente la grafica, tutta la logica di funzionamento la eredita da WidgetAggiungi
*/
class WidgetModifica : public WidgetAggiungi
{
public:
    WidgetModifica(VoceBollettaPtr ptr,QWidget* parent=0);
};

#endif // WIDGETMODIFICA_H
