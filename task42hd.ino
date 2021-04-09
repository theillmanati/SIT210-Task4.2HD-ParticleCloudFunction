// -----------------------------------------------------------
// Task 4.2HD Particle - Calling a function from Web to Device
// -----------------------------------------------------------

/*-------------
Every program based on Wiring (programming language used by Arduino, 
and Particle devices) has two essential parts:
setup - runs once at the beginning of your program
loop - runs continuously over and over

This program will remotely call a function from the web to turn on one
of three LEDs, like a working prototype of a remote junction's traffic 
lights.
-------------*/

// For this task our variables will be led Red, led Blue and led Green.

int ledRed = D6; // Instead of writing D6 over and over again, we'll write ledRed
// You'll need to wire a red LED to this pin.

int ledBlue = D5; // Instead of writing D5 over and over again, we'll write ledBlue
// You'll need to wire a blue LED to this pin.

int ledGreen = D4; // Instead of writing D4 over and over again, we'll write ledGreen
// You'll need to wire a green LED to this pin.

// Having declared these variables, let's move on to the setup function.
// The setup function is a standard part of any microcontroller program.
// It runs only once when the device boots up or is reset.

void setup() {
    // We are going to tell our device that D4, D5 and D6 (which we named ledGreen, 
    // ledBlue and ledRed respectively) are going to be output
	// (That means that we will be sending voltage to them, rather than monitoring 
	// voltage that comes from them)

	pinMode(ledGreen, OUTPUT);
	pinMode(ledBlue, OUTPUT);
	pinMode(ledRed, OUTPUT);
	
    // For good measure, let's also make sure all LEDs are off when we start:
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, LOW);
    
	// We are also going to declare a Particle.function so that we can turn the LED 
	// on and off from the cloud.
    Particle.function("toggleLED", ledToggle);
    // This is saying that when we ask the cloud for the function "led", it will employ 
    // the function ledToggle() from this app.
}

// Next we have the loop function, the other essential part of a microcontroller program.
// Since we're waiting for input through the cloud this time though, we don't actually 
// need to put anything in the loop

void loop() {
    // Nothing to write here
}

// We're going to have a function that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Particle.function earlier.

int ledToggle(String colour) {
    /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how 
    the function should be used. In this case, telling the function "green" will turn the 
    green LED on and the other LEDs off, whilst telling the function "blue" will turn the 
    blue LED on and the other LEDs off, and telling it "red" will turn only the red LED on.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 2 for the green LED turning on, 1 for the blue LED turning
    on, 0 for the red LED turning on, and -1 if we received a totally bogus command that 
    didn't do anything to the LEDs.
    */

    if (colour=="green") {
        digitalWrite(ledGreen, HIGH);
        digitalWrite(ledBlue, LOW);
        digitalWrite(ledRed, LOW);
        return 2;
    }
    else if (colour=="blue") {
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledBlue, HIGH);
        digitalWrite(ledRed, LOW);
        return 1;
    }
    else if (colour=="red") {
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledBlue, LOW);
        digitalWrite(ledRed, HIGH);
        return 0;
    }
    else {
        return -1;
    }
}
