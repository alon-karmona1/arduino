
  // https://www.tinkercad.com/things/46D67SujmRQ  // 


#include <IRremote.h>
//Define Pins
long randNumber;
float temperature;
int tempPin = 0;
int greenLed = 5;
int redLed = 6;
const int echoPin = 7;
const int trigPin = 8;
int RECV_PIN = 11;
int TonePin = 12;
int numOfBoxesRipe1 = 0;
int numOfBoxesRipe2 = 0;
int numOfBoxesRipe3 = 0;
int tempBoxes = 0;
int sentBoxesEndDay = 0;
int numOfNewBoxes = 0;
int thiefArrivedAlready = 0;
int dayIsOn = 0;
int playIsOn = 0;
int over23Degrees = 0;
int goToGarbage = 0;
long duration, cm;
int distance;

//IR Library stuff
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup(){ //setting the input and output values
  randomSeed(analogRead(0));
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); 
  Serial.println("Enabled IRin");
}


void loop() {    //main
 checkStartDay();  // checks in usef pressed "on"
  while(dayIsOn == 1){ // day started
    dayProccess(); //checking temperature and if user pressed "play"
    while (playIsOn == 1){ //user pressed play to insert boxes
      newBoxes(); //insert boxes process
    } //while
  	CheckEndDay(); // checks in usef pressed "on/off" in if soo going to endDay();
  } // while
  if (dayIsOn == 0){ //night mode
     thief();  //checking if thief getting closer to the factory.
  } //if
} //void
      
void checkStartDay(){
  delay(50);
  Serial.println("cheking start day");
  if (irrecv.decode(&results)) {//irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
     unsigned int value = results.value;//Get the value of results as an unsigned int, so we can use switch case
     if (value == 255){
      dayIsOn=1;
      Serial.println("the day started!");
      over23Degrees=0; //initialization the transition sensor.
     } //if
  irrecv.resume();
  }
}

void dayProccess(){
    delay(50);
  	Serial.println("starting day Proccess");
    checkTemperature();
    printActualBoxes();
    if (irrecv.decode(&results)) {
    	unsigned int value = results.value;
      if( value == 41055){ //play button
        Serial.println("user pressed the play/pause button");
        playIsOn = 1;
      }
    irrecv.resume(); 
    }
}

void newBoxes(){
  delay(50);
  numOfNewBoxes=0;
  Serial.println("please insert number of new boxes between 1 to 9 :) ");
  delay(2000);
  if (irrecv.decode(&results)) {
     unsigned int value = results.value; 
     switch (value) {
     	case 2295: //1
      		numOfNewBoxes=1;
       		Serial.println("inserting 1 new boxes");
       		playIsOn =0;
      	   break; 
       
    	case 34935: //2
     		 numOfNewBoxes=2;
      		 Serial.println("inserting 2 new boxes");
       		 playIsOn =0;
      		break;
      
      	case 18615: //3
     		 numOfNewBoxes=3;
       		 Serial.println("inserting 3 new boxes");
       		 playIsOn =0;
      		break;
      
      	case 10455: //4
        	numOfNewBoxes=4;
       		Serial.println("inserting 4 new boxes");
       		playIsOn =0;
       	   break;
      
      	case 43095: //5
      		numOfNewBoxes=5;
       		Serial.println("inserting 5 new boxes");
       		playIsOn =0;
      	   break;
      
      	case 26775: //6
      		numOfNewBoxes=6;
       		Serial.println("inserting 6 new boxes");
       		playIsOn =0;
       	   break;
      
      	case 6375: //7
      		numOfNewBoxes=7;
       		Serial.println("inserting 7 new boxes");
       		playIsOn =0;
       	   break;
      
      	case 39015: //8
      		numOfNewBoxes=8;
       		Serial.println("inserting 8 new boxes");
       		playIsOn =0;
       	   break;
      
      	case 22695: //9
      		numOfNewBoxes=9;
       		Serial.println("inserting 9 new boxes");
       		playIsOn =0;
       	   break;
    } //end switch
  irrecv.resume();
  } // if
  for (int i=0; i<numOfNewBoxes; i++){ //if user didnt pressed the for won't be active
       randNumber = random(9);
       if (randNumber <3){ // 1/3 of the options (0,1,2)
 		 numOfBoxesRipe1++;
         Serial.println("adding one box of avocados ripe 1");
       } //if
       else if (randNumber <6){ // 1/3 of the options (3,4,5)
 		 numOfBoxesRipe2++;
         Serial.println("adding one box of avocados ripe 2");
       } //else if
       else { // 1/3 of the options (6,7,8)
 		 numOfBoxesRipe3++;
         Serial.println("adding one box of avocados ripe 3");
       } //else
  	   digitalWrite(greenLed, HIGH); //greenLed is blinking according to the number of isterting boxes.
       delay(300);
       digitalWrite(greenLed, LOW);
       delay(300); 
  }//for
} // new boxes

void CheckEndDay(){
 delay(300);
 Serial.println("checking end day");
 if (irrecv.decode(&results)){
    unsigned int value = results.value;
    if (value == 255){ //off button
      dayIsOn=0;
      Serial.println("EndDay");
      endDay(); // insert to endDay process
    }
     irrecv.resume();
  }
}

 
void endDay() { // end Day process
  sentBoxesEndDay = 0; //initializing the value from last night
  thiefArrivedAlready = 0; //initializing the value from last night
  Serial.println("end day, ripe up every avocado");
  delay(20);
  sentBoxesEndDay = numOfBoxesRipe3; // sending the ripe 3 to Shupersal :)
  numOfBoxesRipe3 = numOfBoxesRipe2;  //Rising ripe level
  numOfBoxesRipe2 = numOfBoxesRipe1;  //Rising ripe level
  numOfBoxesRipe1 = 0;                //Rising ripe level
  Serial.print("blinking ");
  Serial.print(sentBoxesEndDay); // number of  avocados sent to Super
  Serial.println(" times!");
  for(int i=0; i < sentBoxesEndDay; i++){ // blinking the number of  avocados sent to Super time
      digitalWrite(redLed, HIGH);
      delay(400);
      digitalWrite(redLed, LOW);
      delay(400);
  }
}


void thief() { //thief checks and process
  delay(50); 
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state for 5 micro seconds
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  pinMode(trigPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration)*1.356; //according to the Forum advice
  Serial.print("checking distance. Distance: ");// Prints the distance on the Serial Monitor
  Serial.println(cm);
  if (cm<100){
    if(thiefArrivedAlready == 0){ // if its the first thief in the night so enter
      Serial.println("Distance under 100 - first time in the night so he will stole");
      myTone(TonePin,1000,3000);
      delay(50);
      for(int i=0; i<3; i++){ // 3 times the thief will steal
       randNumber = random(9);
       if (randNumber <3){
 		 numOfBoxesRipe1--;
         Serial.println("the thief stole one box of avocados ripe 1 :(");
       } //if
       else if (randNumber <6){
 		 numOfBoxesRipe2--;
         Serial.println("the thief stole one box of avocados ripe 2 :(");
       } //else if
       else {
 		 numOfBoxesRipe3--;
         Serial.println("the thief stole one box of avocados ripe 3 :(");
       } //else
     delay(50); 
     } //for
    thiefArrivedAlready =1;  
    } //if
  } //if distance
  if(numOfBoxesRipe1 < 0){ // if the thief "steal" from 0 boxes it will stay 0
    numOfBoxesRipe1 = 0;
  }
  if(numOfBoxesRipe2 < 0){ // if the thief "steal" from 0 boxes it will stay 0
    numOfBoxesRipe2 =0;
  }
  if(numOfBoxesRipe3 < 0){ // if the thief "steal" from 0 boxes it will stay 0
    numOfBoxesRipe3 =0;
  }
} // thief



void myTone(byte pin, uint16_t frequency, uint16_t duration){ //function from the lesson
  delay(50);
  unsigned long startTime=millis();
  unsigned long halfPeriod= 1000000L/frequency/2;
  pinMode(pin,OUTPUT);
	while (millis()-startTime<duration){
   	 digitalWrite(pin,HIGH);
     delayMicroseconds(halfPeriod);
   	 digitalWrite(pin,LOW);
     delayMicroseconds(halfPeriod);
  }
  pinMode(pin,INPUT);
}



void checkTemperature() { //check Temperature Process
   delay(50);
   Serial.println("checking temperature");
   temperature = analogRead(tempPin);  	// read analog volt from sensor and save to variable temp
   temperature = temperature * 0.48828125;  // convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE = ");
   Serial.print(temperature); // display temperature value
   Serial.println("*C");
   if (temperature >= 23 ){ // cross the threshold
     if (over23Degrees == 0){ // just in the transition between less to more than 23*C
        Serial.println("temperature over 23*C ,avocados ripe 1 level up");
   		over23Degrees = 1; //won't insert to the "if" if the temperature still obove 23 even if its increasing
        goToGarbage = numOfBoxesRipe3; //rising ripe level - ripe 3 id now rotten.
     	numOfBoxesRipe3 = numOfBoxesRipe2; //rising ripe level
     	numOfBoxesRipe2 = numOfBoxesRipe1; //rising ripe level
   		numOfBoxesRipe1 = 0;           
       	Serial.print("go To garbage: ");
       	Serial.println(goToGarbage);
     }
   }
   else{ //TEMPERATURE under 23 degrees
     over23Degrees = 0;
   }
   delay(50);
} //checkTemperature()


void printActualBoxes() { //function for modular code.
  Serial.print("number of avocado boxes ripe 1 is: ");
  Serial.println(numOfBoxesRipe1);
  Serial.print("number of avocado boxes ripe 2 is: ");
  Serial.println(numOfBoxesRipe2);
  Serial.print("number of avocado boxes ripe 3 is: ");
  Serial.println(numOfBoxesRipe3);
}

  long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}