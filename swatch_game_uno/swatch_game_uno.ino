#define NUM_LEDS 3

int leds[] = {
  7, 8, 9};
int button = 2;

volatile int chosenLED = -1;
int currLED = 0;
int prevLED = 0;

void setup() {
  // set LED pins as outputs and
  // leave lights off
  for( int i=0; i<NUM_LEDS; i++) {
    pinMode( leds[i], OUTPUT );
    digitalWrite( leds[i], LOW ); 
  }

  // set button pin as input and
  // use internal pull-up resistor
  pinMode( button, INPUT );
  digitalWrite( button, HIGH );

  // attach interrupt to our function and
  // have it called when the signal falls
  // from high to low
  attachInterrupt( 0, buttonHit, FALLING );

  Serial.begin( 9600 );
}

void loop() {
  if( chosenLED == -1 ){
    for( currLED=0; currLED<NUM_LEDS-1; currLED++) {
      digitalWrite( leds[currLED], HIGH );
      digitalWrite( leds[prevLED], LOW );
      delay(300); 
      prevLED = currLED;
    }
    for( currLED=NUM_LEDS-1; currLED>=0; currLED--) {
      digitalWrite( leds[currLED], HIGH );
      digitalWrite( leds[prevLED], LOW );
      delay(300); 
      prevLED = currLED;
    }
  }
  else {
   for( int i=0; i<NUM_LEDS; i++ ) {
    digitalWrite( leds[i], LOW );
   } 
   digitalWrite( leds[chosenLED], HIGH );
  }
}

void buttonHit () {
  chosenLED = currLED; 
}







