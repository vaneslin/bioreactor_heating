//define IO pins + temperature bounds
const int HEATER = P1_1;  // output pin 3 of heater element 
const int THERMISTOR = A0;  // input pin 2 for thermistor
const float maxTemp = 35.0;
const float minTemp = 25.0;
const float buffer = 3.0;

void setup() {
  //set baudrate and declare pins
	Serial.begin(9600);
	//pinMode(HEATER, OUTPUT);      
}

void loop() {
  // read analog input and convert to Celcius temperature
        double tempSensor = analogRead(THERMISTOR);	
        double temp = logf(10000.0 * (1023.0 / tempSensor - 1));
        temp = 1/(0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp);
        temp -= 273.15; //convert from K to C
        Serial.print("Temperature: ");
        Serial.print(temp);
        
//	if (temp > maxTemp - buffer){  // if temperature is too high, turn heating unit off
//		Serial.println(" Hot!");
//                digitalWrite(HEATER, LOW); //cuts off voltage to heater element
//                
//	} else if (temp < minTemp + buffer){  // if temperature is too low, turn heating unit on
//		Serial.println(" Cold!");
//                digitalWrite(HEATER, HIGH);  // cuts off voltage to heater element
//                
//	} else {
//		Serial.println(" Just right.");
//	}

	delay(1000);
}
