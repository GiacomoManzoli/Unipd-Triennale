'use strict';

var React = require('react-native');
var {
  Text,
  StyleSheet,
  View,
  Component,
  ListView,
  TouchableHighlight
} = React;

var styles;

class FilterList extends Component {
  /* props:
    onFilterSelected
    filters
  */
  constructor(props) {
    super(props);
    this.state = {
      dataSource: new ListView.DataSource({
        rowHasChanged: (row1,row2) => row1 !== row2
      })
    };
  }

  componentDidMount() {
    this.setState({
      dataSource:this.state.dataSource.cloneWithRows(this.props.filters)
    });
  }

  rowPressed(row) {
    console.log('filter selected');
    console.log(row);
    this.props.onFilterSelected(row);
  }

  render() {
    return (
      <ListView
        dataSource={this.state.dataSource}
        renderRow={this.renderRow.bind(this)}
        style={styles.listView} />
    );
  }

  renderRow(row) {
    return (
      <TouchableHighlight onPress={
          () => this.rowPressed(row)
        } underlayColor="#dddddd">
        <View>
          <View style={styles.listRow}>
            <Text style={styles.title}>{row.filterName}</Text>
          </View>
          <View style={styles.separator}/>
        </View>
      </TouchableHighlight>
    );
  }
}

styles = StyleSheet.create({
  listView:{
    backgroundColor: '#e3e3e3'
  },
  listRow: {
    flex: 1,
    flexDirection: 'row',
    justifyContent: 'flex-start',
    backgroundColor: '#e3e3e3',
    padding: 10
  },
  title: {
    fontSize: 20
  },
  separator: {
    height:1,
    backgroundColor: '#dddddd',
  },
});

module.exports = FilterList;
