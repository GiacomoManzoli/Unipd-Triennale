'use strict';

var React = require('react-native');
var {
  StyleSheet,
  Component,
  View,
  Image,
  Text,
  TouchableHighlight
} = React;

var styles;

class Asset extends Component {
  _onPress() {
    var asset = this.props.asset;
    var ref = this.props.asset.data.name;
    var bounds;
    this.refs[ref].measure((ox, oy, width, height, px, py) => {
        bounds =  {x: px, y: py-44, width: width, height: height};
        this.props.onShowDetail(asset, bounds);
    });
  }

  render() {
    return (
      <View style={styles.asset}>
        <Image
          source={{uri:this.props.asset.data.thumbnail}}
          style={styles.thumbnail}/>
        <View style={styles.separator}/>
        <View style={styles.descriptionRow}>
          <Text
            style={styles.descriptionTitle}>
            Title
          </Text>
          <Text
            numberOfLines={2}
            style={styles.descriptionVaule}>
            {this.props.asset.data.title}
          </Text>
        </View>
        <View style={styles.descriptionRow}>
          <Text
            style={styles.descriptionTitle}>
            Author
          </Text>
          <Text
            style={styles.descriptionVaule}>
            {this.props.asset.data.author}
          </Text>
        </View>
        <View style={styles.descriptionRow}>
          <Text
            style={styles.descriptionTitle}>
            Comments
          </Text>
          <Text
            style={styles.descriptionVaule}>
            {this.props.asset.data.num_comments}
          </Text>
        </View>
        <View>
          <TouchableHighlight onPress={this._onPress.bind(this)} ref={this.props.asset.data.name}>
            <Text>Info</Text>
          </TouchableHighlight>
        </View>
      </View>
    );
  }
}

styles = StyleSheet.create({
  asset:{
    height:200,
    width:220,
    margin:10,
    backgroundColor:'#fafafa',
    borderWidth: 1,
    borderColor: '#cccccc'
  },
  separator: {
    height:1,
    backgroundColor: '#cccccc',
  },
  thumbnail: {
    margin:5,
    width:210,
    height:100
  },
  descriptionRow: {
    justifyContent:'space-between',
    flexDirection:'row',
    marginLeft:5,
    marginRight:5
  },
  descriptionTitle: {
    textAlign:'left'
  },
  descriptionVaule: {
    textAlign:'right',
    fontWeight: 'bold',
    flex:1
  },
});

module.exports = Asset;
