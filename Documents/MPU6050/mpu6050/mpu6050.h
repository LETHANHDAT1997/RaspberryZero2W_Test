
#ifndef _MPU6050_H_
#define _MPU6050_H_
#include <stdio.h>
#include <stdint.h>

/*
    Đối với Raspberry nhớ enable I2C bằng lệnh sudo raspi-config
    Sau đó vào sudo nano /boot/firmware/config.txt -> thêm dòng dtparam=i2c_baudrate=400000
 */

#define MPU6050_ADDR 0x68 // thư viện sẽ tự dịch bit sang trái


#define MPU6050_SMPRT_DIV 0x19
#define MPU6050_WHO_AM_I 0x75
#define MPU6050_CONFIG 0x1A
#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_INT_PIN_CFG 0x37
#define MPU6050_INT_ENABLE 0x38
#define MPU6050_INT_STATUS 0x3A
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_GYRO_XOUT_H  0x43
#define MPU6050_PWR_MGMT_1 0x6B //most important



#define MPU6050_INT_PORT 	GPIOB
#define MPU6050_INT_PIN 	GPIO_PIN_5


typedef struct _MPU6050
{
	short acc_x_raw;
	short acc_y_raw;
	short acc_z_raw;
	short temperature_raw;
	short gyro_x_raw;
	short gyro_y_raw;
	short gyro_z_raw;

	float acc_x;
	float acc_y;
	float acc_z;
	float temperature;
	float gyro_x;
	float gyro_y;
	float gyro_z;
}Struct_MPU6050;

extern Struct_MPU6050 MPU6050;

void MPU6050_Writebyte(uint8_t reg_addr, uint8_t val);
void MPU6050_Writebytes(uint8_t reg_addr, uint8_t len, uint8_t* data);
void MPU6050_Readbyte(uint8_t reg_addr, uint8_t* data);
void MPU6050_Readbytes(uint8_t reg_addr, uint8_t len, uint8_t* data);
char MPU6050_Initialization(void);
void MPU6050_Get6AxisRawData(Struct_MPU6050* mpu6050);
int MPU6050_DataReady(void);
void MPU6050_Get_LSB_Sensitivity(uint8_t FS_SCALE_GYRO, uint8_t FS_SCALE_ACC);
void MPU6050_DataConvert(Struct_MPU6050* mpu6050);
void MPU6050_ProcessData(Struct_MPU6050* mpu6050);

void MPU6050_Init (void);
void MPU6050_Read_Accel (void);
void MPU6050_Read_Gyro (void);
void MPU6050_Read_All(void);



#endif /*_MPU6050_H_*/
