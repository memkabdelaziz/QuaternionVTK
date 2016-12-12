/* MPU9250 Basic Example Code
 by: Kris Winer
 date: April 1, 2014
 license: Beerware - Use this code however you'd like. If you 
 find it useful you can buy me a beer some time.
 
 Demonstrate basic MPU-9250 functionality including parameterizing the register addresses, initializing the sensor, 
 getting properly scaled accelerometer, gyroscope, and magnetometer data out. Added display functions to 
 allow display to on breadboard monitor. Addition of 9 DoF sensor fusion using open source Madgwick and 
 Mahony filter algorithms. Sketch runs on the 3.3 V 8 MHz Pro Mini and the Teensy 3.1.
 
 SDA and SCL should have external pull-up resistors (to 3.3V).
 10k resistors are on the EMSENSR-9250 breakout board.
 
 Hardware setup:
 MPU9250 Breakout --------- Arduino
 VDD ---------------------- 3.3V
 VDDI --------------------- 3.3V
 SDA ----------------------- A4
 SCL ----------------------- A5
 GND ---------------------- GND
 
 Note: The MPU9250 is an I2C sensor and uses the Arduino Wire library. 
 Because the sensor is not 5V tolerant, we are using a 3.3 V 8 MHz Pro Mini or a 3.3 V Teensy 3.1.
 We have disabled the internal pull-ups used by the Wire library in the Wire.h/twi.c utility file.
 We are also using the 400 kHz fast I2C mode by setting the TWI_FREQ  to 400000L /twi.h utility file.
 */
 
//#include "ST_F401_84MHZ.h" 
//F401_init84 myinit(0);
#include "mbed.h"
#include "MPU9250.h"
#include "rtos.h"

//#include "N5110.h"

// Using NOKIA 5110 monochrome 84 x 48 pixel display
// pin 9 - Serial clock out (SCLK)
// pin 8 - Serial data out (DIN)
// pin 7 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 6 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(9, 8, 7, 5, 6);

I2C newi2c_1(p9,p10); 
I2C newi2c_2(p28,p27); 

DigitalOut led2(LED2);


void OutputQuaternions(void const *args)
{       
    MPU9250* mpu9250;
    mpu9250 = (MPU9250*)args;
    mpu9250->Calculations();
           
}




int main()
{
  //pc.baud(921600);  

  //Set up I2C
  newi2c_1.frequency(400000);  // use fast (400 kHz) I2C 
  newi2c_2.frequency(400000);  // use fast (400 kHz) I2C   
  
  //MPU9250 mpu9250_1(newi2c_1, 0x68<<1, 1);   //Board 1
  //MPU9250 mpu9250_2(newi2c_1, 0x69<<1, 2); //Board 2
  MPU9250 mpu9250_3(newi2c_2, 0x68<<1, 3); //Board 3
  //MPU9250 mpu9250_4(newi2c_2, 0x69<<1, 4); //Board 4

/*
mpu9250_3.testConnection();
float * dest1;
float * dest2;
mpu9250_3.magcalMPU9250(dest1,dest2);
*/
//Thread thread1(OutputQuaternions, &mpu9250_1, osPriorityNormal, DEFAULT_STACK_SIZE,NULL);
//Thread thread2(OutputQuaternions, &mpu9250_2, osPriorityNormal, DEFAULT_STACK_SIZE,NULL);
Thread thread3(OutputQuaternions, &mpu9250_3, osPriorityNormal, DEFAULT_STACK_SIZE,NULL);
//Thread thread4(OutputQuaternions, &mpu9250_4, osPriorityNormal, DEFAULT_STACK_SIZE,NULL);

while(true){};
   //Thread t1 (osPriority priority=osPriorityNormal, uint32_t stack_size=DEFAULT_STACK_SIZE, unsigned char *stack_pointer=NULL);
   //start (Thread *t1, mpu9250_1.Calculations());

  //Thread t2(mpu9250_2.Calculations(int));  //Board 2
  //mpu9250_3.Calculations(3);  //Board 3
  //mpu9250_4.Calculations(4);  //Board 4
  
 
  
  //MPU9250 mpu9250();      
  //mpu9250.printQs();
 }

