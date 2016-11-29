'use strict';
var React = require('react-native');
var Popover = require('react-native-popover');

var FilterList = require('../Components/FilterList');
var ImageGrid = require('../Components/ImageGrid');

var AssetsStore = require('../Stores/AssetsStore');
var AssetsActions = require('../Actions/AssetsActions');

var FiltersStore = require('../Stores/FiltersStore');
var FiltersActions = require('../Actions/FiltersActions');

var SCREEN_HEIGHT = require('Dimensions').get('window').height;
var SCREEN_WIDTH = require('Dimensions').get('window').width;

/* l'altezza è la larghezza sono calcolati sull'iPad in portait
dal momento che l'applicazione è in landscape l'altezza e la larghezza si invertono*/
var popoverBounds = {
  x:0,
  y:0,
  width: SCREEN_HEIGHT,
  height: SCREEN_WIDTH
};

var {
  Text,
  View,
  StyleSheet,
  Component,
} = React;

var styles;
var lastFilter = 'petpictures';

var me;

function getStateFromStores(){
  return {
    filters: FiltersStore.getAll(),
    assets: AssetsStore.getAll()
  };
}


class GalleryPage extends Component {
  constructor(props){
    super(props);
    //Serve questo trick per evitare che il this diventi qualche altro oggetto quando
    //passo funzioni da invocare come callback
    me = this;
    AssetsActions.loadAssets(lastFilter);
    FiltersActions.loadFilters();

    var state = getStateFromStores();
    state.popoverVisible = false;
    state.popoverBoundRect = {};
    this.state = state;
  }



  componentDidMount() {
    AssetsStore.addChangeListener(this._onStoreChange);
    FiltersStore.addChangeListener(this._onStoreChange);
  }

  componentWillUnmount() {
    AssetsStore.removeChangeListener(this._onStoreChange);
    FiltersStore.removeChangeListener(this._onStoreChange);
  }

  _onStoreChange() {
    me.setState(getStateFromStores());
    console.log('state changed');
  }

  _onShowDetail(asset, fromBound) {
    //Mostra il popover con i dati presenti in asset.
    //fromBound contiene le informazioni riguardanti il controllo che ha originato l'evento
    console.log('Showing details..');
    console.log(fromBound);
    this.setState({
      popoverVisible: true,
      popoverBoundRect: fromBound
    });
  }

  _onHideDetail() {
    this.setState({
      popoverVisible:false
    });
  }

  filterSelected(row) {
    console.log(row);
    if (row.filter !== lastFilter){
      lastFilter = row.filter;
      AssetsActions.loadAssets(row.filter);
    }
  }

  loadMoreData() {
    AssetsActions.loadMoreAssets(lastFilter);
  }

  render() {
    return (
      <View style={styles.container}>
        <View style={styles.master}>
          <FilterList
            filters={this.state.filters}
            onFilterSelected={this.filterSelected.bind(this)}/>
        </View>
        <View style={styles.details}>
          <ImageGrid
            assets={this.state.assets}
            onEndReached={this.loadMoreData}
            onShowDetail={this._onShowDetail.bind(this)}/>
        </View>
        <Popover
          isVisible={this.state.popoverVisible}
          fromRect={this.state.popoverBoundRect}
          onClose={this._onHideDetail.bind(this)}
          placement="bottom"
          displayArea={popoverBounds}>
            <View style={{width:600}}>
              <Text>Contenuto del popover</Text>
            </View>
        </Popover>
      </View>
    );

  }
}

styles = StyleSheet.create({
  container:{
    flex:1,
    flexDirection:'row'
  },
  master: {
    width:280
  },
  details: {
    flex:1,
    backgroundColor:'#e3e3e3'
  }
});


module.exports = GalleryPage;
