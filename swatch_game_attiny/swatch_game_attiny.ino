#define NUM_LEDS 3

int leds[] = {
  0, 1, 3};
int button = 2;

volatile int chosenLED = -1;
int currLED = 0;
int prevLED = 0;
volatile int delayTime = 300;

volatile int lastButtonTime = 0;

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
}

void loop() {
  // play game if we haven't reaching fastest level
  if ( delayTime > 80 ){
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
}

void buttonHit () {
  // select LED
  if( chosenLED == -1 ) {
    chosenLED = currLED; 
    lastButtonTime = millis();

    if( chosenLED == 1 && delayTime > 60 ) {
      delayTime = delayTime-20; 
    }
  }

  // if an LED has been selected over a second ago
  // start next round of game
  if ( chosenLED != -1 && ( millis()-lastButtonTime > 1000 )) {
    chosenLED = -1;
  }
}
