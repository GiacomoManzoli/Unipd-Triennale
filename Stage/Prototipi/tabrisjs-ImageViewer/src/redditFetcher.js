/*globals Promise: true, fetch: false, tabris: true*/
'use strict';
Promise = require('promise');
require('whatwg-fetch');

function RedditFetcher() {
    console.warn('Building a RedditFetcher');

}

RedditFetcher.prototype.createUrl = function (from, params) {
  //petpictures
  //EarthPorn
  var url = 'http://www.reddit.com/r/'+from+'.json?' + Object.keys(params).map(function(key) {
    return key + '=' + params[key];
  }).join('&');
  console.log(url);
  return url;
};

RedditFetcher.prototype.getData = function (from,params) {
  var url = this.createUrl(from,params);
  return fetch(url)
    .then(function(response) {
      return response.json();
    }, function() {
      console.error('Errore nel caricamento dei dati');
    });
};

module.exports = RedditFetcher;
