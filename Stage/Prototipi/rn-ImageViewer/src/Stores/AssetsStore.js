'use strict';

var AppDispatcher = require('../Dispatcher/AppDispatcher');
var EventEmitter = require('events').EventEmitter;
var AssetsConstants = require('../Constants/AssetsConstants');
var assign = require('object-assign');

var CHANGE_EVENT = 'change';

var _assets = [];

function loadAssets(assets) {
  _assets = assets;
}

function loadMoreAssets(assets){
  assets.forEach((item) => _assets.push(item));
}

var AssetsStore = assign({}, EventEmitter.prototype, {

  getAll: function() {
    return _assets;
  },

  emitChange: function() {
    this.emit(CHANGE_EVENT);
  },

  addChangeListener: function(callback) {
    this.on(CHANGE_EVENT, callback);
  },

  removeChangeListener: function(callback) {
    this.removeListener(CHANGE_EVENT, callback);
  },

  dispatcherIndex: AppDispatcher.register(function(payload) {
    console.log(payload);
    var action = payload.action;


    switch(action.actionType) {

      case AssetsConstants.LOAD_ASSETS:
        console.log('Loading assets');
        loadAssets(action.assets);
        AssetsStore.emitChange();
        break;

      case AssetsConstants.LOAD_MORE_ASSETS:
        console.log('Loading more assets');
        loadMoreAssets(action.assets);
        AssetsStore.emitChange();
        break;

      default:
        console.log('No actions');
        break;
    }

    return true; // No errors. Needed by promise in Dispatcher.
  })

});

module.exports = AssetsStore;
