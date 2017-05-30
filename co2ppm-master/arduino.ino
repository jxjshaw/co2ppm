
#include <SPI.h>

#define CHILD_ID_AIQ 0
#define AIQ_SENSOR_ANALOG_PIN 6

float valAIQ =0.0;
float lastAIQ =0.0;

void setup()
{

  Serial.begin(9600);
  pinMode(AIQ_SENSOR_ANALOG_PIN, INPUT);

}

void loop() {

  //unsigned long duration = pulseIn(AIQ_SENSOR_ANALOG_PIN, HIGH);
  while(digitalRead(AIQ_SENSOR_ANALOG_PIN) == HIGH) {;}
  //wait for the pin to go HIGH and measure HIGH time
  unsigned long duration = pulseIn(AIQ_SENSOR_ANALOG_PIN, HIGH);

  //Serial.print(duration/1000); Serial.println(" ms ");
  //from datasheet
	//CO2 ppm = 2000 * (Th - 2ms) / (Th + Tl - 4ms)
	//  given Tl + Th = 1004
	//        Tl = 1004 - Th
	//        = 2000 * (Th - 2ms) / (Th + 1004 - Th -4ms)
	//        = 2000 * (Th - 2ms) / 1000 = 2 * (Th - 2ms)
  long co2ppm = 2 * ((duration/1000) - 2);
  //Serial.print(co2ppm);
  // if ((co2ppm != lastAIQ)&&(abs(co2ppm-lastAIQ)>=10)) {
  //     gw.send(msg.set((long)ceil(co2ppm)));
  //     lastAIQ = ceil(co2ppm);
  // }

   //Serial.print(co2ppm);
  if ((co2ppm != lastAIQ)&&(abs(co2ppm-lastAIQ)>=3)&&(duration!=0)) {
  //     gw.send(msg.set((long)ceil(co2ppm)));
        Serial.print("co2: ");
        Serial.println(co2ppm);
        Serial.print("\n");
        lastAIQ = ceil(co2ppm);
  }

   delay(3000);


}
