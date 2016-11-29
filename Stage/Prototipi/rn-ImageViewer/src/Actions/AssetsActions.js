'use strict';

var AppDispatcher = require('../Dispatcher/AppDispatcher');
var AssetsConstants = require('../Constants/AssetsConstants');

var RedditFecher = require('../Utils/RedditFetcher');

var redditFecher = new RedditFecher();

var AssetsActions = {

  loadAssets: function(filter) {
    //Carica i dati in modo asincorno
    redditFecher.fetchData(filter)
      .then((responseData) => {

        var assets = responseData.data.children;

        AppDispatcher.handleViewAction({
          actionType: AssetsConstants.LOAD_ASSETS,
          assets: assets
        });
      })
      .done();
  },

  loadMoreAssets: function(filter) {

    redditFecher.fetchMoreData(filter)
      .then((responseData) => {

        var assets = responseData.data.children;

        AppDispatcher.handleViewAction({
          actionType: AssetsConstants.LOAD_MORE_ASSETS,
          assets: assets
        });
      })
      .done();
  },

};

module.exports = AssetsActions;
