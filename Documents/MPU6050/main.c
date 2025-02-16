#include <stdio.h>
#include <stdint.h>
#include <pigpio.h>
#include <unistd.h> // Để sử dụng sleep
#include "mpu6050.h"
// float Ax, Ay, Az, Gx, Gy, Gz;
int main(void)
{
    // Khởi tạo pigpio
    if (gpioInitialise() < 0) 
    {
        printf("Không thể khởi tạo pigpio\n");
        return 1;
    }

	// MPU6050_Initialization();
	// while (1)
	// {

	// 	if(MPU6050_DataReady() == 1)
	// 	{
	// 		MPU6050_ProcessData(&MPU6050);
	// 		printf("ACC_X %f, ACC_Y %f, ACC_Z %f\n", MPU6050.acc_x_raw, MPU6050.acc_y_raw, MPU6050.acc_z_raw);
	// 	}
	// }

	MPU6050_Init();
	while (1)
  	{

		// read the Accelerometer and Gyro values
		//   MPU6050_Read_Accel();
		//   MPU6050_Read_Gyro();
		MPU6050_Read_All();

	  	// sleep(1);  // wait for a while
  	}

}







