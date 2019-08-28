open ReactNavigation;

open ReactNative;
module Button = Paper.Button;
let styles =
  Style.(
    StyleSheet.create({
      "buttons": style(~flexDirection=`row, ~padding=8.->dp, ()),
      "button": style(~margin=8.->dp, ()),
    })
  );

module ArticleScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    let author = navigation->Navigation.getParam("author");
    Js.log2("AUTHOR_PARAMS", author);
    <>
      <View style=styles##buttons>
        <Button
          mode=`contained
          onPress={_ => navigation->Navigation.navigate("Albums")}
          style=styles##button>
          "Push album"->React.string
        </Button>
        <Button
          mode=`outlined
          onPress={_ => navigation->Navigation.goBack}
          style=styles##button>
          "Go back"->React.string
        </Button>
      </View>
    </>;
    <Article />
  };
};
module AlbumsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <React.Fragment>
      <View style=styles##buttons>
        <Button
          mode=`contained
          onPress={_event =>
            navigation->Navigation.navigateWithParams(
              "Article",
              {"author": "Babel fish"},
            )
          }
          style=styles##button>
          "Push article"->React.string
        </Button>
        <Button
          mode=`outlined
          onPress={_event => navigation->Navigation.goBack}
          style=styles##button>
          "Go back"->React.string
        </Button>
      </View>
      <Albums />
    </React.Fragment>;
  };
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let routes = {
    "Albums": {
      screen: AlbumsScreen.make,
    },
    "Article": {
      screen: ArticleScreen.make,
    },
  };
    let configOptions =
      StackUtils.config(
        ~initialRouteName="Albums",
        // ~defaultNavigationOptions,
        (),
      );
    let navigator = StackNavigator.(makeWithConfig(routes, configOptions));
  });

[@react.component]
let make = () => <AppContainer />;