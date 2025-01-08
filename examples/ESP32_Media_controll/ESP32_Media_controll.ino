/* Media control with rotary encoder */

#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

#define outputA 13 //CLK Pin of Rotary encoder
#define outputB 34 //DT Pin of Rotary encoder
#define PinSW 25 //Switch pin of Rotary encoder
//Gnd --> Gnd 

int aState;
int aLastState;
int buttonState = HIGH;   // Assuming the button is normally open
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  

void setup()
{ 
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleKeyboard.begin();
    pinMode (outputA,INPUT_PULLUP);
    pinMode (outputB,INPUT_PULLUP);
    pinMode(PinSW, INPUT_PULLUP);
    
    aLastState = digitalRead(outputA);   
} 

void loop()
{
    if(bleKeyboard.isConnected()) {

        int reading = digitalRead(PinSW);

        if (reading != lastButtonState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (reading != buttonState) {
            buttonState = reading;

            if (!(digitalRead(PinSW))) {
                    bleKeyboard.write(KEY_MEDIA_MUTE);
                    delay(250);    
                }
            }
        }

        lastButtonState = reading;
        
        aState = digitalRead(outputA); // Reads the "current" state of the outputA
        if (aState != aLastState){     
            if (digitalRead(outputB) != aState) { 
            bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
            bleKeyboard.releaseAll();
            } else {
            bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
            }
        } 
        aLastState = aState; // Updates the previous state of the outputA with the current state
    }
}
