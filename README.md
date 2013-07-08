excuse-me-swatch
================

Simple one button game demonstrating using an external interrupt on an ATtiny. Created for E-Textile Summer Camp Swatchbook 2013.

The objective of the game is to hit the button when the green LED is lit up.  By using an external interrupt attached to the pushbutton, it's possible to know which LED was lit up when the button was pressed, even if it's the middle of a for loop.

There are two versions of the game in this repository - one for an Arduino Uno and the other for an ATtiny45.  The functionality is identical between the two.
