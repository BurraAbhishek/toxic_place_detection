void setup() {
    // This code is based on the circuit diagram described in the README section.
    pinMode(2, OUTPUT); // Green Light
    pinMode(4, OUTPUT); // Yellow Light
    pinMode(6, OUTPUT); // Red Light
    pinMode(8, OUTPUT); // Buzzer
    pinMode(A0, INPUT); // Gas sensor 1 - MQ135
    pinMode(A1, INPUT); // Gas sensor 2 - MQ136
    pinMode(A2, INPUT); // Gas sensor 3 - MQ137
    pinMode(A3, INPUT); // Gas sensor 4 - MQ9
    pinMode(A4, INPUT); // Gas sensor 5 - MQ5
    // pinMode(A5, INPUT); // Gas sensor 6 - MQ2, not implemented due to lower permissible limits in MQ9
}


void loop() {
    // Preset the safety index to -1
    int safety_index = -1;
    
    // Interfacing with MQ135 to begin with
    float air_quality = analogRead(A0);
    // The standard upper limit is 100, considering sensitive groups.
    if(air_quality < 100) {
        // Air quality is good
        safety_index = setSafetyIndex(safety_index, 0);
    } else if(air_quality > 100 && air_quality < 250) {
        // Air quality is moderate
        safety_index = setSafetyIndex(safety_index, 1);
    } else if(air_quality > 250) {
        // Air quality is extremely poor
        safety_index = setSafetyIndex(safety_index, 2);
    }

    // Interfacing with MQ136
    float h2s_detected = analogRead(A1);    
    // The standard upper limit is 1 PPM, according to OSHA(2011).
    if(h2s_detected < 1) {
        // Safe
        safety_index = setSafetyIndex(safety_index, 0);
    } else if(h2s_detected > 1 && h2s_detected < 30) {
        // Permissible limits
        safety_index = setSafetyIndex(safety_index, 1);
    } else if(h2s_detected > 30) {
        // Hazardous
        safety_index = setSafetyIndex(safety_index, 2);
    }

    // Interfacing with MQ137
    float ammonia_detected = analogRead(A2);    
    // The recommended safe limit is 25 PPM, according to OSHA(2019).
    if(ammonia_detected < 25) {
        // Safe
        safety_index = setSafetyIndex(safety_index, 0);
    } else if(ammonia_detected > 25 && ammonia_detected < 50) {
        // Permissible limits, according to OSHA, 50 limit strictly enforced.
        safety_index = setSafetyIndex(safety_index, 1);
    } else if(ammonia_detected > 50) {
        // Hazardous
        safety_index = setSafetyIndex(safety_index, 2);
    }

    // Interfacing with MQ9
    float co_detected = analogRead(A3);    
    // The recommended safe limit is 35 PPM, according to OSHA.
    if(co_detected < 35) {
        // Safe
        safety_index = setSafetyIndex(safety_index, 0);
    } else if(co_detected > 35 && co_detected < 50) {
        // Permissible limits, according to OSHA.
        safety_index = setSafetyIndex(safety_index, 1);
    } else if(co_detected > 50) {
        // Hazardous
        safety_index = setSafetyIndex(safety_index, 2);
    }

    // Interfacing with MQ5
    float lpg_naturalgas_detected = analogRead(A4);    
    // The recommended limit is 1000 PPM, according to OSHA.
    if(lpg_naturalgas_detected < 1000) {
        // Safe
        safety_index = setSafetyIndex(safety_index, 0);
    } else iflpg_naturalgas_detected > 1000 && lpg_naturalgas_detected < 2000) {
        // Revised IDLH: 2000 PPM
        safety_index = setSafetyIndex(safety_index, 1);
    } else if(lpg_naturalgas_detected > 2000) {
        // Hazardous
        safety_index = setSafetyIndex(safety_index, 2);
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
