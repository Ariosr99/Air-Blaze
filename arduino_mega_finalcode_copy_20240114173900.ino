#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>
#include <DHT.h>

#define DHTPIN 4     // esp8266 D2 pin map as 4 in Arduino IDE
#define DHTTYPE DHT11   // there are multiple kinds of DHT sensors

#define Board                   ("Arduino MEGA")
#define Pin135                   (A2)  // Analog input 2 of your Arduino for MQ135
#define Pin7                     (A3)  // Analog input 3 of your Arduino for MQ7
#define Pin6                     (A7)  // Analog input 7 of your Arduino for MQ6

#define RatioMQ135CleanAir        (3.6) // RS / R0 = 10 ppm 
#define RatioMQ7CleanAir          (27.5) // RS / R0 = 27.5 ppm  
#define RatioMQ6CleanAir          (9.6) // RS / R0 = 9.6 ppm 
#define ADC_Bit_Resolution        (10) // 10-bit ADC 
#define Voltage_Resolution        (5) // Volt resolution to calc the voltage
#define Type                      ("Arduino MEGA") // Board used

DHT dht(DHTPIN, DHTTYPE);
MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin135, Type);
MQUnifiedsensor MQ7(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin7, Type);
MQUnifiedsensor MQ6(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin6, Type);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10000);

  // Wait for serial to initialize.
  while(!Serial) { }

  dht.begin();

  MQ135.init();
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setR0(9.03);
  MQ7.init();
  MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ7.setR0(5.90);
  MQ6.init();
  MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ6.setR0(13.93);

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running Gas and DHT!");
  Serial.println("-------------------------------------");
}

int timeSinceLastRead = 0;

void loop() {
  // Gas sensor readings
  MQ135.update();  
  MQ7.update();
  MQ6.update();

  MQ135.setA(300); MQ135.setB(-8.308); // smoke 
  float smoke = MQ135.readSensor(); 
  MQ135.setA(110.47); MQ135.setB(-2.862); // CO2 
  float CO2 = MQ135.readSensor(); 
  MQ7.setA(30.042); MQ7.setB(-1.518); // CO
  float CO = MQ7.readSensor(); 
  MQ6.setA(150.5); MQ6.setB(-2.186); // flammable gas
  float FG = MQ6.readSensor();

  // DHT sensor readings
  if (timeSinceLastRead > 2000) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }

    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    // Print gas sensor readings
    Serial.print("Gas - Smoke:U");
    Serial.print(smoke);
    Serial.print(" CO2:V ");
    Serial.print(CO2);
    Serial.print(" CO:W ");
    Serial.print(CO);
    Serial.print("Flammable Gas:X");
    Serial.println(FG);

    // Print DHT sensor readings
    Serial.print("DHT - Humidity:Y");
    Serial.print(h);
    Serial.print(" %\tTemperature:Z");
    Serial.print(t);
    Serial.println(" *C ");

    timeSinceLastRead = 0;
  }
  
  delay(100);
  timeSinceLastRead += 100;
}