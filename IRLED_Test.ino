int inPB = 7; //input for pushbutton
int outLED = 13; //input for LED
int offLED = 8; //PB 2 input
int val_1 = 0; //variable for capturing LED state  
int val_2 = 0; //variable for capturing LED state

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inPB, INPUT);
  pinMode(outLED, OUTPUT);
  pinMode(offLED, INPUT);
}

void Blinky() {
  //Function to blink the LED at a 2 second pulse
  while (val_1 == 0 && val_2 == 1){
    digitalWrite(outLED, LOW); //Turn off LED
    delay(2000); //off for 2 seconds
    digitalWrite(outLED, HIGH); //Turn On LED
    delay(2000); //on for 2 seconds
    Serial.println("in blink loop"); //print values
    delay(100);
    val_1 = digitalRead(inPB);  // read PB1 input value
    val_2 = digitalRead(offLED); //read PB2 value
    if (val_1 == 1 && val_2 == 0){
      stayup(); //enter stayup loop
      delay(100);
      Serial.println("entering stayup");
    }
    while (val_1 == 1 && val_2 == 1){
      Serial.println("Reloop");
      digitalWrite(outLED, LOW); //Turn off LED
      delay(2000); //off for 2 seconds
      digitalWrite(outLED, HIGH); //Turn On LED
      delay(2000); //on for 2 seconds
      Serial.println("in blink loop"); //print values
      delay(100);
      val_1 = digitalRead(inPB);  // read PB1 input value
      val_2 = digitalRead(offLED); //read PB2 value
      if (val_1 == 1 && val_2 == 0){
      stayup(); //enter stayup loop
      delay(100);
      Serial.println("entering stayup");
    }
   }
  }
}

void stayup(){
  //Function to keep LED off
  digitalWrite(outLED, LOW);  // turn LED OFF
  delay(200);
  Serial.println("in off loop");
}

void loop() {
  //loop to provide 2 second pulse of LED
  val_1 = digitalRead(inPB);  // read PB1 input value
  val_2 = digitalRead(offLED); //read PB2 value
  Serial.println(val_1); //print PB1 value
  Serial.println(val_2);//print PB2 value
  
  if (val_1 == 0 && val_2 == 1) {         // check if the input is HIGH (button released)
    Blinky();  // Blink the LED
    //delay(500);
  } 
  if (val_1 == 1 && val_2 == 0){
    stayup(); //Keep LED low
    //delay(500);
  }
 }
