/*globals tabris:true*/
'use strict';
var smartImageView = tabris.create('Composite', {
  layoutData: {top:0, bottom:0, left:320, right:0},
  image:'https://i.redditmedia.com/AwBlkJQ4GTke_xesIQX9NSV02yjnbMFZ9p-rPVZ3q7w.jpg?s=0393037002fa293a0fc386957cfc22e4'
});

var placeHolder = tabris.create('TextView',{
  id:'placeHolder',
  layoutData:{top:0,left:0,bottom:0,right:0},
  text:'<strong>Non è ancora stata selezionata un\'immagine</strong>',
  alignment:'center',
  markupEnabled:true
}).appendTo(smartImageView);

smartImageView.setImage = function (url) {
  var imageViews = this.find('#imageView');
  var imageView;
  if (imageViews.length === 0){
    //Non ho ancora creato l'imageView
    //Rimuovo il testo segna posto
    this.find('#placeHolder')[0].dispose();

    //Creo l'imageView
    imageView = tabris.create('ImageView',{
      id:'imageView',
      layoutData:{top:0,left:0,bottom:0,right:0},
      image:url
    });
    //Creo la scritta caricamento in corso
    var loading = tabris.create('TextView',{
      layoutData:{top:0,left:0,bottom:0,right:0},
      text:'Caricamento in corso ...',
      alignment:'center'
    });
    smartImageView.append(loading, imageView);
  }else {
    //Ho già creato l'ImageView, aggiorno l'url dell'immagine
    imageViews[0].set('image',url);
  }
};


module.exports = smartImageView;
