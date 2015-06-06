/*
 

 In this sketch folder is a basic webpage and a copy of zepto.js, a
 minimized version of jQuery.  When you upload your sketch, these files
 will be placed in the /arduino/www/webled folder on your SD card.

 You can then go to http://your_yun_name.local/sd/nomdossier
 to see the output of this sketch.


 */

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;
String readString; 

void setup() {
  Serial.begin(9600);

  // Bridge startup
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
//  pinMode(9, OUTPUT);
//  pinMode(8, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
//  digitalWrite(9, LOW);
//  digitalWrite(8, LOW);
  
  Bridge.begin();
  //digitalWrite(13, HIGH);

 

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();

 
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // read the command
    String command = client.readString();
    command.trim();        //kill whitespace
    Serial.println(command);
    
   

    if (command == "ledon") {
       digitalWrite(13, HIGH);
    }
    else if (command == "ledoff") {
       digitalWrite(13, LOW);
    }
     if (command == "led2on") {
       digitalWrite(12, HIGH);
    }
    else if (command == "led2off") {
       digitalWrite(12, LOW);
    }
     if (command == "led3on") {
       digitalWrite(11, HIGH);
    }
    else if (command == "led3off") {
       digitalWrite(11, LOW);
    }
     if (command == "led4on") {
       digitalWrite(10, HIGH);
    }
    else if (command == "led4off") {
       digitalWrite(10, LOW);
    }
     if (command == "led5on") {
       digitalWrite(13, HIGH);
       digitalWrite(12, HIGH);
       digitalWrite(11, HIGH);
       digitalWrite(10, HIGH);
//       digitalWrite(9, HIGH);
//       digitalWrite(8, HIGH);
    }
    else if (command == "led5off") {
       digitalWrite(13, LOW);
       digitalWrite(12, LOW);
       digitalWrite(11, LOW);
       digitalWrite(10, LOW);
//       digitalWrite(9, LOW);
//       digitalWrite(8, LOW);
    }
    
    
    
//       if (command == "led6on") {
//       digitalWrite(9, HIGH);
//    }
//    else if (command == "led6off") {
//       digitalWrite(9, LOW);
//    }
//    
//       if (command == "led7on") {
//       digitalWrite(8, HIGH);
//    }
//    else if (command == "led7off") {
//       digitalWrite(8, LOW);
//    }
if (command == "temperature") {
      int val = analogRead(A1);
  //getting the voltage reading from the temperature sensor
 int reading = analogRead(A1);  
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
   //to degrees ((voltage - 500mV) times 100)
 client.print(temperatureC); client.println(" degrees C");client.println();
 

 
      
      
    }

    // Close connection and free resources.
    client.stop();
   
  
  }
  
 

  delay(50); // Poll every 50ms
}


