const int HEATER_PIN = P1_1;  // output pin 3 of heater element 
const int TEMPOUT_PIN = P1_2; //output pin 4 of temperature to main controller

const int THERMISTOR_PIN = A0;  // input pin 2 for THERMISTOR_PIN
const int IDEAL = A5;  // input pin 5 for ideal temperature

float idealTemp = 27.0;  // default ideal temp value
const float buffer = 0.5; //range of fluctation from ideal temperature

void setup() {
  //set baudrate and declare pins
	Serial.begin(9600);
	pinMode(HEATER_PIN, OUTPUT);
        //pinMode(TEMPOUT_PIN, OUTPUT);
}

void loop() {
  //read ideal temperature
        //idealTemp = analogRead(IDEAL);
        //idealTemp = int(0.126*pulseIn(IDEAL, HIGH)-0.1246)
        
  // read analog input and convert to Celcius temperature ver 2
        
        float ADCvalue;
        float Resistance;
        ADCvalue = analogRead(THERMISTOR_PIN);
        Serial.print("Analog ");
        Serial.print(ADCvalue);
        Serial.print(" = ");
        //convert value to resistance
        Resistance = (1023.0 / ADCvalue) - 1.0;
        Resistance = 10000.0 / Resistance;
        Serial.print(Resistance);
        Serial.println(" Ohm");
        
        float temp;
        temp = Resistance / 10000.0; // (R/Ro)
        temp = logf(temp); // ln(R/Ro)
        temp /= 4220.0; // 1/B * ln(R/Ro)
        temp += 1.0 / (25.0 + 273.15); // + (1/To)
        temp = 1.0 / temp; // Invert
        temp -= 273.15; // convert to C
        Serial.print(temp);
        Serial.println(" oC");

        
 // write temperature to main MSP
        //int temp_int = (int) temp;  // get int representation of temperature
        //digitalWrite(TEMPOUT_PIN, temp_int);
        
        
// regulate temperature
	if (temp > idealTemp){  // if temperature is too high, turn heating unit off
		Serial.println(" Hot!");
                digitalWrite(HEATER_PIN, LOW); //cuts off voltage to heater element             
	} else if (temp < idealTemp){  // if temperature is too low, turn heating unit on
		Serial.println(" Cold!");
                digitalWrite(HEATER_PIN, HIGH);  // cuts off voltage to heater element
	} else {
		Serial.println(" Just right.");
	}
	delay(2000);
}
