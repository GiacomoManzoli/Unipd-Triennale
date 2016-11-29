'use strict';

var BASE_URL = 'http://www.reddit.com/r/';

var lastFilter = '';
var after = '';

class RedditFetcher {

  fetchData(filter) {
    lastFilter = filter;
    var url = BASE_URL+filter+'.json';
    return fetch(url)
      .then((response) => response.json())
      .then((responseData) => {
        after = responseData.data.after;
        return responseData;
      });
  }

  fetchMoreData(filter) {
    if (filter === lastFilter){
      var url = BASE_URL+filter+'.json?after='+after;
      return fetch(url)
        .then((response) => response.json())
        .then((responseData) => {
          after = responseData.data.after;
          return responseData;
        });
    }else {
      return this.fetchData(filter);
    }
  }
}

module.exports = RedditFetcher;
