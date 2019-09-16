---
id: going-back-demo
title: Going Back
sidebar_label: Going Back
---

converted from: <https://reactnavigation.org/docs/en/navigating.html#going-back>

Going back to previous screen in `js`:

```js
<Button
  title="Go back"
  onPress={() => this.props.navigation.goBack()}
/>
```

Going back to previous screen in `reason`:

```reason
<Button
  title="Go back"
  onPress={_ => navigation->Navigation.goBack}
/>
```
