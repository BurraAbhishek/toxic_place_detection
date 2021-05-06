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
    int air_quality = analogRead(A0);
    if(air_quality < 150) {
        // Safe - Green
        safezone();
    } else if(air_quality > 150 && air_quality < 300) {
        // Slightly hazardous - indicates severe hazards ahead as warning - Yellow
        warnzone();
    } else if(air_quality > 300) {
        // Extremely hazardous - Must avoid - Red
        dangerzone();
    }
    delay(1000); // The time interval between two readings is 1000 milliseconds (1 second).
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
