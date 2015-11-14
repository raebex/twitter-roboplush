var app = require("express")();
var http = require("http").Server(app);
var io = require("socket.io")(http);
var robo_tweet = "";
var count = 0;

//
// Twitter setup
//
var Twitter = require("twitter");
var client = new Twitter({
  consumer_key: 'Fdztb34YCxCTO2uhoK42Vp7f1',
  consumer_secret: 'XVGgawkSrkAmdbwWcszui7mzF27EndQKRFFVs2amo75drMtmG6',
  access_token_key: '3012883804-mVFt5fNAlWpmSRRZm8vL5mE3BpLpXUdwxHzN6mH',
  access_token_secret: '7bxLmTATZFxhjMX4UfwVScz9fAaJxOqa5tMpcQqgbJ5JC'
});

//
// Arduino setup
//

// var SerialPort = require("serialport").SerialPort;
// var serialport = new SerialPort("/dev/cu.usbmodem1421", {
//   baudrate: 9600
// });

//
// Listen for tweets
//
client.stream('statuses/filter', {track: '@roboplush'}, function(stream) {
  stream.on('data', function(tweet) {
  	io.emit('chat message', tweet);

    //send char to arduino
    if (tweet.text.indexOf(":)") >= 0) {
      serialport.write('1');
    } else if (tweet.text.indexOf(":(") >= 0) {
      serialport.write('2');
    } else {
      serialport.write('3');
    }
  });
 
  stream.on('error', function(error) {
    throw error;
  });
});

//
// Tweet 
//
io.on('connection', function (socket) {
  socket.on('tweet-content', function (count) {
    tweetOut(count);
  });

  socket.on('tweet-to-user', function (username) {
    count++;
    tweetReply(count, username);
  });
});

//
// Path to index.html
//
app.get('/', function(req, res){
  res.sendFile(__dirname + '/www/index.html');
});

//
// Start Localhost
//
http.listen(3000, function(){
  console.log('listening on *:3000');
});

//
// Functions 
//

var tweetReply = function(count, username){
  robo_tweet = "@" + username + " " + pickResponse() + " (Tweet #" + count + ")";
  client.post('statuses/update', {status: robo_tweet}, function(error, tweet, response){
    // if (!error) {
    //   console.log(tweet);
    // }
  });
};

var tweetOut = function(count, username){
  robo_tweet = pickResponse() + " Tweet #" + count;
  client.post('statuses/update', {status: robo_tweet}, function(error, tweet, response){
  });
};


var pickResponse = function(){
  var random = responses[Math.floor(Math.random()*responses.length)];
  return random;
}

var responses = [
  "Hello :D", 
  "Hi there! :D", 
  "You make me sad :( ", 
  "You make me angry >:O", 
  "Hows it going? :D", 
  "'Robot' comes from the Czech word 'robota', meaning work, and first appeared in the 1921 play 'Rossum’s Universal Robots.'",
  "The first known case of robot homicide occurred in 1981, when a robotic arm crushed a Japanese Kawasaki factory worker.",
  "More than a million industrial robots are now in use, nearly half of them in Japan.",
  "Archytas of Tarentum built a mechanical bird driven by a jet of steam or compressed air in the fifth century B.C.",
  "Engineer Mark Rosheim has created a mini version of Leonardo Da Vinci's armored humanoid machine for NASA to colonize Mars.",
  "The real Mars robots, Spirit and Opportunity, have logged 10.5 miles trudging across the Red Planet formore than three years.",
  "Elektro, the world’s first humanoid robot, debuted in1939. The seven-foot-tall walking machine spoke more than 700 words.",
  "Hans Moravec, founder of Carnegie Mellon’s Robotics Institute, predicts that robots will emerge as their own species by2040.",
  "The first working robot was introduced in 1961. It worked on a production line making cars for Ford.",
  "The smallest robot is a nanobot, which measures only 10 nanometres in size – less than one thousandth of a millimetre.",
  "The first mention of a robot comes from Leonardo DaVinci in 1495. He wrote about mechanical knights who would help in battle.",
  "NASA employs a large range of robotic equipment. ISS’s Canadarm2, are used to lift, manoeuvre and recover large objects in space."
];
