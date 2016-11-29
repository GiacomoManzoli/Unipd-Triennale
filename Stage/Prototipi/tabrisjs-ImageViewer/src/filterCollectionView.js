/*globals tabris:true*/
'use strict';
/* CollectionView per la lista dei filtri, al momento i dati sono hard-coded */
var filterCollection = tabris.create('CollectionView',{
  id:'filterCollection',
  layoutData: {
    top:0,
    bottom:0,
    left:0,
    width:280
  },
  refreshEnabled:false,
  itemHeight:50,
  background:'#e3e3e3',
  initializeCell: function(cell){
    var titleText = tabris.create('TextView', {
      layoutData:{
        left:6,
        centerY:0
      },
      font:'24px sans-serif'
    });
    cell.append(titleText);
    /* Creo un componente per fare da separtore tra le celle */
    tabris.create('Composite', {
                layoutData: {
                    left: 0,
                    bottom: 0,
                    right: 0,
                    height: 1
                },
                background: '#546E7A'
            }).appendTo(cell);

    cell.on('change:item',function (widget,item) {
      titleText.set('text',item.filterName);
    });
  },
  items:[
    { filterName:'Pet pictures', filter:'petpictures' },
    { filterName:'Earth pictures', filter:'EarthPorn'}
  ]
});
/* Qunado seleziono un filtro aggiorno i dati dalla tabella */
filterCollection.on('select',function (target,value){
  this.onItemSelect(target,value);
});

module.exports = filterCollection;
