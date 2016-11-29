'use strict';

var React = require('react-native');
var GalleryPage = require('../Pages/GalleryPage');
var Router = require('react-native-router'); //Router (NavigationBar) avanzata

var {
  Component,
  StyleSheet,
  Text,
  View,
  Navigator,
  NavigatorIOS
} = React;

var styles;

/*var firstRoute = {
  name:'Gallery',
  component: GalleryPage,
  leftCorner: LeftButtons
};*/

//Se questo disgraziato non è definito prima la route prende un "undefined" e non funziona più niente
class LeftCorner extends Component {
  render () {
    return (<Text style={styles.title}>Left</Text>);}
}

var firstRoute = {
  name:'Featued',
  component: GalleryPage
  //,leftCorner: LeftCorner //non serve più, è stato modificato il componente Router
};

class GalleryRouter extends Component {
  render() {

    return (
      <Router
        firstRoute={firstRoute}
        headerStyle={styles.header}
        titleStyle={styles.title}
        rightCorner={RightCorner}
        leftCorner={LeftCorner}
        style={styles.navbar}
        />
    );

/*
    return (
      <NavigatorIOS
        initialRoute={firstRoute}
        barTintColor="#263238"
        tintColor="#fafafa"
        titleTextColor="#fafafa"
        translucent="false"
        style={styles.navigator}
        />
    );
    */
  }
}

class BackButton extends Component {
    render() {return (<Text>Indietro</Text>);}
}

class RightCorner extends Component {
  render () {
    return (<Text style={styles.title}>Right</Text>);}
}


styles = StyleSheet.create({
  header: {
    backgroundColor: '#263238'
  },
  title:{
    color:'#fafafa'
  }
});

module.exports = GalleryRouter;
