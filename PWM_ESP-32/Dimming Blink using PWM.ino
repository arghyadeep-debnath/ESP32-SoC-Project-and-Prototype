

// the number of the LED pin
const int ledPin = 16;  // GPIO 16

void setup() {
  
  pinMode(ledPin, OUTPUT);
}

void loop(){
  
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   // increase the LED brightness
    // changing the LED brightness with PWM
    analogWrite(ledPin, dutyCycle);
    delay(15);
  }


  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){       // decrease the LED brightness
    analogWrite(ledPin, dutyCycle);
    delay(15);
  }
}
