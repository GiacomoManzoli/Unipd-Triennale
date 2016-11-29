/*globals Promise: true, fetch: false, tabris: true*/
'use strict';

//Imposto i colori della NavigationBar
tabris.ui.set({
  background:'#263238',
  textColor:'#fafafa'
});

var RedditFetcher = require('./redditFetcher');
var fetcher = new RedditFetcher();

//Filtro corrente, al momento specifica da quale reddit andare a recuperare le immagini
var currentFilter = 'petpictures';

//Creo l'oggetto Pagina
var page = tabris.create('Page', {
  title: 'ImageViewer',
  topLevel: true
});

//Funzioni Helper
function getRedditId(item) {
  return item ? item.kind + '_' + item.data.id : null;
}

function getLastId() {
  var items = collectionView.get('items');
  return getRedditId(items[items.length - 2]) || null;
}

/* CollectionView per la lista dei filtri, al momento i dati sono hard-coded */
var filterCollection = require('./filterCollectionView');

filterCollection.onItemSelect = function (target, value) {
  currentFilter = value.filter;
  collectionView.loadData();
};

/* Richiedo l'oggetto collectionView, rappresenta la lista di immagini che viene visualizzata a destra.
Al momento viene importato direttamente l'oggetto. Sarebbe più corretto importare una funzione che lo costruisce */
var collectionView = require('./imageCollectionView');

/* L'oggetto che importo ha bisogno di delle due funzioni per il caricamento dei dati.
Queste due funzioni devono essere implementate altrimenti viene sollevato un'errore.

Ho scelto questa strategia per provare a seprare la definizione del componente dalla sorgente dei dati.
*/

//Implemento il metodo per il caricamento dei dati
collectionView.loadData = function () {
  collectionView.set('refreshIndicator', true);
  fetcher.getData(currentFilter,{limit: 25})
    .then(function(json) {
      // Aggiungo un segnaposto per l'item che triggerà il refresh
      collectionView.set('items', json.data.children.concat({loading: true}));
      collectionView.set('refreshIndicator', false);
    });
};

//Implemento il metodo per il caricamento di un maggior numero di dati
collectionView.loadMoreData = function () {
  fetcher.getData(currentFilter,{
      limit: 25,
      after: getLastId()
    }).then(function(json) {
    // Aggiungo l'item che triggererà il download dei nuovi dati
    collectionView.insert(json.data.children.concat({loading: true}), -1);
    // Rimuovo il vecchio trigger
    collectionView.remove(-1);
  });
};

/* Per come è definito l'oggetto collectionView è necessario fornire una funzione per l'handling
della selezione di un'elemento dalla lista*/

//Implemento l'handler per il click su un elemento della lista
collectionView.onItemSelect = function(target, value) {
  if (!value.loading) {
    //detailView.setImage(value.data.url);
    console.log(value.data.url);
  }
};
/* Creo la linea separatrice tra la lista dei filtri e la lista delle immagini */
var separtor = tabris.create('CollectionView',{
  id:'separator',
  layoutData:{top:0,bottom:0,left:'#filterCollection',width:1},
  background:'#546E7A'
});

/* Creo la TabBar */
var tabBar = tabris.create('TabFolder', {
  layoutData: {top:0,left:0, bottom:0, right:0},
  background:'#263238',
  textColor:'#fafafa'
});

/* Creo la Tab 'Gallery' */
var galleryTab = tabris.create('Tab',{
  title:'Gallery'
  /* image: '...'*/
});

/* Le TabBar/Tab funzionano in modo strano, quando viene selezionata una Tab, non viene visualizzato un nuovo
 oggetto Page ma viene visualizzato un nuovo Widget e l'oggetto Page non subisce modifice.
 Creo quindi un Widget che andrà a contenere le due liste*/
var galleryView = tabris.create('Composite',{
  layoutData:{ top:0, left:0, right:0, bottom:0},
});
galleryView.append(filterCollection, separtor, collectionView);

/* Inserisco nella Tab la 'view' corrispondente */
galleryTab.append(galleryView);

/* Aggiungo la Tab alla TabBar*/
tabBar.append(galleryTab);
/* Selezione la Tab, questa istruzione sembra essere buggata in quanto l'elemento della TabBar assoicatio a
galleryTab non viene mostrato come attivo.*/
tabBar.set('selection', galleryTab);

/* Aggiunto la TabBar alla pagina*/
page.append(tabBar);

/* Visualizzo la pagina e scarico i dati*/
page.open();
collectionView.loadData();
