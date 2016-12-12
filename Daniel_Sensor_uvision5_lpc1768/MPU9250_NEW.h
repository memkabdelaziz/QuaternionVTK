// Include guards
#ifndef MPU9250_H
#define MPU9250_H

// Pre-processor directives
// standard header files
#include<stdio.h>
#include<time.h>
#include<cmath.h>

using namespace std;

// MPU9250 address includes the accelerometer, gyroscope and temperature sensor
// AK8963 address includes only the Magnetometer

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
// Data ready status
#define AK8963_ST1       0x02  // data ready status bit 0
// Magnetometer x-axis data
#define AK8963_XOUT_L    0x03  // low byte of X-axis Magnetometer data
#define AK8963_XOUT_H    0x04  // High byte of X-axis Magnetometer data
// Magnetometer y-axis data
#define AK8963_YOUT_L    0x05  // Low byte of Y-axis Magnetometer data
#define AK8963_YOUT_H    0x06  // High byte of Y-axis Magnetometer data
// Magnetometer z-axis data
#define AK8963_ZOUT_L    0x07  // Low byte of Z-axis Magnetometer data
#define AK8963_ZOUT_H    0x08  // High byte of Z-axis Magnetometer data

//In single measurement mode, continuous measurement mode, external trigger measurement mode and
//self-test mode, magnetic sensor may overflow even though measurement data regiseter is not saturated. In this case, measurement data is not correct and HOFL bit turns to “1”. When next measurement stars, it returns to “0”
#define AK8963_ST2       0x09  // Data overflow bit 3 and data read error status bit 2

// Address of the Magnetometer
#define AK8963_ADDRESS   0x0C<<1

// AK8963 Initialization
#define AK8963_CNTL      0x0A  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0

// MPU9250 Initialization
#define PWR_MGMT_1       0x6B // Device defaults to the SLEEP mode
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define ACCEL_CONFIG2    0x1D
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define SMPLRT_DIV       0x19

// Accelerometer scale ranges (+-2g, +-4g, +-8g, +- 16g)
// g = 9.81 m/s^2
enum Ascale {
  AFS_2G, // programmable scale range of +- 2g
  AFS_4G, // programmable scale range of +- 4g
  AFS_8G, // programmable scale range of +- 8g
  AFS_16G // programmable scale range of +- 16g
};

// Gyroscope scale ranges (+-250DPS, +-500DPS, +- 1000DPS, +- 2000DPS)
// DPS --> Degrees Per Second
enum Gscale {
  GFS_250DPS, // programmable scale range of +-250 DPS (Degrees per second)
  GFS_500DPS, // programmable scale range of +- 500 DPS (Degrees per second)
  GFS_1000DPS, // programmable scale range of +- 1000 DPS (Degrees per second)
  GFS_2000DPS // programmable scale range of +- 2000 DPS (Degrees per second)
};

// Magnetometer 16 bit and 14 bit
enum Mscale {
  MFS_14BITS,  // 14 bit resolution
  MFS_16BITS   // 16 bit resolution
};


class MPU9250{
  public
  uint8_t boardNumber; //MPU9250 Board Number

  // Constants needed to calculate the accelerometer, gyroscope and
  // magnetometer resolution
  uint8_t Ascale;    // Accelerometer scale ranges (+-2g, +-4g, +-8g, +-16g)
  uint8_t Gscale;    // Gyroscope scale ranges (+-250DPS, +-500DPS, +-1000DPS, +-2000DPS)
  uint8_t Mscale;    // 14-bit (vs) 16-bit Magnetometer resolution

  // Resolution Values (Obtained using the get functions getAres, getGres
  // and getMres)
  float aRes;        // Accelerometer resolution
  float gRes;        // Gyroscope resolution
  float mRes;        // Magnetometer resolution

  // Accelerometer, Gyroscope and Magnetometer data stored
  int16_t accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
  int16_t gyroCount[3];   // Stores the 16-bit signed gyro sensor output
  int16_t magCount[3];    // Stores the 16-bit signed magnetometer sensor output


  /***********************************************************************************/
  /**********************Resolution Calculation of Sensors****************************/
  /***********************************************************************************/

  // Get accelerometer resolution (g/LSB)
  void getAres(){
    switch (Ascale){
      case AFS_2G: // (+-2g)
      aRes = 2.0/32768.0;
      // Method 1 --> aRes = 2.0 / 2^15 = 2.0/32768 (implemented)
      // Method 2 --> aRes = 4.0 / 2^16 = 4.0 / 65536
      break;
      case AFS_4G: // (+-4g)
      aRes = 4.0/32768.0;
      // Method 1 --> aRes = 4.0 / 2^(15) = 4.0/ 32768 (implemented)
      // Method 2 --> aRes = 8.0 / 2^16 = 8.0 / 65536
      break;
      case AFS_8G: // (+-8g)
      aRes = 8.0/32768.0;
      // Method 1 --> aRes = 8.0 / 2^(15) = 8.0/ 32768 (implemented)
      // Method 2 --> aRes = 16.0 / 2^16 = 16.0 / 65536
      break;
      case AFS_16G: // (+-16g)
      aRes = 16.0/32768.0;
      // Method 1 --> aRes = 16.0 /2^15= 16.0 / 32768 (implemented)
      // Method 2 --> aRes = 32.0 / 2^16 = 32.0 / 65536
      break;
    }
  }

  // Get gyroscope resolution (DPS/LSB)
  void getGres(){
    switch (Gscale)
    {
      case GFS_250DPS:  // (+-250DPS)
      gRes = 250.0/32768.0;
      // Method 1 --> gRes = 250 / 2^15 = 250/32768 (implemented)
      // Method 2 --> gRes = 500.0 / 2^16 = 500 / 65536
      break;
      case GFS_500DPS:  // (+-500DPS)
      gRes = 500.0/32768.0;
      //  Method 1 --> gRes = 500.0 / 2^15 = 500.0/32768 (implemented)
      //  Method 2 --> gRes = 1000.0 / 2^16 = 1000.0 / 65536
      break;
      case GFS_1000DPS: // (+-1000DPS)
      gRes = 1000.0/32768.0;
      //  Method 1 --> aRes = 1000.0 / 2^15 = 1000.0/32768 (implemented)
      //  Method 2 --> aRes = 2000.0 / 2^16 = 2000.0 / 65536
      break;
      case GFS_2000DPS: // (+-2000DPS)
      gRes = 2000.0/32768.0;
      // Method 1 --> aRes = 2000.0 / 2^15 = 2000.0 /32768 (implemented)
      // Method 2 --> aRes = 4000.0 / 2^16 = 4000.0/ 65536
      break;
    }
  }

  // Get magnetometer resolution (milliGauss/LSB)
  void getMres(){
    switch (Mscale)
    {
      case MFS_14BITS: // 14 bit
      mRes = 10.0*(4800.0/8192.0);
      // Method 1 --> mRes = 4800 / 2^13 = 4800/8192 (implemented)
      // Method 2 --> mRes = (4800-(-4800)) / 2^14 = 9600 / 16394
      // For both methods (micro teslas to milliGauss) = multiply the
      // value by 10
      break;
      case MFS_16BITS: // 16 bit
      mRes = 10.0*(4800.0/32768.0);
      // Method 1 --> mRes = 4800 / 2^15 = 4800/32768 (implemented)
      // Method 2 --> mRes = (4800-(-4800)) / 2^16 = 9600 / 65536
      // For both methods (micro teslas to milliGauss) = multiply the
      // value by 10
      break;
    }
  }


  /***********************************************************************************/
  /**********************Read and Write bytes helper functions************************/
  /***********************************************************************************/

  // Write data to the register (1 byte) of the slave (I2C)
  void writeByte(uint8_t address, uint8_t subAddress, uint8_t data){
    char data_write[2];
    data_write[0] = subAddress; // Address of byte to write into
    data_write[1] = data; // data to be written into the byte
    i2c->write(address, data_write, 2, 0);
  }

  // Read data form a register (1 byte) of the slave (I2C)
  char readByte(uint8_t address, uint8_t subAddress){
    char data[1]; // `data` will store the register data
    char data_write[1];
    data_write[0] = subAddress;
    i2c->write(address, data_write, 1, 1); // no stop
    i2c->read(address, data, 1, 0);
    return data[0];
  }

  // Read data from registers (count) of the slave (I2C)
  void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest){
    char data[14];
    char data_write[1];
    data_write[0] = subAddress;
    i2c->write(address, data_write, 1, 1); // no stop
    i2c->read(address, data, count, 0);
    for(int ii = 0; ii < count; ii++) {
      dest[ii] = data[ii];
    }
  }

  /***********************************************************************************/
  /**Read Data Functions From accelerometer, gyroscope, magnetometer and temp sensor**/
  /***********************************************************************************/

  // Read data from the accelerometer register data (x,y and z) utilising the
  // readBytes function
  void readAccelData(int16_t * destination){
    uint8_t rawData[6];  // x/y/z accel register data stored here
    readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
    destination[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
    destination[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
    destination[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }

  // Read data from the gyroscope register data (x,y and z) utilising the
  // readBytes function
  void readGyroData(int16_t * destination){
    uint8_t rawData[6];  // x/y/z gyro register data stored here
    readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
    destination[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
    destination[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
    destination[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }

  // Read data from the magnetometer register data (x,y and z) utilising the
  // readByte and readBytes function
  void readMagData(int16_t * destination){
    uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition

    // & is a bitwise and operation....so in order to check whether the status is 1...it performs a bitwise AND operation ...so if it the status is 0...0 anded with 1 is simply zero...if the
    // status is 1 ....1 anded with 1 is 1.

    if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
      //pc.printf("ready");
      readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
      uint8_t c = rawData[6]; // End data read by reading ST2 register
      // bit wise and as well to check if the status 2 (bit number 3) is 1 (which means it's overflow or not). If yes, then don't read...until it's 0.
      if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
        destination[0] = (int16_t)(((int16_t)rawData[1] << 8) | rawData[0]);  // Turn the MSB and LSB into a signed 16-bit value
        destination[1] = (int16_t)(((int16_t)rawData[3] << 8) | rawData[2]) ;  // Data stored as little Endian
        destination[2] = (int16_t)(((int16_t)rawData[5] << 8) | rawData[4]) ;
      }
    }
  }

  // Read data from the temperature sensor register data, also utilising the
  // readBytes function
  int16_t readTempData(){
    uint8_t rawData[2];  // x/y/z gyro register data stored here
    readBytes(MPU9250_ADDRESS, TEMP_OUT_H, 2, &rawData[0]);  // Read the two raw data registers sequentially into data array
    return (int16_t)(((int16_t)rawData[0]) << 8 | rawData[1]) ;  // Turn the MSB and LSB into a 16-bit value
  }

  /***********************************************************************************/
  /**********************Reset, Initialize and Calibrate MPU9250**********************/
  /***********************************************************************************/

  // Reset MPU9250
  void resetMPU9250(){
    // reset device
    writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
    wait(0.1);
    }

  // Initialize mpu9250
  void initMPU9250(){
    // Initialize MPU9250 device
    // wake up device
    writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
    wait(0.1); // Delay 100 ms for PLL to get established on x-axis gyro; should check for PLL ready interrupt

    // get stable time source
    writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001

    // Configure Gyro and Accelerometer
    // Disable FSYNC and set accelerometer and gyro bandwidth to 44 and 42 Hz, respectively;
    // DLPF_CFG = bits 2:0 = 010; this sets the sample rate at 1 kHz for both
    // Maximum delay is 4.9 ms which is just over a 200 Hz maximum rate
    writeByte(MPU9250_ADDRESS, CONFIG, 0x03);

    // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
    writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x04);  // Use a 200 Hz rate; the same rate set in CONFIG above


    // Set gyroscope full scale range
    // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
    uint8_t c =  readByte(MPU9250_ADDRESS, GYRO_CONFIG);
    writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c & ~0xE0); // Clear self-test bits [7:5]
    writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
    writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c | Gscale << 3); // Set full scale range for the gyro


    // Set accelerometer configuration
    c =  readByte(MPU9250_ADDRESS, ACCEL_CONFIG);
    writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c & ~0xE0); // Clear self-test bits [7:5]
    writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
    writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c | Ascale << 3); // Set full scale range for the accelerometer



    // Set accelerometer sample rate configuration
    // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
    // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
    c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG2);
    writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c & ~0x0F); // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
    writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c | 0x03); // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz

    // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
    // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

    // Configure Interrupts and Bypass Enable
    // Set interrupt pin active high, push-pull, and clear on read of INT_STATUS, enable I2C_BYPASS_EN so additional chips
    // can join the I2C bus and all can be controlled by the Arduino as master
    writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
    writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
  }

  // calibrate MPU9250
  void calibrateMPU9250(float * dest1, float * dest2){
    uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
    uint16_t ii, packet_count, fifo_count;
    int32_t gyro_bias[3] = {0, 0, 0}, accel_bias[3] = {0, 0, 0};

    // reset device, reset all registers, clear gyro and accelerometer bias registers
    writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
    wait(0.1);

    // get stable time source
    // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
    writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
    writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
    wait(0.2);

    // Configure device for bias calculation
    writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);   // Disable all interrupts
    writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);      // Disable FIFO
    writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);   // Turn on internal clock source
    writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
    writeByte(MPU9250_ADDRESS, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
    writeByte(MPU9250_ADDRESS, USER_CTRL, 0x0C);    // Reset FIFO and DMP
    wait(0.015);

    // Configure MPU9250 gyro and accelerometer for bias calculation
    writeByte(MPU9250_ADDRESS, CONFIG, 0x01);      // Set low-pass filter to 188 Hz
    writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
    writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
    writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity

    uint16_t  gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
    uint16_t  accelsensitivity = 16384;  // = 16384 LSB/g

    // Configure FIFO to capture accelerometer and gyro data for bias calculation
    writeByte(MPU9250_ADDRESS, USER_CTRL, 0x40);   // Enable FIFO
    writeByte(MPU9250_ADDRESS, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO (max size 512 bytes in MPU-9250)
    wait(0.04); // accumulate 40 samples in 80 milliseconds = 480 bytes

    // At end of sample accumulation, turn off FIFO sensor read
    writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
    readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
    fifo_count = ((uint16_t)data[0] << 8) | data[1];
    packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging

    for (ii = 0; ii < packet_count; ii++) {
      int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
      readBytes(MPU9250_ADDRESS, FIFO_R_W, 12, &data[0]); // read data for averaging
      accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  ) ;  // Form signed 16-bit integer for each sample in FIFO
      accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  ) ;
      accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  ) ;
      gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
      gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
      gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;

      accel_bias[0] += (int32_t) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
      accel_bias[1] += (int32_t) accel_temp[1];
      accel_bias[2] += (int32_t) accel_temp[2];
      gyro_bias[0]  += (int32_t) gyro_temp[0];
      gyro_bias[1]  += (int32_t) gyro_temp[1];
      gyro_bias[2]  += (int32_t) gyro_temp[2];

    }
    accel_bias[0] /= (int32_t) packet_count; // Normalize sums to get average count biases
    accel_bias[1] /= (int32_t) packet_count;
    accel_bias[2] /= (int32_t) packet_count;
    gyro_bias[0]  /= (int32_t) packet_count;
    gyro_bias[1]  /= (int32_t) packet_count;
    gyro_bias[2]  /= (int32_t) packet_count;

    if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis accelerometer bias calculation
    else {accel_bias[2] += (int32_t) accelsensitivity;}

    // Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
    data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
    data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
    data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
    data[3] = (-gyro_bias[1]/4)       & 0xFF;
    data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
    data[5] = (-gyro_bias[2]/4)       & 0xFF;

    /// Push gyro biases to hardware registers
    /*  writeByte(MPU9250_ADDRESS, XG_OFFSET_H, data[0]);
    writeByte(MPU9250_ADDRESS, XG_OFFSET_L, data[1]);
    writeByte(MPU9250_ADDRESS, YG_OFFSET_H, data[2]);
    writeByte(MPU9250_ADDRESS, YG_OFFSET_L, data[3]);
    writeByte(MPU9250_ADDRESS, ZG_OFFSET_H, data[4]);
    writeByte(MPU9250_ADDRESS, ZG_OFFSET_L, data[5]);
    */
    dest1[0] = (float) gyro_bias[0]/(float) gyrosensitivity; // construct gyro bias in deg/s for later manual subtraction
    dest1[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
    dest1[2] = (float) gyro_bias[2]/(float) gyrosensitivity;

    // Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
    // factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
    // non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
    // compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
    // the accelerometer biases calculated above must be divided by 8.

    int32_t accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
    readBytes(MPU9250_ADDRESS, XA_OFFSET_H, 2, &data[0]); // Read factory accelerometer trim values
    accel_bias_reg[0] = (int16_t) ((int16_t)data[0] << 8) | data[1];
    readBytes(MPU9250_ADDRESS, YA_OFFSET_H, 2, &data[0]);
    accel_bias_reg[1] = (int16_t) ((int16_t)data[0] << 8) | data[1];
    readBytes(MPU9250_ADDRESS, ZA_OFFSET_H, 2, &data[0]);
    accel_bias_reg[2] = (int16_t) ((int16_t)data[0] << 8) | data[1];

    uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
    uint8_t mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis

    for(ii = 0; ii < 3; ii++) {
      if(accel_bias_reg[ii] & mask) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
    }

    // Construct total accelerometer bias, including calculated average accelerometer bias from above
    accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
    accel_bias_reg[1] -= (accel_bias[1]/8);
    accel_bias_reg[2] -= (accel_bias[2]/8);

    data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
    data[1] = (accel_bias_reg[0])      & 0xFF;
    data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
    data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
    data[3] = (accel_bias_reg[1])      & 0xFF;
    data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
    data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
    data[5] = (accel_bias_reg[2])      & 0xFF;
    data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

    // Apparently this is not working for the acceleration biases in the MPU-9250
    // Are we handling the temperature correction bit properly?
    // Push accelerometer biases to hardware registers
    /*  writeByte(MPU9250_ADDRESS, XA_OFFSET_H, data[0]);
    writeByte(MPU9250_ADDRESS, XA_OFFSET_L, data[1]);
    writeByte(MPU9250_ADDRESS, YA_OFFSET_H, data[2]);
    writeByte(MPU9250_ADDRESS, YA_OFFSET_L, data[3]);
    writeByte(MPU9250_ADDRESS, ZA_OFFSET_H, data[4]);
    writeByte(MPU9250_ADDRESS, ZA_OFFSET_L, data[5]);
    */
    // Output scaled accelerometer biases for manual subtraction in the main program
    dest2[0] = (float)accel_bias[0]/(float)accelsensitivity;
    dest2[1] = (float)accel_bias[1]/(float)accelsensitivity;
    dest2[2] = (float)accel_bias[2]/(float)accelsensitivity;
  }

  /***********************************************************************************/
  /***************************** Initialize AK8963************************************/
  /***********************************************************************************/

  // Initialize AK8963
  void initAK8963(float * destination){
    // First extract the factory calibration for each magnetometer axis
    uint8_t rawData[3];  // x/y/z gyro calibration data stored here
    writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
    wait(0.01);
    writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
    wait(0.01);
    readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values
    destination[0] =  (float)(rawData[0] - 128)/256.0f + 1.0f;   // Return x-axis sensitivity adjustment values, etc.
    destination[1] =  (float)(rawData[1] - 128)/256.0f + 1.0f;
    destination[2] =  (float)(rawData[2] - 128)/256.0f + 1.0f;
    writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
    wait(0.01);
    // Configure the magnetometer for continuous read and highest resolution
    // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
    // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
    writeByte(AK8963_ADDRESS, AK8963_CNTL, Mscale << 4 | Mmode); // Set magnetometer data resolution and sample ODR
    wait(0.01);
  }



};
#endif // MPU9250_H
