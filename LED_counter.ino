int buttPin = 2;
int redPin = 5;
int greenPin = 6; 
int bluePin = 7;
int yelPin = 8;
int whitePin = 9;

int state = 0; // Stores the state of how many led's are on

int time = 0; // time to start the auto count
float target = 100; //hold to count speed
unsigned long prevMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buttPin, INPUT_PULLUP); //
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(yelPin, OUTPUT);
  pinMode(whitePin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); //Set pin modes

  digitalWrite(redPin, LOW); //Set start condition
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(yelPin, LOW);
  digitalWrite(whitePin, LOW);
  digitalWrite(LED_BUILTIN, HIGH);

}

void setLeds(){ //logic to set the led's
    if(state == 0){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(yelPin, LOW);
    digitalWrite(whitePin, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if(state == 1){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(redPin, HIGH);
  }
  else if(state == 2){
    digitalWrite(greenPin, HIGH);
  }
    else if(state == 3){
    digitalWrite(bluePin, HIGH);
  }
    else if(state == 4){
    digitalWrite(yelPin, HIGH);
  }
    else if(state == 5){
    digitalWrite(whitePin, HIGH);
  }
}

void updateState(){
      state = state + 1;
      if(state > 5){ //roll over to 0
        state = 0;
      }
}
void loop() {

  while(digitalRead(buttPin) == 1){} //wait until button is pressed

  updateState();
  setLeds(); //Set led's when button is pressed

  while(digitalRead(buttPin) == 0){  //wait until button is released, if button is held then go through the led's faster/
    delay(1);
    time = time + 1;
    if(time >= 500 && millis() - prevMillis >= target){
      prevMillis = millis();
      updateState();
      setLeds();
      target = pow(.99,(time / 6000.) * 500.) * 500.; // every 6 seconds make the hold to count go faster along an exponential curve
      Serial.println(target);
    }
  }
  time = 0; // Reset the hold check
  prevMillis = millis();
  target = 100; //resets hold count speed
}
