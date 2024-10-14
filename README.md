# BMP280_STM32
 
## What Is BMP280 Sensor?
The BMP280 is an absolute barometric pressure sensor, which is especially feasible for mobile applications. Its small dimensions and its low power consumption allow for the implementation in battery-powered devices such as mobile phones, GPS modules or watches. You can communicate with the library prepared with I2c communication in stm32 via any I2c method you want. I used the I2C1 path in this project


![image](https://github.com/user-attachments/assets/e9881a70-2f27-47c3-bb19-cd51510b0de4)

## How Do I Use This Library?
You need to create a sample instance of this structure defined in the .h file in your own project and enter the parameters. Each parameter is defined as a separate enum. You can learn the details by examining the .h file.
```c
typedef struct{

	OversamplingValues oversamplingT;	
	OversamplingValues oversamplingP; 
	power_mode mode; 				 
	filter_coefficient filter; 		
	uint8_t spiEn; 					
	t_sb tstandby;			
	BMP280_MEASURE_MODE modeMeasure;
	I2C_HandleTypeDef* hi2cX;

}bmp280_parameters;
```

For example, this enum includes the modes of the measured sensor. Depending on the selected parameter, only temperature or only pressure can be measured. If you think it will affect the performance or if you do not need all the data, you can act according to the option.

```c
typedef enum{

	ONLY_TEMPERATURE = 1,
	ONLY_PRESSURE = 2, 	
	BOTH = 3,

}BMP280_MEASURE_MODE;
```


With this function, measurement is carried out as we wish.

```c
void CalculationStart(float* t,float* p, bmp280_parameters* params);
```
## For Example
We choose our I2c path


```c
I2C_HandleTypeDef hi2c1;
```

Variables that obtain values ​​are defined

```c
float temp, pres;
```

In the example given, the parameters are standard, you can use them directly, if you want to use them in other settings, you can browse the .h file or datasheet.

```c
	bmp280_parameters bmp_params;
	bmp_params.hi2cX = &hi2c1;
	bmp_params.oversamplingT = OSRS_16;
	bmp_params.oversamplingP = OSRS_16;
	bmp_params.mode = normal_mode;
	bmp_params.tstandby = t_sb4;
	bmp_params.filter = fc4;
	bmp_params.spiEn = 0x00;
	bmp_params.modeMeasure = BOTH;
```

Finally, we start the reading process in an infinite loop.

```c
 CalculationStart(&temp, &pres, &bmp_params);
 HAL_Delay(200);
```


```c
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef hlpuart1;

/* USER CODE BEGIN PV */
float temp, pres;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	bmp280_parameters bmp_params;
	bmp_params.hi2cX = &hi2c1;
	bmp_params.oversamplingT = OSRS_16;
	bmp_params.oversamplingP = OSRS_16;
	bmp_params.mode = normal_mode;
	bmp_params.tstandby = t_sb4;
	bmp_params.filter = fc4;
	bmp_params.spiEn = 0x00;
	bmp_params.modeMeasure = BOTH;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*	/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  BMP280_Init(&bmp_params);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  CalculationStart(&temp, &pres, &bmp_params);
	  HAL_Delay(200);
  }
  /* USER CODE END 3 */
}
```
