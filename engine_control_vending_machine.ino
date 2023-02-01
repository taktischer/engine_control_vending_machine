short current_direction = 0;
int start = 0;
void setup()
{
    // set pin 0 and 1 to output
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);

    // set pin 2 to input
    pinMode(2, INPUT);
    
    // reset the pins
    digitalWrite(0, 0);
    digitalWrite(1, 0);
}


void loop()
{
    // check if button is pressed (connected to pin 2)
    if (digitalRead(2) == 1){
        if (start==0){
            // set start to current runtime (milliseconds)
            start = millis();
        }
        // rotate the engine at the chosen pin (0/1)
        else if (millis()-start>1000){
            digitalWrite(current_direction, 1);
        }
    } else {
        // check if the difference between start and the current runtime is lower than 1 second
        if (millis()-start<=1000 && start != 0){
            // change the rotation direction to the opposite
            if (current_direction == 0){
                current_direction = 1;
            } else {
                current_direction = 0;
            }
        }
        // reset start and both LEDs
        start = 0;
        digitalWrite(0, 0);
        digitalWrite(1, 0);
    }
}
