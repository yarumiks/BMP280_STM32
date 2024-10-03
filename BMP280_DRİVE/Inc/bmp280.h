/*
 * bmp280.h
 *
 *  Created on: Sep 30, 2024
 *      Author: yasar k
 */
#ifndef BMP280_DRİVE_INC_BMP280_H_
#define BMP280_DRİVE_INC_BMP280_H_
#include <stdint.h>
#include "stm32g4xx_hal.h"

//DEVİCE ADDRESS DEFİNİTİONS
//====================================================
#define BMP280_DEVICE_ADDR 0x76 //SDO PIN CONNECTED TO GND
#define BMP280_READ_ADDR 0xED
#define BMP280_WRITE_ADDR 0xEC


#define BMP280_ID 0xD0
#define CHIP_ID 0x58
#define BMP280_RESET 0xE0
#define RESET_VALUE 0xB6
#define BMP280_STATUS 0xF3
#define STATUS_CONV 0x08
#define STATUS_COPY 0x01

#define BMP280_GET_DATA 0xF4
#define BMP280_CONFIG 0xF5

#define T_OFFSET 0x05
#define P_OFFSET 0x02

#define READ_DATA_START 0xF7
#define READ_DATA_LENGTH 6

#define CALIBRATION_DATA_ADDR 0x88


typedef enum {
    OSRS_SKIPPED = 0x00,  // 0b0000
    OSRS_16      = 0x01,  // 0b0001
    OSRS_17      = 0x02,  // 0b0010
    OSRS_18      = 0x03,  // 0b0011
    OSRS_19      = 0x04,  // 0b0100
    OSRS_20      = 0x05   // 0b0101
} OversamplingValues;


/*
 * The operating modes of bmp280 are generally normal_mode,
 * which is used to receive continuous instantaneous data.
 */
typedef enum {

	 sleep_mode = 0x00,
	 forced_mode = 0x01,
	 normal_mode = 0x03

}power_mode;


typedef enum {

	 fc2 = 0x02,
	 fc4 = 0x04,
	 fc8 = 0x08,
	 fc16 = 0x10

}filter_coefficient;


typedef enum{

	t_sb0 = 0x00,  //Tstandby = 0.5 ms
	t_sb1 = 0x01, //Tstandby = 62.5 ms
	t_sb2 = 0x02,  //Tstandby = 125 ms
	t_sb3 = 0x03,  //Tstandby = 250 ms
	t_sb4 = 0x04,  //Tstandby = 500 ms
	t_sb5 = 0x05,  //Tstandby = 1000 ms
	t_sb6 = 0x06,  //Tstandby = 2000 ms
	t_sb7 = 0x07,  //Tstandby = 4000 ms

}t_sb;

typedef enum{

	ONLY_TEMPERATURE = 1, //This mode is only for reading temperature data
	ONLY_PRESSURE = 2, 	 //This mode is only for reading pressure data
	BOTH = 3, 			//This mode is reads both temperature and pressure data simultaneously

}BMP280_MEASURE_MODE;


typedef struct{

	OversamplingValues oversamplingT;	//This mode default to assign is OSRS_16
	OversamplingValues oversamplingP;  	//This mode default to assign is OSRS_16
	power_mode mode; 				  	//This mode default to assign is normal_mode
	filter_coefficient filter; 		 	//The appropriate filter coefficient should be selected to reduce environmental and hardware noise.
	uint8_t spiEn; 						//If you are going to use I2c, you need to assign this part to 0x00.
	t_sb tstandby;						//It is a parameter that determines how long to wait between measurements in standby mode.
	BMP280_MEASURE_MODE modeMeasure;	//The user must select the mode as desired, basically "BOTH" option must be selected.

	I2C_HandleTypeDef* hi2cX;

}bmp280_parameters;


uint8_t BMP280_ReadRegister(bmp280_parameters* params,uint8_t dataAddr);
void BMP280_WriteRegister(bmp280_parameters* params,uint8_t dataAddr,uint8_t data);
void BMP280_RawDataRead(bmp280_parameters* params);
void bmp280_getTemprature(void);
void bmp280_getPressure(void);
void BMP280_Init(bmp280_parameters* params);
void BMP280_Calibration(bmp280_parameters* params);
void CalculationStart(float* t,float* p, bmp280_parameters* params);
#endif /* BMP280_DRİVE_INC_BMP280_H_ */
