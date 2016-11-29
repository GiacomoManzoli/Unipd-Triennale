/*globals tabris:true*/
'use strict';

//Per il momento non idee migliori di questa:
//Chi usa un l'oggetto collectionView deve definire i seguenti metodi:
// - loadMoreData
// - loadData
// - onItemSelect


var collectionView = tabris.create('CollectionView', {
  layoutData: {left: '#separator', top: 0, right:0, bottom:0},
  itemHeight: 156,
  refreshEnabled: true,
  background:'#e3e3e3',
  initializeCell: function(cell) {
    var container = tabris.create('Composite',{
      layoutData:{top:3,bottom:3,right:6,left:6},
      background:'#fafafa'
    }).appendTo(cell);

    var imageView = tabris.create('ImageView', {
      layoutData: {left: 6, top: 6, width: 138, height: 138},
      scaleMode: 'fill'
    }).appendTo(container);
    var titleView = tabris.create('TextView', {
      id:'titleView',
      layoutData:{
        top:6,
        left:150,
        right:6
      },
      maxLines: 2,
      font:'bold 18px sans-serif'
    }).appendTo(container);
    var authorView = tabris.create('TextView', {
      id:'authorView',
      layoutData: {
        top: ['#titleView',6],
        left: 150
      },
      textColor: '#234'
    }).appendTo(container);
    var commentsView = tabris.create('TextView', {
      layoutData: {
        top:['#authorView', 6],
        left:150
      },
      alignment: 'right',
      textColor: 'green'
    }).appendTo(container);
    cell.on('change:item', function(widget, item) {
      if (item.loading) {
        cell.children().set('visible', false);
        titleView.set({visible: true, text: 'Loading ...'});
        collectionView.loadMoreData();
      } else {
        cell.children().set('visible', true);
        imageView.set('image', item.data.thumbnail);
        titleView.set('text', item.data.title);
        authorView.set('text', item.data.author);
        commentsView.set('text', item.data.num_comments + ' comments');
      }
    });
  }
});

collectionView.on('refresh', function() {
  this.loadData();
}).on('select', function(target, value) {
  if (!value.loading) {
    this.onItemSelect(target,value);
  }
});


module.exports = collectionView;
