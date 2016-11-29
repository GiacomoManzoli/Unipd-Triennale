#ifndef LISTBOLLETTAWIDGET_H
#define LISTBOLLETTAWIDGET_H

#include <QListWidget>
#include <QString>
#include "VoceBollettaPtr.h"

class ListBollettaWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ListBollettaWidget(QWidget *parent = 0);
    int selectedIndex();

signals:
    void itemSelected(bool);
public slots:
    void selectedItemChanged(int);
    void addNewItem(const VoceBollettaPtr&);
    void removeIndex(int);
    void updateIndex(int,const VoceBollettaPtr&);
};

#endif // LISTBOLLETTAWIDGET_H
