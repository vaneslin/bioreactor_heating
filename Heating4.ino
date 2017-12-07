const int HEATER_PIN = P1_1;  // output pin 3 of heater element 
const int TEMPOUT_PIN = P1_2; //output pin 4 of (int) temperature to main MSP

const int THERMISTOR_PIN = A0;  // input pin 2 of thermistor
const int IDEAL = A5;  // input pin 5 to read ideal temperature from main MSP

float idealTemp = 27.0;  // default ideal temp value
const float buffer = 0.5; // range of fluctation from ideal temperature, if needed

void setup() {
  //set baudrate and declare pins
	Serial.begin(9600);
	pinMode(HEATER_PIN, OUTPUT);
        //pinMode(TEMPOUT_PIN, OUTPUT);
}

void loop() {
  //read ideal temperature
        //idealTemp = analogRead(IDEAL); 
        //OR
        //idealTemp = int(0.126*pulseIn(IDEAL, HIGH) - 0.1246)
        
  // read analog ADC input and convert to Celcius temperature,  v3.0
        int ADC = analogRead(THERMISTOR_PIN);
        double temp = logf(((10240000/(ADC - 200.0)) - 10000));  // adjust ADC range as per calibration
        temp = 1.0/ (0.001125161025848 + (0.000234721098632 + (0.000000085877049 * temp * temp)) * temp);
        temp -= 273.15;
        temp += 17.5;  // add set constant as per calibration
        Serial.print(temp);
        Serial.println(" oC");
        
 // write temperature to main MSP
        //int temp_int = (int) temp;  // get int representation of temperature
        //digitalWrite(TEMPOUT_PIN, temp_int);  
        
// write to heater element and regulate temperature
	if (temp > idealTemp){ 
		Serial.println(" Hot!");
                digitalWrite(HEATER_PIN, LOW); // turns off heater element             
	} else if (temp < idealTemp){ 
		Serial.println(" Cold!");
                digitalWrite(HEATER_PIN, HIGH);  // turns on heater element
	} else {
		Serial.println(" Just right.");
	}
	delay(1000);
}
