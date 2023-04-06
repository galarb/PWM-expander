/* ******************** * * *
      PWM expander Example
      Supporting pca9685 I2C expander module
      

 
 By: Gal Arbel
 2023
*/

 #include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);//object to represent PCA9685 at default I2C address  (0x40, more extensions up to 0x60)

class PWMexpander {
  public:
    PWMexpander() {
     }
    void begin(double bdrate) {
      Serial.begin(bdrate);
      pca9685.begin();  
      pca9685.setPWMFreq(500);   // Set PWM Frequency(24-1526Hz). arduino PWM works at 500Hz
    }

    byte i2c (int port, int value) { //writes a value to the i2c port
        value = map(value, 0, 255, 0, 4095);
        pca9685.setPWM(port, 0, value);    // Write to PCA9685. 
    }


    byte pinstat (int pin) {
        int val = pca9685.getPWM(pin);
        Serial.print("pin Value =");
        Serial.println(val);
        return(val);
      }


  private:
    
  
};
PWMexpander myexpander;
void setup() {
  pca9685.begin(115200); //Also starts the Serial monitor at the baudrate value
  Serial.println("Started");
}

void loop() {
  myexpander.i2c(2, 255);
  delay(1000);
  myexpander.i2c(2, 0);
  delay(1000);
}
