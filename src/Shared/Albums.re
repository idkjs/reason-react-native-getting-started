open ReactNative;

let dimensions = Dimensions.get(`window);
let styles =
  Style.(
    StyleSheet.create({
      "container":
        style(
          ~flex=1.,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~backgroundColor="#343C46",
          (),
        ),
      "content": style(~flexDirection=`row, ~flexWrap=`wrap, ()),
      "cover":
        style(~width=50.->pct, ~height=(dimensions##width /. 2.)->dp, ()),
      "instructions": style(~textAlign=`center, ~color="#ffffff", ()),
    })
  );
let covers = [|
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-1.jpg"),
  ),
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-2.jpg"),
  ),
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-3.jpg"),
  ),
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-4.jpg"),
  ),
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-5.jpg"),
  ),
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-6.jpg"),
  ),
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-7.jpg"),
  ),
  Image.Source.fromRequired(
    Packager.require("../assets/album-art-8.jpg"),
  ),
|];

[@react.component]
let make = () => {
  <ScrollView style=styles##content contentContainerStyle=styles##container>
    {covers->Belt.Array.mapWithIndex((i, source) =>
       <Image key={string_of_int(i)} source style=styles##cover />
     )
     |> React.array}
  </ScrollView>;
};