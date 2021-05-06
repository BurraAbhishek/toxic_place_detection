void setup() {
    // This code is based on the circuit diagram described in the README section.
    pinMode(2, OUTPUT); // Green Light
    pinMode(4, OUTPUT); // Yellow Light
    pinMode(6, OUTPUT); // Red Light
    pinMode(8, OUTPUT); // Buzzer
    pinMode(A0, INPUT); // Gas sensor 1
    // pinMode(A1, INPUT); // Gas sensor 2
    // pinMode(A2, INPUT); // Gas sensor 3
    // pinMode(A3, INPUT); // Gas sensor 4
    // pinMode(A4, INPUT); // Gas sensor 5
    // pinMode(A5, INPUT); // Gas sensor 6
}

void loop() {
    // Interfacing with MQ135 to begin with
    // These values may not be correct.
    int safety_index = -1;
    int air_quality = analogRead(A0);
    if(air_quality < 150) {
        // Air quality is good
        safety_index = setSafetyIndex(safety_index, 0);
    } else if(air_quality > 150 && air_quality < 300) {
        // Air quality is moderate
        safety_index = setSafetyIndex(safety_index, 1);
    } else if(air_quality > 300) {
        // Air quality is extremely poor
        safety_index = setSafetyIndex(safety_index, 2);
    }
    if(safety_index == 0) {
        // Safe environment
        safezone();
    } else if(safety_index == 1) {
        // Slightly hazardous
        warnzone();
    } else if(safety_index == 2) {
        // Extremely hazardous
        dangerzone();
    }
    delay(1000); // The time interval between two readings is 1000 milliseconds (1 second).
}

// Set the safety index for this program - 0 (Safe), 1 (Warning), 2 (Hazardous)
int setSafetyIndex(int current_safety_index, int desired_safety_index) {
    int new_safety_index = current_safety_index;
    if(desired_safety_index > current_safety_index) {
        new_safety_index = desired_safety_index;
    }
    return new_safety_index;
}

// Whatever should happen in case of safe environment - No hazards ahead.
void safezone() {
    digitalWrite(2, HIGH); // Green light glows
    digitalWrite(4, LOW); // Yellow light does not glow
    digitalWrite(6, LOW); // Red light does not glow
    digitalWrite(8, LOW); // Switch off the buzzer
}

// Whatever should happen in case of approach towards hazardous environment - Warn the user of the dangers ahead
void warnzone() {
    digitalWrite(2, LOW); // Green light does not glow
    digitalWrite(4, HIGH); // Yellow light glows
    digitalWrite(6, LOW); // Red light does not glow
    // Buzzer beeps at regular intervals
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
}

// Whatever should happen in a hazardous environment - Warn the user to vacate immediately
void dangerzone() {
    digitalWrite(2, LOW); // Green light does not glow
    digitalWrite(4, LOW); // Yellow light does not glow
    digitalWrite(6, HIGH); // Red light glows
    digitalWrite(8, HIGH); // The buzzer emits continuous sound until the environment is safe
}
