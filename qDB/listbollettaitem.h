#ifndef LISTBOLLETTAITEM_H
#define LISTBOLLETTAITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "VoceBollettaPtr.h"
#include "VoceBolletta.h"
#include "TrafficoDati.h"
#include "Telefonata.h"



class ListBollettaItem : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout* mainLayout;
public:
    ListBollettaItem(VoceBollettaPtr ptr,QWidget *parent = 0);
};

#endif // LISTBOLLETTAITEM_H
