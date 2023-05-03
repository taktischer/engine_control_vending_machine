short current_direction = 0;
int start = 0;

#define MOTOR_FORWARD_PIN 2
#define MOTOR_BACKWARDS_PIN 4
#define SENSOR_PIN 5

void setup()
{
    // set MOTOR_FORWARD_PIN and MOTOR_BACKWARDS_PIN to output
    pinMode(MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(MOTOR_BACKWARDS_PIN, OUTPUT);

    // set SENSOR_PIN to input
    pinMode(SENSOR_PIN, INPUT);
    
    // reset the pins
    digitalWrite(MOTOR_FORWARD_PIN, 0);
    digitalWrite(MOTOR_BACKWARDS_PIN, 0);
}


void loop()
{
    // check if SENSOR_PIN gets an active value
    if (digitalRead(SENSOR_PIN) != 0){
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
        // reset start and both MOTOR_PINS
        start = 0;
        digitalWrite(MOTOR_FORWARD_PIN, 0);
        digitalWrite(MOTOR_BACKWARDS_PIN, 0);
    }
}
