
// http://stackoverflow.com/questions/1653958/why-are-ifndef-and-define-used-in-c-header-files

// Those are called Include guards (to prevent multiple inclusion)
// Once the header is included, it checks if a unique value (in this case HEADERFILE_H) is defined. Then if it's not defined, it defines it and continues to the rest of the page.
// When the code is included again, the first ifndef fails, resulting in a blank file.
// That prevent double declaration of any identifiers such as types, enums and static variables.

#ifndef MPU9250_H  // If not defined
#define MPU9250_H  // define

// Pre-processor directives (is a small programme that runs before the
// compilation process takes place) Examples:
// (1) include
// (2) define
// (3) ifndef

// Conditional compilation -> Compile part of the code, not the entire code
// depending on some condition
// Other conditional compilation macros:
// #if, #endif, #elif (else if) #else
// ifdef ->  If it is defined

// Angular brackets to include the standard header files
#include<stdio.h>
#include<time.h>
// Double quotes to include the user-defined header files
//#include "mbed.h"
#include "math.h"


// #define is a pre-processor directive that defines an identifier (which is
// also refered to as the macro name) and a character sequence (which is also
// refered to as the macro replacement). The character sequence will replace
// the identifier each time it is encountered in the source file.

// There are two types of macros
// Function type macros
// Object type macros

// Object type macros
// Macro is a fragment of code which is given some name
// # define register1 0x22
// register1 -> Macro name (or) Identifier
// 0x22 -> Macro replacement (or) character sequence
// Whenever I use the identifier register1 in my programme, register will be
// replaced by "Egypt"

// Function type macros
// define ABS(number)  ((number) < 0 ? -(number) : (number))
// depending on the input argument number one of the ouputs is outputted


// Accelerometer x, y and z axes data
// Accelerometer x-axis data
#define ACCEL_XOUT_H     0x3B   // High byte of accelerometer x-axis data
#define ACCEL_XOUT_L     0x3C   // Low byte of accelerometer x-axis data
// Accelerometer y-axis data
#define ACCEL_YOUT_H     0x3D   // High byte of accelerometer y-axis data
#define ACCEL_YOUT_L     0x3E   // Low byte of accelerometer y-axis data
// Accelerometer z-axis data
#define ACCEL_ZOUT_H     0x3F   // High byte of accelerometer z-axis data
#define ACCEL_ZOUT_L     0x40   // low byte of accelerometer z-axis data

// Temperature Sensor Output
#define TEMP_OUT_H       0x41  // High byte of temperature sensor output
#define TEMP_OUT_L       0x42  // Low byte of temperature sensor output

// Gyroscope x, y and z axes data
// Gyroscope x-axis data
#define GYRO_XOUT_H      0x43  // High byte of X-Axis gyroscope output
#define GYRO_XOUT_L      0x44  // Low byte of X-Axis gyroscope output
// Gyroscope y-axis data
#define GYRO_YOUT_H      0x45  // High byte of Y-Axis gyroscope output
#define GYRO_YOUT_L      0x46  // Low byte of Y-Axis gyroscope output
// Gyroscope z-axis data
#define GYRO_ZOUT_H      0x47  // High byte of Z-Axis gyroscope output
#define GYRO_ZOUT_L      0x48  // low byte of Z-Axis gyroscope output

// MPU-9250's Magnetometer (AK8963) x, y and z axes data
// Magnetometer x-axis data
#define AK8963_XOUT_L    0x03  // low byte of X-axis Magnetometer data
#define AK8963_XOUT_H    0x04  // High byte of X-axis Magnetometer data
// Magnetometer y-axis data
#define AK8963_YOUT_L    0x05  // Low byte of Y-axis Magnetometer data
#define AK8963_YOUT_H    0x06  // High byte of Y-axis Magnetometer data
// Magnetometer z-axis data
#define AK8963_ZOUT_L    0x07  // Low byte of Z-axis Magnetometer data
#define AK8963_ZOUT_H    0x08  // High byte of Z-axis Magnetometer data

// const vs static
// constant is unable to be modified
// only one copy for the entire class (so all objects share this static variable)


// Set initial input parameters
//enumerated list of constants
// These scales (Ascale) helps in calculating the sensitivity of the accelerometer,
// (Ascale) gyroscope (Gscale) and magnetometer (Mscale). It is used to obtain
// gRes, aRes, mRes scale resolutions per LSB for the sensors

// In this case, the default values of this list (Ascale)
//  AFS_2G =0 , AFS_4G = 1, AFS_8G = 2, AFS_16G = 3
// scale range (The list of constants below are used later in a switch/case
// function to obtain the resolution of the sensor accordingly)
enum Ascale {
  AFS_2G, // programmable scale range of +- 2g
  AFS_4G, // programmable scale range of +- 4g
  AFS_8G, // programmable scale range of +- 8g
  AFS_16G // programmable scale range of +- 16g
 // where g = 9.8 m/s^2
 //Accelerometers are devices that measure acceleration, which is the rate of change of the velocity of an object. They measure in meters per second squared (m/s2) or in G-forces (g). A single G-force for us here on planet Earth is equivalent to 9.8 m/s2, but this does vary slightly with elevation (and will be a different value on different planets due to variations in gravitational pull).
};

// Similarly, the defalt values of this list (Gscale)
// GFS_250DPS = 0, GFS_500DPS = 1, GFS_1000DPS = 2, GFS_2000DPS = 3
// scale range (These variables are used later in a switch/case way to obtain the resolution
// of the sensor accordingly)
enum Gscale {
  GFS_250DPS, // programmable scale range of +-250 DPS (Degrees per second)
  GFS_500DPS, // programmable scale range of +- 500 DPS (Degrees per second)
  GFS_1000DPS, // programmable scale range of +- 1000 DPS (Degrees per second)
  GFS_2000DPS // programmable scale range of +- 2000 DPS (Degrees per second)
};


// In this case, the default values of this list (Mscale)
// MFS_14BITS = 0, MFS_16BITS = 1
// 14 BIT (VS) 16 BIT (These variables are used later in a switch/case function to
// obtain the resolution of the sensor accordingly)
enum Mscale {
  MFS_14BITS,  // 14 bit resolution
  MFS_16BITS   // 16 bit resolution
};


class MPU9250{
    public
      uint8_t boardNumber; //MPU9250 Board Number
      uint8_t Ascale;    // AFS_2G, AFS_4G, AFS_8G, AFS_16G
      uint8_t Gscale;    // GFS_250DPS, GFS_500DPS, GFS_1000DPS, GFS_2000DPS
      uint8_t Mscale;    // MFS_14BITS or MFS_16BITS, 14-bit or 16-bit magnetometer resolution
      float aRes;
      float gRes;
      float mRes;


      //Bandwidth - This means the amount of times per second you can take a reliable acceleration //reading. For slow moving tilt sensing applications, a bandwidth of 50Hz will probably //suffice. If you intend to do vibration measurement, or control a fast moving machine, you //will want a bandwidth of several hundred Hz.

      //Sensitivity - Generally speaking, the more sensitivity the better. This means that for a //given change in acceleration, there will be a larger change in signal. Since larger signal //changes are easier to measure, you will get more accurate readings.

      // Sensitivity of a sensor is defined as the change in output of the
      // sensor per unit change in the parameter being measured.
      // volts/cm....volts/inches

    //  Sensitivity is an absolute quantity; resolution is a relative quantity. Sensitivity describes the smallest absolute amount of change that can be detected by a measurement, often expressed in terms of millivolts, microhms, or tenths of a degree. like in Gas chromotography one column can detect minimum1 nano gram level that is its sensitivity. Resolution describes the degree to which a change can be detected. It is expressed as a fraction of an amount to which one can easily relate. For example, printer manufacturers often describe resolution as dots per inch .

    //Accelerometer sensitivity
    // +/- 2, 4, 8 or 16 G
    // the values obtained here is the output data resolution in in g/LBS...which means
    // for every change by 1 bit...how much g change occur
    void getAres(){
      switch (Ascale)
      {
        // Possible accelerometer scales (and their register bit settings) are:
        // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
            // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
        case AFS_2G:
              // Since 16-bit ADCs are used..you have 2^16 possibilities.
              // There are two main ways of representing negative values (two's complement)
              // First trick is to say that the Most Significant BiT (MSB) decides the sign of the
              // value // In this case the Most Significant BiT (MSB) is for the sign (1--> Negative) and // (0 --> Positive).  (you divide half of the range which is 2g in the first case by the total Possible bit combinations - 1... which means 2^(16-1) = 2^15..so the 15 least significant bits hold the data and the most significant bit decides the signature )

              // Second trick is to just simply divide the full range by the total number of combinations (2^16). In the first case the total range of 2g range (2-(-2) = 4g)...divide that by 2^16 to get the resolution of the sensor.

              // range +- 2g (so 4g in total 2-(-2) = 4g)
              aRes = 2.0/32768.0;  //  aRes = 2.0 / 2^15 = 2.0/32768 -trick 1
              // or aRes = 4.0 / 2^16 = 4.0 / 65536 - trick 2
              break;
        case AFS_4G: // range +- 4g (so 8g in total 4-(-4) = 8g)
              aRes = 4.0/32768.0; // aRes = 4.0 / 2^(15) = 2.0/ 32768 -trick 1
              // or aRes = 8.0 / 2^16 = 8.0 / 65536 - trick 2
              break;
        case AFS_8G: // range +- 8g (so 16g in total 8-(-8) = 16g)
              aRes = 8.0/32768.0; // aRes = 8.0 / 2^(15) = 2.0/ 32768 -trick 1
              // or aRes = 16.0 / 2^16 = 16.0 / 65536 - trick 2
              break;
        case AFS_16G: // range +- 16g (so 32g in total 16-(-16) = 32g)
              aRes = 16.0/32768.0; // aRes = 16.0 /2^15= 16.0 / 32768 - trick 1
              // or aRes = 32.0 / 2^16 = 32.0 / 65536 - trick 2
              break;
      }
    }

    //Gyroscope sensitivity (DPS means Degree Per Second)
    // the values obtained here is the output data resolution in in dps/LBS...which means
    // for every change by 1 bit...how much degrees per second change occur
    void getGres(){
      switch (Gscale)
      {
        // Possible gyro scales (and their register bit settings) are:
        // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11).
            // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
        case GFS_250DPS:     // range +- 250dps (so 500 dps in total 250-(-250) = 500 dps)
              gRes = 250.0/32768.0; //  gRes = 250 / 2^15 = 250/32768 -trick 1
              // or gRes = 500.0 / 2^16 = 500 / 65536 - trick 2
              break;
        case GFS_500DPS:    // range +- 500dps (so 500 dps in total 500-(-500) = 1000 dps)
              gRes = 500.0/32768.0; //  gRes = 500.0 / 2^15 = 500.0/32768 -trick 1
              // or gRes = 1000.0 / 2^16 = 1000.0 / 65536 - trick 2
              break;
        case GFS_1000DPS:  // range +- 1000dps (so 1000 dps in total 1000-(-1000) = 2000dps)
              gRes = 1000.0/32768.0; //  aRes = 1000.0 / 2^15 = 1000.0/32768 -trick 1
              // or aRes = 2000.0 / 2^16 = 2000.0 / 65536 - trick 2
              break;
        case GFS_2000DPS:  // range +- 2000dps (so 2000dps in total 2000-(-2000) = 4000dps)
              gRes = 2000.0/32768.0; //  aRes = 2000.0 / 2^15 = 2000.0 /32768 -trick 1
              // or aRes = 4000.0 / 2^16 = 4000.0/ 65536 - trick 2
              break;
      }
    }

      // For the magnetometer there are two resolutions 14 bit and 16 bit when compared to
      // the accelerometer and gyroscope (which have 16 bits only)...but the magnetometer has
      // only one range (+- 4800 micro teslas).

      // The required resolution is in milliGauss....the conversion from micro teslas to
      // milliGauss is simply mulitplying the micro tesla value by 10.0

      //Magnetometer sensitivity ( 4800 / 2^ 13 ) micro tesla to milligaus .. multiply by 10
      // and  in the other case (4800 / 2^15)
      void getMres(){
        switch (Mscale)
        {
          // Possible magnetometer scales (and their register bit settings) are:
          // 14 bit resolution (0) and 16 bit resolution (1)
          case MFS_14BITS: // 14 bit
                // 14 bit 2^14 = 16394 (trick 1)
                // 16 bit 2^13 = 8192 (trick 1)
               mRes = 10.0*4800.0/8192.0; // Proper scale to return milliGauss
               // in this case trick 1 is utilised where by the MSB is the sign and the
               // remaining 13 bits hold the data...the full range is 4800
               // trick 2 -> 10* 9600 / 16384.0 where 9600 is the full range
               // (4800 - (-4800) = 9600 micro tesla)
                break;
          case MFS_16BITS: // 16 bit
                mRes = 10.0*4800.0/32768.0; // Proper scale to return milliGauss
                // in this case trick 1 is utilised where by the MSB is the sign and the
                // remaining 15 bits hold the data...the full range is 4800
                // 10 * 4800 / 2^15 = 10 * 4800 / 32768
                // trick 2 -> 10 * 9600 / 2^16  --> 10* 9600 / 65536.0 where 9600 is the full range (4800 - (-4800) = 9600 micro tesla)
               //
                break;
        }
      }

      // Function used to read the bytes of data defined earliers
      // ACCEL_XOUT_H, ACCEL_XOUT_L, etc
      void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest){
          char data[14];
          char data_write[1];
          data_write[0] = subAddress;
          // For the i2c you can simply write directly into the register of the
          // slave
          // For the i2c read...you first write followed by reading

          // write data on the slave
          // address it he 8-bit I2C slave address [ addr | 0 ]
          // The bottom bit of the address is forced to 0 to indicate a write.
          // So for example if the address of the sensor MPU9250 is
          // 0x69....in order write...you shfit this to the left by 1
          // 0x69 << 1 . once you shift the right most bit is 0 (indicating a right)
          // this bit is forced so that's why the 7bit address
          // is shifted to make sure that the address is not changed
          // when a 0 or 1 are forced

          // data_write
          // Pointer to the byte-array that you are going to read
          // (Address of the register that you are about to read from)

          // tHE FIRST 1 is the number of bytes to send
          // The second 1 indicates repeated start
          // when repeated start is 1, the master and slave still communicate

          i2c->write(address, data_write, 1, 1); // no stop

          // read data from the slave
          // address is the address of the slave
          // we already specified where are we going to read from
          // in the write function (data_write)
          // in the read function you specify where do you place this data
          // in
          // count -> number of bytes to read
          // 0 --> no repeated start
          i2c->read(address, data, count, 0);

          for(int ii = 0; ii < count; ii++) {
           dest[ii] = data[ii];
          }
      }

      void readAccelData(int16_t * destination){
        uint8_t rawData[6];  // x/y/z accel register data stored here
        readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
        destination[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
        destination[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
        destination[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
      }


      void readGyroData(int16_t * destination){
        uint8_t rawData[6];  // x/y/z gyro register data stored here
        readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
        destination[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
        destination[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
        destination[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
      }

      void readMagData(int16_t * destination){
        uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition
        if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
        //pc.printf("ready");
        readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
        uint8_t c = rawData[6]; // End data read by reading ST2 register
          if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
          destination[0] = (int16_t)(((int16_t)rawData[1] << 8) | rawData[0]);  // Turn the MSB and LSB into a signed 16-bit value
          destination[1] = (int16_t)(((int16_t)rawData[3] << 8) | rawData[2]) ;  // Data stored as little Endian
          destination[2] = (int16_t)(((int16_t)rawData[5] << 8) | rawData[4]) ;
         }
        }
        //pc.printf("out");
      }

      int16_t readTempData(){
        uint8_t rawData[2];  // x/y/z gyro register data stored here
        readBytes(MPU9250_ADDRESS, TEMP_OUT_H, 2, &rawData[0]);  // Read the two raw data registers sequentially into data array
        return (int16_t)(((int16_t)rawData[0]) << 8 | rawData[1]) ;  // Turn the MSB and LSB into a 16-bit value
      }






};
#endif // MPU9250_H
