'use strict';

var React = require('react-native');
var GridView = require('react-native-grid-view');
var Asset = require('./Asset');

var {
  StyleSheet,
  Component
} = React;

var styles;

class ImageGrid extends Component {
  render() {
    return (
      <GridView
        items={this.props.assets}
        itemsPerRow={3}
        renderItem={this.renderItem.bind(this)}
        onEndReached={this.props.onEndReached}
      />
    );
  }
  renderItem(item) {
    console.log('render asset');
    return (
      <Asset asset={item} onShowDetail={this.props.onShowDetail}/>
    );
  }
}

styles = StyleSheet.create({

});

module.exports = ImageGrid;
