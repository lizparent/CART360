var serial;                             // variable to hold an instance of the serialport library
var portName = '/dev/cu.usbmodem1441';  // fill in your serial port name here
var myEllipses = [];
var MOTORS = 3;
var currentSelected;

function setup() {
  createCanvas(windowWidth, windowHeight);
  serial = new p5.SerialPort();       // make a new instance of the serialport library
 serial.on('list', printList);  // set a callback function for the serialport list event
 serial.on('connected', serverConnected); // callback for connecting to the server
 serial.on('open', portOpen);        // callback for the port opening
 serial.on('data', serialEvent);     // callback for when new data arrives
 serial.on('error', serialError);    // callback for errors
 serial.on('close', portClose);      // callback for the port closing

 serial.list();                      // list the serial ports
 serial.open(portName);              // open a serial port

 for(var i = 0; i < MOTORS; i++) {
   myEllipses.push(new Circle(char(i + 65), (windowHeight/MOTORS)+(i*1.15*(windowHeight/MOTORS)), windowHeight/MOTORS, windowHeight/MOTORS));
 }
}


function draw()
{
  background(0);
  for(var i = 0; i < MOTORS; i++) {
    myEllipses[i].display();
  }

}

/* CALL BACK FUNCTIONS */

function printList(portList) {
  // portList is an array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // Display the list the console:
    println(i + " " + portList[i]);
  }
}

function serverConnected() {
  println('connected to server.');
}

function portOpen() {
  println('the serial port opened.')
}

function serialEvent() {


}

function serialError(err) {
  println('Something went wrong with the serial port. ' + err);
}

function portClose() {
  println('The serial port closed.');
}

function mouseReleased() {
myEllipses[currentSelected].circleSize = windowHeight/MOTORS;


}

function mouseDragged() {
 // map the mouseY to a range from 0 to 255:

 for(var i =0; i < MOTORS;i++)
 {
   var dist_Coll  = dist(mouseX, mouseY, myEllipses[i].x, myEllipses[i].y);
   if(abs(dist_Coll)< myEllipses[i].circleSize/2)
   {
     console.log(myEllipses[i].index);
     if(myEllipses[i].circleSize < (windowHeight/MOTORS) || myEllipses[i].circleSize > (windowHeight/MOTORS)+130) {
       myEllipses[i].speed*=-1;
     }
     myEllipses[i].circleSize += myEllipses[i].speed;

     console.log("P5 DEBUG OUTPUT: ");
     console.log("MOTOR ID: " + myEllipses[i].index);
     console.log("ROTATION DEGREE: " + floor(map(myEllipses[i].circleSize,(windowHeight/MOTORS),(windowHeight/MOTORS)+130,0,180)));
     serial.write(myEllipses[i].index);
     serial.write(floor(map(myEllipses[i].circleSize,(windowHeight/MOTORS),(windowHeight/MOTORS)+130,0,180)));
     currentSelected=i;
      //myEllipses[i].circleSize = windowHeight/MOTORS;
   }
 }

 //outByte = int(map(mouseY, 0, height, 0, 255));
 // send it out the serial port:
 //serial.write(outByte);
}

function Circle(i, x, y, s)
{
  this.speed = 1;
  this.index = i;
  this.x = x;
  this.y = y;
  this.circleSize = s;
  this.colorFill = color(random(255),random(255),random(255));
  this.display = function() {
    fill(this.colorFill);
    ellipse(this.x,this.y, this.circleSize, this.circleSize);
  }
}
