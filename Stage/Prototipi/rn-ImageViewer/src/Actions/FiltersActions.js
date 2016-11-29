'use strict';

var AppDispatcher = require('../Dispatcher/AppDispatcher');
var FiltersConstants = require('../Constants/FiltersConstants');

var FiltersActions = {

  loadFilters: function() {

    var filters = [
      {filterName: 'Pet Pictures', filter:'petpictures'},
      {filterName: 'Earth Pictures', filter:'EarthPorn'},
      {filterName: 'Cute Pictures', filter:'aww'}
    ];

    AppDispatcher.handleViewAction({
      actionType: FiltersConstants.LOAD_FILTERS,
      filters: filters
    });
  }

};

module.exports = FiltersActions;
