#define NUM_LEDS 3

int leds[] = {
  7, 8, 9};
int button = 2;

int currLED = 0;
int prevLED = 0;
int winTime = 140;

volatile int chosenLED = -1;
volatile int delayTime = 240;
volatile int lastChosenTime = 0;
volatile int lastPress = 0;


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
  attachInterrupt( 0, buttonHit, CHANGE );

  Serial.begin( 9600 );
}

void loop() {
  // play game if we haven't reaching fastest level
  if ( delayTime > winTime ){
    switch( chosenLED ){
    case -1:
      // if the button hasn't been pressed to choose an LED
      // keep flashing the gam
      for( currLED=0; currLED<NUM_LEDS-1; currLED++) {
        digitalWrite( leds[currLED], HIGH );
        digitalWrite( leds[prevLED], LOW );
        delay( delayTime ); 
        prevLED = currLED;
      }
      for( currLED=NUM_LEDS-1; currLED>0; currLED--) {
        digitalWrite( leds[currLED], HIGH );
        digitalWrite( leds[prevLED], LOW );
        delay( delayTime ); 
        prevLED = currLED;
      }
      break;

    default:
      // light up the chosen LED
      for( int i=0; i<chosenLED; i++ ) {
        digitalWrite( leds[i], LOW );
      } 
      for( int i=chosenLED+1; i<NUM_LEDS; i++ ) {
        digitalWrite( leds[i], LOW );
      } 
      digitalWrite( leds[chosenLED], HIGH );

    }
  } 
  else {
    for( int i=0; i<NUM_LEDS; i++) {
      digitalWrite( leds[i], HIGH );
    }
    delay( 150 );
    for( int i=0; i<NUM_LEDS; i++) {
      digitalWrite( leds[i], LOW );
    }
    delay( 150 ); 
  }

  /*Serial.print("delayTime: ");
   Serial.print(delayTime);
   Serial.print(" chosenLED: " );
   Serial.println(chosenLED);
   */
}

void buttonHit () {
  // button debounce
  int currState = digitalRead( button );

  if ( millis() - lastPress > 100 && currState==LOW) {
    Serial.println("button pressed");
    // select LED
    if( chosenLED == -1 ) {
      chosenLED = currLED; 
      lastChosenTime = millis();

      if( chosenLED == 1 && delayTime >= winTime ) {
        delayTime = delayTime-20; 
        Serial.print( "minus time " );
        Serial.println( chosenLED );
      }
    }

    // if an LED has been selected over a second ago
    // start next round of game
    if ( chosenLED != -1 && ( millis()-lastChosenTime > 1000 )) {
      chosenLED = -1;
    }

    Serial.print( chosenLED );
    Serial.print( " ");
    Serial.println( delayTime );
  } 
  lastPress = millis();
}
