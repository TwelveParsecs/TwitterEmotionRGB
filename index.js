
//Twitter and Alchemy APIs
var watson = require('watson-developer-cloud');
var Twitter = require('twitter');

//Serialport communication
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

//Set serialport via command line
var portName = process.argv[2];
// print out the port you're listening on:
console.log("opening serial port: " + portName);

var myPort = new SerialPort(portName, {
	baudRate: 9600//,
});


var emotion = "";//holds emotion retrieved from Twitter

//holds images to iterate through for each emotion
var angerArray = [];
var disgustArray = [];
var fearArray = [];
var joyArray = [];
var sadnessArray = [];

var imageCommand = ""; //command that's going to be sent to arduino

//Required to load pngs
var fs = require('fs'),
    PNG = require('pngjs').PNG;

//load images
loadImage("icons/sad11.png", "anger");

//loadImage("disgust2.png", "disgust");

//Get emotion from Twitter feed
//getTwitter();


myPort.on("open", function () {
  console.log('open');
  myPort.on('data', function(data) {
    console.log('data received: ' + data);
  });
	//wait until Arduino has restarted before sending data
	setTimeout(function(){
		var count = 0;
		var timeElapsed = 0;
		var imageArray;

		//loop through frames
			setInterval(function(){

				//check that an emotion has been set
				//console.log("started looping");
				emotion = "anger"; //REMOVE LATER//
				//console.log(emotion);

				if (emotion != ""){
					//display frames from current emotion
					if (emotion == "anger")imageArray = angerArray;
					else if (emotion == "disgust")imageArray = disgustArray;
					else if (emotion == "fear")imageArray = fearArray;
					else if (emotion == "joy")imageArray = joyArray;
					else imageArray = sadnessArray;

					//if there are no more frames, restart
					if (count >= imageArray.length) count = 0;

					sendToSerial(imageArray[count]);
					count +=1;
					timeElapsed += 600;

					//if 2 minutes have passed, check Twitter again
					if (timeElapsed > 120000){
							//getTwitter();
							timeElapsed = 0;
					}
				}
			},200);
	},2000);
});


/*
	Image loading and parsing
*/

//must install pngjs


//load image
function loadImage(img,emotion){
	fs.createReadStream(img)
	    .pipe(new PNG({
	        filterType: 4
	    }))
	    .on('parsed', function() {
imageCommand = "";
	        for (var y = 0; y < this.height; y++) {
							// Add row number

							imageCommand += y+1;
	            for (var x = 0; x < this.width; x++) {
	                var idx = (this.width * y + x) << 2;
									var empty = true; // Whether any colours are actually present

	                // Fill array with color values
	                if (this.data[idx]==255){
										// Add to command
										imageCommand += "r";
										empty = false;
	                }
									if (this.data[idx+1]==255){
										// Add to command
										imageCommand += "g";
										empty = false;
	                }
									if (this.data[idx+2]==255){
										// Add to command
										imageCommand += "b";
										empty = false;
	                }

	                if (empty) {
										// Add to command
										imageCommand += "x";
	                }

									// Add delimiter
									imageCommand +="-";
	            }
							// Add line ending
							imageCommand +="*";
							switch(emotion){
								case "anger":
									angerArray.push(imageCommand);
									break;
								case "disgust":
									disgustArray.push(imageCommand);
									break;
								case "fear":
									fearArray.push(imageCommand);
									break;
								case "joy":
									joyArray.push(imageCommand);
									break;
								case "sadness":
									sadnessArray.push(imageCommand);
									break;
							}

	        }
					//Arduino will read number sign as end of serial data.
					console.log(imageCommand);

					//add data to matching array

			});
}

function sendToSerial(data) {

		myPort.write(data, function(err, results) {
			//console.log('err ' + err);
		//	console.log('results ' + results);
			//console.log("sent");
		});

}


/* TWITTER
 * Gets user's 10 latest tweets and runs their
 * combined text through Watson language analysis.
 * Returns the dominant emotion from the text.
 */
 function getTwitter (){
	var alchemyKey = "a62741b9f19751f464297d53615422f0058635ba";


	//Twitter authentication info
	var client = new Twitter({
		consumer_key: 'neIl2vfIibKjeT72V3EzpZd3k',
		consumer_secret: '20w5g4jfFu5f7uNbipNTv01aiF7GUsWOtLGCveDaLmpWWvDoqJ',
		access_token_key: '3329047650-unQ8BdHKWOmek5rX2MnHOpsKpwOO6UyniXOcvhx',
		access_token_secret: 'bRfRHEpd8NVzPmuigymE1e23D6bm9AtTOgikHkjlaWVcY'
	});

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
				console.log(emotion);

	});


	}


}
