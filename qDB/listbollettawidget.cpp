#include "listbollettawidget.h"
#include "listbollettaitem.h"

ListBollettaWidget::ListBollettaWidget(QWidget *parent) :
    QListWidget(parent)
{
    connect(this,SIGNAL(currentRowChanged(int)),this,SLOT(selectedItemChanged(int)));
}


//SLOT
void ListBollettaWidget::addNewItem(const VoceBollettaPtr& p){
    QListWidgetItem* item=new QListWidgetItem();
    item->setSizeHint(QSize(0,55));
    this->addItem(item);
    this->setItemWidget(item,new ListBollettaItem(p));

}
#include <QDebug>
void ListBollettaWidget::removeIndex(int i){
    //this->removeItemWidget(item(i)); //sembra non funzionare
    QListWidgetItem* t = this->takeItem(i); //questo fa il suo lavoro, stando alla documentazione Qt, l'item rimosso deve essere deallocato manualmente
    delete t;
    setCurrentRow(-1);

}
void ListBollettaWidget::updateIndex(int i,const VoceBollettaPtr& p){
    this->removeIndex(i);
    QListWidgetItem* item=new QListWidgetItem();
    item->setSizeHint(QSize(0,55));
    this->insertItem(i,item);
    this->setItemWidget(item,new ListBollettaItem(p));
}

void ListBollettaWidget::selectedItemChanged(int i){
    emit itemSelected(i != -1);
}

int ListBollettaWidget::selectedIndex(){
    return currentRow();
}

