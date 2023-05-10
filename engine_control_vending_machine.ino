// definitions
#define ESP_PIN 3
#define MOTOR_FORWARD_PIN 2
#define MOTOR_BACKWARDS_PIN 4
#define BUTTON_PIN 5
#define INDUCTION_SENSOR_PIN 6
#define SLEEP_TIME 100
#define LOWEST_VALUE 2.7
#define HIGHEST_VALUE 4.7

short current_direction = 0;
int start = 0;
double keep_rotating = 0.0;
int time_keep_rotating;

void setup()
{
    // set MOTOR_FORWARD_PIN and MOTOR_BACKWARDS_PIN to output
    pinMode(MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(MOTOR_BACKWARDS_PIN, OUTPUT);

    // set BUTTON_PIN to input
    pinMode(BUTTON_PIN, INPUT);

    // reset the MOTOR_PINS
    digitalWrite(MOTOR_FORWARD_PIN, 0);
    digitalWrite(MOTOR_BACKWARDS_PIN, 0);
}


void loop()
{
    // check ESP_32 input and turn forward
    // turn until inductive sensor sends an active value
    // (plus additional time from potentiometer)
    if(digitalRead(ESP_PIN) == 1){
        // rotate motor
        digitalWrite(MOTOR_FORWARD_PIN, 1);
        for(int i = 0; i < 4; i++){
            while(!digitalRead(INDUCTION_SENSOR_PIN)){
                // get voltage value of induction sensor
                keep_rotating = digitalRead(INDUCTION_SENSOR_PIN);
                
                // mapping input from INDUCTION_SENSOR_PIN
                map(keep_rotating, LOWEST_VALUE, HIGHEST_VALUE, 0, 1023);

            }
        }
        // keep rotating until the time is depleted 
        time_keep_rotating = 1023 - keep_rotating;
        while(time_keep_rotating > 0){
            time_keep_rotating -= SLEEP_TIME;
            delay(1000);
        }
        digitalWrite(MOTOR_FORWARD_PIN,0);

    }
    // check if button is pressed (connected to SENSOR_PIN)
    if (digitalRead(BUTTON_PIN) == 1){
        if (start==0){
            // set start to current runtime (milliseconds)
            start = millis();
        }
            // rotate the engine at the chosen PIN
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
        // reset start value and MOTOR_PINS
        start = 0;
        digitalWrite(MOTOR_FORWARD_PIN, 0);
        digitalWrite(MOTOR_BACKWARDS_PIN, 0);
    }
}
