'use strict';

var AppDispatcher = require('../Dispatcher/AppDispatcher');
var EventEmitter = require('events').EventEmitter;
var FiltersConstants = require('../Constants/FiltersConstants');
var assign = require('object-assign');

var CHANGE_EVENT = 'change';

var _filters = [];

function loadFilters(filters) {
  _filters = filters;
}

var FiltersStore = assign({}, EventEmitter.prototype, {

  getAll: function() {
    return _filters;
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

      case FiltersConstants.LOAD_FILTERS:
        console.log('Loading filters');
        loadFilters(action.filters);
        console.log(_filters);
        FiltersStore.emitChange();
        break;


      default:
        console.log('No actions');
        break;
    }

    return true; // No errors. Needed by promise in Dispatcher.
  })

});

module.exports = FiltersStore;
