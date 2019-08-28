open ReactNative;
let styles =
  Style.(
    StyleSheet.create({
      "container": style(~flex=1., ~backgroundColor="#eceff1", ()),

      "inverted": style(~transform=[|scaleY(~scaleY=-1.)|], ()),
      "content": style(~padding=16.->dp, ()),

      "even": style(~flexDirection=`row, ()),

      "odd": style(~flexDirection=`rowReverse, ()),

      "avatar":
        style(
          ~marginVertical=8.->dp,
          ~marginHorizontal=6.->dp,
          ~height=40.->dp,
          ~width=40.->dp,
          ~borderRadius=20.,
          ~borderColor="rgba(0, 0, 0, .16)",
          ~borderWidth=StyleSheet.hairlineWidth,
          (),
        ),

      "bubble":
        style(
          ~marginVertical=8.->dp,
          ~marginHorizontal=6.->dp,
          ~paddingVertical=12.->dp,
          ~paddingHorizontal=16.->dp,
          ~borderRadius=20.,
          (),
        ),

      "sent": style(~backgroundColor="#cfd8dc", ()),

      "received": style(~backgroundColor="#2196F3", ()),

      "sentText": style(~color="black", ()),

      "receivedText": style(~color="white", ()),

      "input":
        style(
          ~height=48.->dp,
          ~paddingVertical=12.->dp,
          ~paddingHorizontal=24.->dp,
          ~backgroundColor="white",
          (),
        ),
    })
  );
let messages = [|
  "okay",
  "sudo make me a sandwich",
  "what? make it yourself",
  "make me a sandwich",
|];

[@react.component]
let make = () => {
  let odd = i => i mod 2 == 1;
  <View style=styles##container>
    <ScrollView style=styles##inverted contentContainerStyle=styles##content>
      {messages->Belt.Array.mapWithIndex((i, text) =>
         <View
           key={string_of_int(i)}
           style=Style.(
             list([styles##inverted, odd(i) ? styles##odd : styles##even])
           )>
           <Image
             style=styles##avatar
             source={
               odd(i)
                 ? Image.Source.fromRequired(
                     Packager.require("../../assets/avatar-2.png"),
                   )
                 : Image.Source.fromRequired(
                     Packager.require("../../assets/avatar-1.png"),
                   )
             }
           />
           <View
             style=Style.(
               list([
                 styles##bubble,
                 odd(i) ? styles##received : styles##sent,
               ])
             )>
             <Text
               style=Style.(
                 list([odd(i) ? styles##receivedText : styles##sentText])
               )>
               text->React.string
             </Text>
           </View>
         </View>
       )
       |> React.array}
    </ScrollView>
    <TextInput
      style=styles##input
      placeholder="Write a message"
      underlineColorAndroid="transparent"
    />
  </View>;
};