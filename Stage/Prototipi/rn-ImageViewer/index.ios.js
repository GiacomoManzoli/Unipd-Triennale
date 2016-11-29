/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 */
'use strict';

var React = require('react-native');
var {
  AppRegistry,
  StyleSheet,
  View,
  TabBarIOS,
  NavigatorIOS,
  Component
} = React;

var GalleryRouter = require('./src/Routers/GalleryRouter');

class ImageViewer extends Component {
  constructor(props) {
    super(props);
    this.state = {
      selectedTab: 'gallery'
    };
  }

  render() {
    return (
      <TabBarIOS
        selectedTab={this.state.selectedTab}
        barTintColor="#263238"
        tintColor="#fafafa"
        traslucent="false">
        <TabBarIOS.Item
          title="Gallery"
          selected={this.state.selectedTab === 'gallery'}
          icon={{uri: 'featured'}}
          onPress={()=>{
            this.setState({
              selectedTab:'gallery'
            });
          }}>
          <GalleryRouter />
        </TabBarIOS.Item>
      </TabBarIOS>
    );
  }
}

var styles = StyleSheet.create({

});

AppRegistry.registerComponent('ImageViewer', () => ImageViewer);
