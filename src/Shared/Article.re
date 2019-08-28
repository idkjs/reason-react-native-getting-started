open ReactNative;
// type author = {name: string};
// type props = {
//   date: string,
//   author,
// };
let styles =
  Style.(
    StyleSheet.create({
      "container": style(~backgroundColor="white", ()),
      "content": style(~paddingVertical=16.->dp, ()),
      "author":
        style(
          ~flexDirection=`row,
          ~marginVertical=8.->dp,
          ~marginHorizontal=16.->dp,
          (),
        ),
      "meta": style(~marginHorizontal=8.->dp, ~justifyContent=`center, ()),
      "name":
        style(
          ~color="#000",
          ~fontWeight=`bold,
          ~fontSize=16.,
          ~lineHeight=24.,
          (),
        ),
      "timestamp": style(~color="#999", ~fontSize=14., ~lineHeight=21., ()),
      "avatar": style(~height=48.->dp, ~width=48.->dp, ~borderRadius=24., ()),
      "title":
        style(
          ~color="#000",
          ~fontWeight=`bold,
          ~fontSize=36.,
          ~marginVertical=8.->dp,
          ~marginHorizontal=16.->dp,
          (),
        ),
      "paragraph":
        style(
          ~color="#000",
          ~fontSize=16.,
          ~lineHeight=24.,
          ~marginVertical=8.->dp,
          ~marginHorizontal=16.->dp,
          (),
        ),
      "image":
        style(
          ~width=100.->pct,
          ~height=200.->dp,
          ~resizeMode=`cover,
          ~marginVertical=8.->dp,
          (),
        ),
    })
  );
open Types;
[@react.component]
let make = () => {
  let defaultProps = {
    date: "1st Jan 2025",
    author: {
      name: "Knowledge Bot",
    },
  };
  <ScrollView style=styles##container contentContainerStyle=styles##content>
    <View style=styles##author>
      <Image
        style=styles##avatar
        source={Image.Source.fromRequired(
          Packager.require("../assets/avatar-1.png"),
        )}
      />
      <View style=styles##meta>
        <Text style=styles##name>
          defaultProps.author.name->React.string
        </Text>
        <Text style=styles##timestamp> defaultProps.date->React.string </Text>
      </View>
    </View>
    <Text style=styles##title> "Lorem Ipsum"->React.string </Text>
    <Text style=styles##paragraph>
      "Contrary to popular belief, Lorem Ipsum is not simply random text. It
          has roots in a piece of classical Latin literature from 45 BC, making
          it over 2000 years old."
      ->React.string
    </Text>
    <Image
      style=styles##image
      source={Image.Source.fromRequired(
        Packager.require("../assets/book.jpg"),
      )}
    />
    <Text style=styles##paragraph>
      "Richard McClintock, a Latin professor at Hampden-Sydney College in
          Virginia, looked up one of the more obscure Latin words, consectetur,
          from a Lorem Ipsum passage, and going through the cites of the word in
          classical literature, discovered the undoubtable source."
      ->React.string
    </Text>
    <Text style=styles##paragraph>
      "Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of &quot;de
          Finibus Bonorum et Malorum&quot; (The Extremes of Good and Evil) by
          Cicero, written in 45 BC. This book is a treatise on the theory of
          ethics, very popular during the Renaissance. The first line of Lorem
          Ipsum, &quot;Lorem ipsum dolor sit amet..&quot;, comes from a line in
          section 1.10.32."
      ->React.string
    </Text>
  </ScrollView>;
};