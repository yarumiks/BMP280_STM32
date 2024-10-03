/*
 * bmp280.c
 *
 *  Created on: Sep 30, 2024
 *      Author: yasar k
 */


#include "bmp280.h"

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;

//Raw Datas
double temperatureRaw;
double PressureRaw;
float temperature, pressure;

//Calculation Datas
double tvar1,tvar2,t_fine,T;
double pvar1, pvar2, p;

uint8_t BMP280_ReadRegister(bmp280_parameters* params,uint8_t dataAddr){
	uint8_t readData;
	HAL_I2C_Mem_Read(params->hi2cX, BMP280_READ_ADDR, dataAddr, 1, &readData, 1, 100);
	return readData;
};

void BMP280_WriteRegister(bmp280_parameters* params,uint8_t dataAddr,uint8_t data){
	HAL_I2C_Mem_Write(params->hi2cX, BMP280_READ_ADDR, dataAddr, 1, &data, 1, 100);
}
void BMP280_Calibration(bmp280_parameters* params){
	uint8_t calibrationData[24] = {0};
	HAL_I2C_Mem_Read(params->hi2cX, BMP280_READ_ADDR, CALIBRATION_DATA_ADDR, 1, calibrationData, 24, 1000);

	dig_T1 = (calibrationData[1] << 8 | calibrationData[0]);
	dig_T2 = (calibrationData[3] << 8 | calibrationData[2]);
	dig_T3 = (calibrationData[5] << 8 | calibrationData[4]);
	dig_P1 = (calibrationData[7] << 8 | calibrationData[6]);
	dig_P2 = (calibrationData[9] << 8 | calibrationData[8]);
	dig_P3 = (calibrationData[11] << 8 | calibrationData[10]);
	dig_P4 = (calibrationData[13] << 8 | calibrationData[12]);
	dig_P5 = (calibrationData[15] << 8 | calibrationData[14]);
	dig_P6 = (calibrationData[17] << 8 | calibrationData[16]);
	dig_P7 = (calibrationData[19] << 8 | calibrationData[18]);
	dig_P8 = (calibrationData[21] << 8 | calibrationData[20]);
	dig_P9 = (calibrationData[23] << 8 | calibrationData[22]);
}


void bmp280_getTemprature(void){

	tvar1 = (((double)temperatureRaw /16384.0) - ((double)dig_T1/1024.0))*(double)dig_T2;
	tvar2 = ((((double)temperatureRaw /131072.0) - ((double)dig_T1/8192.0))* ((double)temperatureRaw/131072.0) - (double)dig_T1/8192.0) * (double)dig_T3;
	t_fine = (tvar1 + tvar2);
	T = (tvar1 + tvar2) / 5120.0;

	temperature =T;
}

void bmp280_getPressure(void){

	pvar1 = ((double)t_fine/2.0) - 64000.0;
	pvar2 = pvar1 * pvar1 * ((double)dig_P6) /32768.0;
	pvar2 = pvar2 + pvar1 * ((double)dig_P5) *2.0;
	pvar2 = (pvar2/4.0)+ (((double)dig_P4) * 65536.0);
	pvar1 = (((double)dig_P3) * pvar1 * pvar1/524288.0 + ((double)dig_P2) * pvar1) / 524288.0;
	pvar1 = (1.0 + pvar1 / 32768.0)*((double)dig_P1);
	p = 1048576.0 - (double)PressureRaw;
	p = (p - (pvar2/4096.0)) * 62500.0 / pvar1;
	pvar1 = ((double)dig_P9) * p * p /2147483648.0;
	pvar2 = p * ((double)dig_P8)/32768.0;
	p = p + (pvar1 + pvar2 + ((double)dig_P7)) / 16.0;

	pressure = p;
}

void BMP280_RawDataRead(bmp280_parameters* params){
	uint8_t rawData[6] = {0};

	HAL_I2C_Mem_Read(params->hi2cX, BMP280_READ_ADDR, READ_DATA_START, 1, rawData, 6, 100);

	temperatureRaw = ((rawData[3] << 12) | (rawData[4] << 8) | (rawData[5] >> 4));
	PressureRaw =   ((rawData[0] << 12) | (rawData[1] << 8) | (rawData[2] >> 4));;
}

void BMP280_Init(bmp280_parameters* params)
{
	 uint8_t ctrl_meas = (params->oversamplingT << T_OFFSET) | (params->oversamplingP << P_OFFSET) | params->mode;
	 uint8_t config = (params->tstandby << T_OFFSET) | (params->filter << P_OFFSET) | params->spiEn;

	BMP280_WriteRegister(params,BMP280_GET_DATA, ctrl_meas);
	BMP280_WriteRegister(params,BMP280_CONFIG, config);
	BMP280_Calibration(params);
}


void CalculationStart(float* t,float* p, bmp280_parameters* params){
	BMP280_RawDataRead(params);

	if(params->modeMeasure == ONLY_TEMPERATURE || params->modeMeasure  == BOTH){
		bmp280_getTemprature();
		*t = temperature;
	}
	if (params->modeMeasure  == ONLY_PRESSURE || params->modeMeasure  == BOTH){
		bmp280_getPressure();
		*p = pressure;
	}
}
