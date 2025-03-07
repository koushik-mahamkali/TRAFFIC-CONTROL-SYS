int redLight = 9;    
int yellowLight = 10; 
int greenLight = 11; 

int vehicleCount = 0;
int ambulanceCount = 0;

void setup() {
  pinMode(redLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int data = Serial.read();
    if (data == 1) {
      // Ambulance detected, adjust timing of lights
      digitalWrite(redLight, LOW);
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, HIGH);
      delay(15000); // Extended green light duration for ambulances

      digitalWrite(redLight, LOW);
      digitalWrite(yellowLight, HIGH);
      digitalWrite(greenLight, LOW);
      delay(5000);

      digitalWrite(redLight, HIGH);
      digitalWrite(yellowLight, LOW);
      digitalWrite(greenLight, LOW);
      delay(5000);
    } else {
      vehicleCount = data;

      // Ensure vehicle count is valid and above 0
      if (vehicleCount > 0) {
        if (vehicleCount > 25) {
          digitalWrite(redLight, LOW);
          digitalWrite(yellowLight, LOW);
          digitalWrite(greenLight, HIGH);
          delay(50000); // High traffic, long green light

          digitalWrite(redLight, LOW);
          digitalWrite(yellowLight, HIGH);
          digitalWrite(greenLight, LOW);
          delay(5000);

          digitalWrite(redLight, HIGH);
          digitalWrite(yellowLight, LOW);
          digitalWrite(greenLight, LOW);
          delay(5000);
        }
        else {
          // Calculate the green light duration based on the vehicle count
          int greenLightDuration = 2000 * vehicleCount; // 2 seconds per vehicle
          greenLightDuration = max(greenLightDuration, 5000);  // Ensure minimum green light duration of 5 seconds

          digitalWrite(redLight, LOW);
          digitalWrite(yellowLight, LOW);
          digitalWrite(greenLight, HIGH);
          delay(greenLightDuration);  // Set the delay to the calculated duration

          digitalWrite(redLight, LOW);
          digitalWrite(yellowLight, HIGH);
          digitalWrite(greenLight, LOW);
          delay(5000);

          digitalWrite(redLight, HIGH);
          digitalWrite(yellowLight, LOW);
          digitalWrite(greenLight, LOW);
          delay(5000);
        }
      }
    }
  }
}
