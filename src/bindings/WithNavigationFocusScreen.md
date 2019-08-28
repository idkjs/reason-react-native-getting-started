# `NavigationEvent with focus` Demo React Native Module

<https://reactnavigation.org/>

Converted to reasonml from <https://reactnavigation.org/docs/en/with-navigation-focus.html#example>

```js
import React from 'react';
import { Text } from 'react-native';
import { withNavigationFocus } from 'react-navigation';

class FocusStateLabel extends React.Component {
  render() {
    return <Text>{this.props.isFocused ? 'Focused' : 'Not focused'}</Text>;
  }
}
```


