---
id: using-nav-params-in-title
title: Using Navigation Params In Title
sidebar_label: Using Nav Params In Title
---

convert to reasonml from <https://reactnavigation.org/docs/en/headers.html#using-params-in-the-title>

```js
class DetailsScreen extends React.Component {
  static navigationOptions = ({ navigation }) => {
    return {
      title: navigation.getParam('otherParam', 'A Nested Details Screen'),
    };
  };

  /* render function, etc */
}
```

Use `setDynamicNavigationOptions` and pass in the `params` object. The `title` is on `params##navigation`, here we are you `getParamsWithDefault` to get the value `otherParam` and if not there, use the default.

```reason
[@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Details Screen">
      /* rest of your component*/
    </Screen>;
  };

  make->NavigationOptions.setDynamicNavigationOptions(params => {
    let title = params##navigation->Navigation.getParamWithDefault("otherParam", "A Nested Details Screen");
    (NavigationOptions.t(~title, ()));
  });
```
