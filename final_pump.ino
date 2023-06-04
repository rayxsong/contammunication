#include <CapacitiveSensor.h>
#include <Servo.h>

Servo servo1;  // pump servo 1
Servo servo2;  // pump servo 2
Servo servo3;  // dipping loop servo
CapacitiveSensor  cs_4_2 = CapacitiveSensor(4,2); // finger tip sensor

int pos = 40; // starting point of the pump servos
int end = 180; // ending point of the pump servos
int pos_dip = 12; // starting point of the dipping loop

void setup() {
  servo1.attach(5); // attach the left servo to the pump
  servo2.attach(6); // attach the right servo to the pump
  servo3.attach(9); // attach the dipping servo
  servo1.write(pos);
  servo3.write(pos_dip);
  servo2.write(180 - pos);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1
  Serial.begin(9600);
}

void loop() {
  long start = millis();
  long total =  cs_4_2.capacitiveSensor(50);

  Serial.println(millis() - start);        // check on performance in milliseconds
  Serial.print("total:"); // print finger tip sensor output
  Serial.println(total);
  delay(10);
  // dipping loop back to nozzle
  for (int i = 0; i <= 150; i += 3) {
    servo3.write(180 - pos_dip);
    delay(50);
  }
  // delay(1500);
  if (total > 100) {
    // pump moving forward stage 1
    for (pos = 40; pos <= end - 90; pos += 3) {
      servo1.write(pos);
      servo2.write(180 - pos);
      delay(15);
    }
    // pump moving forward stage 2
    for (pos = end - 90; pos <= end; pos += 15) {
      servo1.write(pos);
      servo2.write(180 - pos);
      delay(15);
    }
    // pump moving backward
    for (pos = end; pos >= 40; pos -= 10) {
      servo1.write(pos);
      servo2.write(185 - pos);
      delay(15);
    }
    delay(500);
  }
  // dipping soap
  for (int i = 180; i >= 0; i -= 3) {
   servo3.write(pos_dip);
   delay(50);
  }
}