'use strict';
var observableModule = require('data/observable');
var observableArrayModule = require('data/observable-array');
var httpModule = require('http');
var frameModule = require('ui/frame');

var model = new observableModule.Observable();
model.filters = new observableArrayModule.ObservableArray([]);
model.assets = new observableArrayModule.ObservableArray([]);
model.selectedFilter = null;

var after = '';

function pageLoaded(args) {
  var page = args.object;
  page.bindingContext = model;

  if (page.ios){
    var textColor = UIColor.colorWithRedGreenBlueAlpha(0.98, 0.98, 0.98, 1);
    var backgroundColor = UIColor.colorWithRedGreenBlueAlpha(0.15, 0.19, 0.22, 1);

    frameModule.topmost().ios.navBarVisibility='always';

    var controller = frameModule.topmost().ios.controller;

    controller.navigationBarHidden = false;
    page.ios.title = 'ImageViewer';
    //Colore di sfondo
    controller.navigationBar.barTintColor = backgroundColor;
    //Colore dei pulsanti
    controller.navigationBar.tintColor = textColor;
    controller.navigationBar.barStyle = 1; //UIStatusBarStyleLightContent
    controller.navigationBar.titleTextAttributes = new NSDictionary([textColor], [NSForegroundColorAttributeName]);

    /* Definisco una nuova classe che estende NSObject per poter gestire gli eventi del pulsante a sinistra della NavBar */
    var TapHandler = NSObject.extend({
      handle: function () {
        console.log('tapped');
      }
    }, {
      name:'TapHandler',
      exposedMethods: {
        handle: {returns: interop.types.void}
      }
    });
    //Creo l'oggetto
    var tapHandler = TapHandler.alloc().init();
    /* Questa cosa non funziona, peccato. */
    //tapHandler.handle = function() { console.log('Overrided tap handler'); };

    /* Per qualche strano motivo, se rimuvo questo console.log, l'applicazione crasha */
    console.log(tapHandler);

    // UINavigationItem https://developer.apple.com/library/ios/documentation/UIKit/Reference/UINavigationItem_Class/index.html#//apple_ref/doc/c_ref/UINavigationItem
    /* L'handler deve per forza essere un oggetto nativo, e deve essorre il metodo handle.
    Per quanto riguarda la personalizzazione, è possibile spingergi oltre, utilizzando il costruttore initWithView, che permette di creare il pulsante a partire da una UIView*/
    controller.navigationBar.topItem.leftBarButtonItem = new UIBarButtonItem().initWithTitleStyleTargetAction('Filter',2, tapHandler, 'handle');

    /* Non c'è un modo ad alto livello per andare a settare il colore della tabBar
    * devo quindi utilizzare le API di iOS per poterlo andare a settare a mano
    */
    var tabView = page.getViewById('tabView');
    var tabBarController = tabView.ios;
    //#263238 --> 38,50,56
    tabBarController.tabBar.barTintColor = backgroundColor;
    tabBarController.tabBar.tintColor = textColor;
  }

  model.filters.push({title:'Pet pictures', filter:'petpictures'});
  model.filters.push({title:'Earth pictures', filter:'EarthPorn'});
  model.filters.push({title:'Cute pictures', filter:'aww'});

  model.selectedFilter = model.filters.getItem(0);
  loadAssets();
}

//Carica gli asset da model.selectedFilter
function loadAssets() {
  var url = 'http://www.reddit.com/r/'+model.selectedFilter.filter+'.json?after=';
  httpModule.getJSON(url).then(function (response) {
    response.data.children.forEach(function (item) {
      if (item.data.thumbnail.match(/.jpg/)){
        model.assets.push({
          title:item.data.title,
          url: item.data.thumbnail,
          author: item.data.author,
          comments: item.data.num_comments
        });
      }
    });
  });
}

function filterListTap (args) {
  var filter = model.filters.getItem(args.index);
  if (model.selectedFilter !== filter){
    model.assets.splice(0, model.assets.length);
    model.selectedFilter = filter;
    loadAssets();
  }
}

exports.pageLoaded = pageLoaded;
exports.loadAssets = loadAssets;
exports.filterListTap = filterListTap;
