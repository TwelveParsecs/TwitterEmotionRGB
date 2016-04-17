  /*var AlchemyAPI = require('./alchemyapi');
  var alchemyapi = new AlchemyAPI();*/
  var alchemyKey = "a62741b9f19751f464297d53615422f0058635ba";

  var watson = require('watson-developer-cloud');
  var Twitter = require('twitter');

  //Twitter authentication info
  var client = new Twitter({
    consumer_key: 'neIl2vfIibKjeT72V3EzpZd3k',
    consumer_secret: '20w5g4jfFu5f7uNbipNTv01aiF7GUsWOtLGCveDaLmpWWvDoqJ',
    access_token_key: '3329047650-unQ8BdHKWOmek5rX2MnHOpsKpwOO6UyniXOcvhx',
    access_token_secret: 'bRfRHEpd8NVzPmuigymE1e23D6bm9AtTOgikHkjlaWVcY'
  });

  var emotion = "";
//Get first ten tweets from home timeline
 client.get('statuses/home_timeline', {count: '10'}, function(error, tweets, response){
   var fullText = "";
    if(error) throw error;
    for (i in tweets){
        var tweetText = tweets[i].text;
        var linkIndex = tweetText.search("http");
        fullText += tweetText.substring(0,linkIndex);
    }
    //send to Alchemy
    analyze(fullText);
    console.log(emotion);
  });

//analyze emotions in text
function analyze(fullText){
  var alchemy_language = watson.alchemy_language({
    api_key: 'a62741b9f19751f464297d53615422f0058635ba'
  });

  var params = {
    text: fullText
  };


  alchemy_language.emotion(params, function (error, response) {
    if (error){
      console.warn('error:', error);
      return "error";
    }
    else
      var emotionVal = [];
      emotionVal[0] = parseFloat(response.docEmotions.anger);
      emotionVal[1] = parseFloat(response.docEmotions.disgust);
      emotionVal[2] = parseFloat(response.docEmotions.fear);
      emotionVal[3] = parseFloat(response.docEmotions.joy);
      emotionVal[4] = parseFloat(response.docEmotions.sadness);

      for (i = 0; i < 5; i++){
          console.warn(emotionVal[i])
      }


        //check which one is largest
        var maxIndex = 0.0;
        var maxNum = 0.0;
        for (i = 0; i < 5; i++){
          if (emotionVal[i] > maxNum){
            maxNum = emotionVal[i];
            maxIndex = i;
            console.log(maxNum);
          }
        }

        switch(maxIndex) {
            case 0:
                emotion = "anger ";
                break;
            case 1:
                emotion = "disgust";
                break;
            case 2:
                emotion = "fear";
                break;
            case 3:
                emotion = "joy";
                break;
            case 4:
                emotion = "sadness";
                break;
        }

  });


}

setInterval(function(){
  if (emotion != "") console.log(emotion);

},600);
