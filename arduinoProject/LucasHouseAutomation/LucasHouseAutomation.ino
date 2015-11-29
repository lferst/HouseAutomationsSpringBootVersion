//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY


#include <Ethernet2.h>
#include <SPI.h>
#include <LiquidCrystal.h>

boolean reading = false;
boolean led = false;
int IRledPin =  7;
int pinSensor = 0;
int readValue = 0;
float temperature = 0;

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(9, 8, 6, 5, 3, 2);
//Maybe use digital pins 3,5,6,7,8,9 for the lcd instead?

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x06, 0x11 };

 EthernetServer server = EthernetServer(9090); //port 80
////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);

  pinMode(IRledPin, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  //initial Project Message prints here.
  lcd.print("Lucas Automation");
  delay(1000);
  lcd.clear();
  lcd.print("Obtaining IP...");
  
  Ethernet.begin(mac); //for manual setup
  Serial.println(Ethernet.localIP());
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("IP: ");
  lcd.print(Ethernet.localIP());

  server.begin();

}

void loop(){

  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  
  // listen for incoming clients, and process qequest.
  checkForClient();

}

void checkForClient(){

  EthernetClient client = server.available();

  if (client) {

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean sentHeader = false;

    while (client.connected()) {
      
      if (client.available()) {

        if(!sentHeader){
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          sentHeader = true;
        }

        char c = client.read();

        if(reading && c == ' ') reading = false;
        if(c == '?') reading = true; //found the ?, begin reading the info

        if(reading && c != '?'){
          

           switch (c) {
            case '2':
              lcd.clear(); 
              lcd.print("Turning ON NET");
              cableTvControl(client);
              lcd.setCursor(0, 1);
              lcd.print(" OK");
              break;
            case '3':
              lcd.clear(); 
              lcd.print("Turning ON TV");
              tvControlONOFF(client);
              lcd.setCursor(0, 1);
              lcd.print(" OK");
              break;
            case '4':
             lcd.clear(); 
             lcd.print("NET Channel UP");
             cableTVChannelUP(client);
             lcd.setCursor(0, 1);
             lcd.print(" OK");
              break;
            case '5':
              lcd.clear(); 
              lcd.print("NET Channel DOWN");
              cableTVChannelDOWN(client);  
              lcd.setCursor(0, 1);
              lcd.print(" OK");
              break;
            case  '6':
              lcd.clear(); 
              lcd.print("Turning ON Air ");
              airConditionedONOFF(client);
              lcd.setCursor(0, 1);
              lcd.print(" OK");
              break;
           case  '7':
              lcd.clear(); 
              lcd.print("Reading Temperature ");
              lcd.setCursor(0, 1);
              readValue = analogRead(pinSensor);
              temperature = (readValue * 0.00488);
              temperature = temperature * 100;
              lcd.print(temperature);

          }
          delay(1000);
        }

        if (c == '\n' && currentLineIsBlank)  break;

        if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        }

      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  } 

}

void triggerPin(int pin, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
  client.print("Turning on pin ");
  Serial.println("Turning on pin ");
  client.println(pin);

  client.print("<br>");

  digitalWrite(pin, HIGH);
  delay(25);
  digitalWrite(pin, LOW);
  delay(25);
}

// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}

//Turns ON-OFF cable TV (NET)
void cableTvControl(EthernetClient client) {
  
    client.println("Turning ON NET");
 
    pulseIR(8860);
    delayMicroseconds(4400);
    pulseIR(580);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(540);
    delayMicroseconds(560);
    pulseIR(540);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(560);
    delayMicroseconds(1620);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(580);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(540);
    delayMicroseconds(560);
    pulseIR(540);
    delayMicroseconds(1660);
    pulseIR(540);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1620);
    pulseIR(580);
    delayMicroseconds(38360);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);
    delayMicroseconds(29004);
    pulseIR(8860);
    delayMicroseconds(2200);
    pulseIR(580);
    delayMicroseconds(28984);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);
    delayMicroseconds(29004);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);
    delayMicroseconds(29004);
    pulseIR(8860);
    delayMicroseconds(2180);
    pulseIR(600);
    delayMicroseconds(28984);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);


}

//Turns ON-OFF TV (LG)
void tvControlONOFF(EthernetClient client) {

    client.println("Turning ON TV");
    pulseIR(8980);
    delayMicroseconds(4440);
    pulseIR(660);
    delayMicroseconds(480);
    pulseIR(620);
    delayMicroseconds(480);
    pulseIR(640);
    delayMicroseconds(1600);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(640);
    delayMicroseconds(480);
    pulseIR(640);
    delayMicroseconds(460);
    pulseIR(640);
    delayMicroseconds(480);
    pulseIR(620);
    delayMicroseconds(480);
    pulseIR(640);
    delayMicroseconds(1600);
    pulseIR(580);
    delayMicroseconds(1640);
    pulseIR(640);
    delayMicroseconds(460);
    pulseIR(640);
    delayMicroseconds(1600);
    pulseIR(640);
    delayMicroseconds(1600);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(640);
    delayMicroseconds(1600);
    pulseIR(640);
    delayMicroseconds(1560);
    pulseIR(620);
    delayMicroseconds(520);
    pulseIR(640);
    delayMicroseconds(460);
    pulseIR(640);
    delayMicroseconds(480);
    pulseIR(640);
    delayMicroseconds(1600);
    pulseIR(620);
    delayMicroseconds(480);
    pulseIR(640);
    delayMicroseconds(480);
    pulseIR(620);
    delayMicroseconds(480);
    pulseIR(640);
    delayMicroseconds(480);
    pulseIR(620);
    delayMicroseconds(1600);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(620);
    delayMicroseconds(1620);
    pulseIR(640);
    delayMicroseconds(480);
    pulseIR(640);
    delayMicroseconds(1600);
    pulseIR(620);
    delayMicroseconds(1580);
    pulseIR(600);
    delayMicroseconds(1660);
    pulseIR(620);
    delayMicroseconds(1600);
    pulseIR(580);
    delayMicroseconds(39940);
    pulseIR(9000);
    delayMicroseconds(2200);
    pulseIR(660);
    delayMicroseconds(30144);
    pulseIR(9000);
    delayMicroseconds(2200);
    pulseIR(660);
    delayMicroseconds(30164);
    pulseIR(8980);
    delayMicroseconds(2220);
    pulseIR(640);
    delayMicroseconds(30184);
    pulseIR(8980);
    delayMicroseconds(2200);
    pulseIR(680);
    delayMicroseconds(30144);
    pulseIR(9000);
    delayMicroseconds(2200);
    pulseIR(660);
    delayMicroseconds(30144);
    pulseIR(8980);
    delayMicroseconds(2200);
    pulseIR(660);
    delayMicroseconds(30164);
    pulseIR(8980);
    delayMicroseconds(2200);
    pulseIR(660);
    delayMicroseconds(30164);
    pulseIR(8980);
    delayMicroseconds(2220);
    pulseIR(660);
    delayMicroseconds(30144);
    pulseIR(9000);
    delayMicroseconds(2200);
    pulseIR(660);
    delayMicroseconds(30164);
    pulseIR(8980);
    delayMicroseconds(2200);
    pulseIR(680);
    delayMicroseconds(30144);
    pulseIR(8980);
    delayMicroseconds(2220);
    pulseIR(640);
    delayMicroseconds(30164);
    pulseIR(8980);
    delayMicroseconds(2220);
    pulseIR(660);
    delayMicroseconds(30164);
    pulseIR(8980);
    delayMicroseconds(2200);
    pulseIR(660);
    delayMicroseconds(30164);
    pulseIR(8980);
    delayMicroseconds(2220);
    pulseIR(640);

}

//Changes channel UP (NET)
void cableTVChannelUP(EthernetClient client) {

    client.println("NET Channel UP");  
    pulseIR(8880);
    delayMicroseconds(4400);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1620);
    pulseIR(580);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(540);
    delayMicroseconds(560);
    pulseIR(540);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(540);
    delayMicroseconds(560);
    pulseIR(540);
    delayMicroseconds(560);
    pulseIR(540);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(540);
    delayMicroseconds(540);
    pulseIR(560);
    delayMicroseconds(1660);
    pulseIR(540);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(38380);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);
    delayMicroseconds(28984);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);
    delayMicroseconds(29004);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);
    delayMicroseconds(29004);
    pulseIR(8860);
    delayMicroseconds(2200);
    pulseIR(560);
    delayMicroseconds(29004);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(580);
}

//Changes channel DOWN (NET)
void cableTVChannelDOWN(EthernetClient client) {

    pulseIR(8880);
    delayMicroseconds(4400);
    pulseIR(600);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(540);
    delayMicroseconds(540);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(500);
    pulseIR(600);
    delayMicroseconds(1620);
    pulseIR(540);
    delayMicroseconds(540);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(540);
    delayMicroseconds(540);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(540);
    delayMicroseconds(560);
    pulseIR(560);
    delayMicroseconds(1620);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(540);
    pulseIR(580);
    delayMicroseconds(520);
    pulseIR(580);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(1640);
    pulseIR(560);
    delayMicroseconds(1620);
    pulseIR(560);
    delayMicroseconds(38380);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(600);
    delayMicroseconds(28984);
    pulseIR(8860);
    delayMicroseconds(2200);
    pulseIR(600);
    delayMicroseconds(28964);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(600);
    delayMicroseconds(28984);
    pulseIR(8860);
    delayMicroseconds(2200);
    pulseIR(600);
    delayMicroseconds(28984);
    pulseIR(8860);
    delayMicroseconds(2200);
    pulseIR(580);
    delayMicroseconds(28984);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(600);
    delayMicroseconds(28984);
    pulseIR(8880);
    delayMicroseconds(2180);
    pulseIR(600);
    delayMicroseconds(28984);
    pulseIR(8860);
    delayMicroseconds(2180);
    pulseIR(600);
    delayMicroseconds(28984);
    pulseIR(8860);
    delayMicroseconds(2200);
    pulseIR(580);

}

//Turns Air Conditioned ON-OFF
void airConditionedONOFF(EthernetClient client) {

    pulseIR(8740);
    delayMicroseconds(4080);
    pulseIR(600);
    delayMicroseconds(1480);
    pulseIR(540);
    delayMicroseconds(480);
    pulseIR(560);
    delayMicroseconds(480);
    pulseIR(540);
    delayMicroseconds(460);
    pulseIR(560);
    delayMicroseconds(1500);
    pulseIR(540);
    delayMicroseconds(460);
    pulseIR(560);
    delayMicroseconds(460);
    pulseIR(560);
    delayMicroseconds(460);
    pulseIR(580);
    delayMicroseconds(440);
    pulseIR(580);
    delayMicroseconds(460);
    pulseIR(560);
    delayMicroseconds(460);
    pulseIR(560);
    delayMicroseconds(460);
    pulseIR(540);
    delayMicroseconds(480);
    pulseIR(540);
    delayMicroseconds(1500);
    pulseIR(540);
    delayMicroseconds(480);
    pulseIR(540);
    delayMicroseconds(480);
    pulseIR(540);
    delayMicroseconds(1480);
    pulseIR(580);
    delayMicroseconds(1500);
    pulseIR(560);
    delayMicroseconds(1460);
    pulseIR(580);
    delayMicroseconds(1500);
    pulseIR(540);
    delayMicroseconds(460);
    pulseIR(560);
    delayMicroseconds(1480);
    pulseIR(560);
    delayMicroseconds(460);
    pulseIR(540);
    delayMicroseconds(480);
    pulseIR(560);
    delayMicroseconds(440);
    pulseIR(580);
    delayMicroseconds(1500);
    pulseIR(480);
    delayMicroseconds(1540);
    pulseIR(520);
    delayMicroseconds(1520);
    pulseIR(580);

}


