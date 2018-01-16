// Define IO Pins
const int HEATER_PIN = P1_4;    
const int TEMPOUT_PIN = P1_5;    
const int THERMISTOR_PIN = A0;  

// Set a default ideal temperature
float idealTemp = 26.50;  

void setup() {
  /* runs once and sets baudrate, declares output pins */
    Serial.begin(9600);
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(TEMPOUT_PIN, OUTPUT);
}

void loop() {
  /* constantly loops the following:
   * update value idealTemp from main MSP
   * calculate temperature
   * turn heater on/off
   */
   
 // read ideal temperature from main MSP
    int serial_size=Serial.available();
    if(serial_size>0){
      idealTemp=0;
      if(serial_size>1){
        serial_size=2;
      }
      for(int j=0;j<serial_size;j++){
        idealTemp*=10;
        idealTemp+=(Serial.read()-48);
      }
    }
        
 // read analog ADC input and convert to Celcius temperature using Steinhart-Hart equation @ https://www.thermistor.com/calculators
    int ADC = analogRead(THERMISTOR_PIN);
    double temp = logf(((10240000/(ADC - 200.0)) - 10000));  // adjust ADC range as per calibration
    temp = 1.0/ (0.001125161025848 + (0.000234721098632 + (0.000000085877049 * temp * temp)) * temp);
    temp -= 273.15;
    temp += 17.5;  // add set constant as per calibration
    Serial.println(temp);
        
 // write temperature to main MSP
    int temp_int = (int) temp;  // get int representation of temperature
    digitalWrite(TEMPOUT_PIN, temp_int);  
        
 // write to heater element and regulate temperature
    if (temp > idealTemp){ 
              digitalWrite(HEATER_PIN, LOW);           
    else digitalWrite(HEATER_PIN, HIGH);  
    
 // ~one second delay to not mess up reading/writing
    delay(1000);
}
