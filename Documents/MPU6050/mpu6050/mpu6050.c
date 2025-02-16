#include "mpu6050.h"
#include <pigpio.h>
#include <unistd.h> // Để sử dụng sleep
#include <math.h>

#define RAD_TO_DEG (180.0 / M_PI)
// Tham số của Complementary Filter
#define ALPHA 0.97

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

float Ax, Ay, Az, Gx, Gy, Gz;

Struct_MPU6050 MPU6050;

static float LSB_Sensitivity_ACC;
static float LSB_Sensitivity_GYRO;
static int handle;

void HAL_Delay(int delay)
{
    usleep(delay*1000);
}

void MPU6050_Writebyte(uint8_t reg_addr, uint8_t val)
{
	// HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &val, 1, 1);
    if (i2cWriteByteData(handle, reg_addr, val) < 0) 
    {
        printf("Không thể ghi dữ liệu vào thiết bị I2C\n");
    } else 
    {
        // printf("Ghi thành công: Thanh ghi 0x%02X, Giá trị 0x%02X\n", reg_addr, val);
    }
}

// void MPU6050_Writebytes(uint8_t reg_addr, uint8_t len, uint8_t* data)
// {
// 	// Với MPU6050, bạn cần gửi lệnh ghi để chỉ định thanh ghi bắt đầu trước khi đọc
//     int result = i2cWriteByte(handle, reg_addr); 
//     // Ghi mảng byte vào thiết bị I2C
//     result = i2cWriteDevice(handle, data, len);
//     if (result < 0) 
//     {
//         printf("Ghi dữ liệu thất bại\n");
//     } else 
//     {
//         // printf("Ghi dữ liệu thành công\n");
//     }
// }

void MPU6050_Readbyte(uint8_t reg_addr, uint8_t* data)
{
	// HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, 1, 1);
    // Đọc dữ liệu từ thiết bị I2C (ví dụ: đọc từ thanh ghi 0x01)
    *data = i2cReadByteData(handle, reg_addr);
    if (*data < 0) 
    {
        printf("Không thể đọc dữ liệu từ thiết bị I2C\n");
    } else 
    {
        // printf("Đọc thành công: Thanh ghi 0x%02X, Giá trị 0x%02X\n", reg_addr, *data);
    }
}

void MPU6050_Readbytes(uint8_t reg_addr, uint8_t len, uint8_t* data)
{
    // Với MPU6050, bạn cần gửi lệnh ghi để chỉ định thanh ghi bắt đầu trước khi đọc
    int result = i2cWriteByte(handle, reg_addr); 
    // Đọc nhiều byte từ thiết bị
    result = i2cReadDevice(handle, data, len);
    if (result < 0) 
    {
        printf("Đọc dữ liệu thất bại\n");
    } else 
    {
        // printf("Dữ liệu đọc: ");
        // for (int i = 0; i < len; i++) 
        // {
        //     printf("0x%X ", data[i]);
        // }
        // printf("\n");
    }
}

char MPU6050_Initialization(void)
{
	HAL_Delay(50);
	uint8_t who_am_i = 0;
	printf("Checking MPU6050...\n");
    
    // Mở kênh I2C (bus 1, địa chỉ 0x40)
    handle = i2cOpen(1, MPU6050_ADDR, 0);
    if (handle < 0) 
    {
        printf("Không thể mở kênh I2C\n");
        gpioTerminate();
        return 1;
    }

	MPU6050_Readbyte(MPU6050_WHO_AM_I, &who_am_i);
	if(who_am_i == 0x68)
	{
		printf("MPU6050 who_am_i = 0x%02x...OK\n", who_am_i);
	}
	else
	{
		printf("ERROR!\n");
		printf("MPU6050 who_am_i : 0x%02x should be 0x68\n", who_am_i);
		while(1)
		{
			printf("who am i error. Can not recognize mpu6050\n");
			HAL_Delay(100);
		}
	}

	//Reset the whole module before initialization
	MPU6050_Writebyte(MPU6050_PWR_MGMT_1, 0x1<<7);
	HAL_Delay(100);

	//Power Management setting
	/* Default is sleep mode
	 * necessary to wake up MPU6050*/
	MPU6050_Writebyte(MPU6050_PWR_MGMT_1, 0x00);
	HAL_Delay(50);

	//Sample rate divider
	/*Sample Rate = Gyroscope Output Rate / (1 + SMPRT_DIV) */
	//	MPU6050_Writebyte(MPU6050_SMPRT_DIV, 0x00); // ACC output rate is 1kHz, GYRO output rate is 8kHz
	MPU6050_Writebyte(MPU6050_SMPRT_DIV, 39); // Sample Rate = 200Hz
	HAL_Delay(50);

	//FSYNC and DLPF setting
	/*DLPF is set to 0*/
	MPU6050_Writebyte(MPU6050_CONFIG, 0x00);
	HAL_Delay(50);

	//GYRO FULL SCALE setting
	/*FS_SEL  Full Scale Range
	  0    	+-250 degree/s
	  1		+-500 degree/s
	  2		+-1000 degree/s
	  3		+-2000 degree/s	*/
	uint8_t FS_SCALE_GYRO = 0x0;
	MPU6050_Writebyte(MPU6050_GYRO_CONFIG, FS_SCALE_GYRO<<3);
	HAL_Delay(50);

	//ACCEL FULL SCALE setting
	/*FS_SEL  Full Scale Range
	  0    	+-2g
	  1		+-4g
	  2		+-8g
	  3		+-16g	*/
	uint8_t FS_SCALE_ACC = 0x0;
	MPU6050_Writebyte(MPU6050_ACCEL_CONFIG, FS_SCALE_ACC<<3);
	HAL_Delay(50);

	MPU6050_Get_LSB_Sensitivity(FS_SCALE_GYRO, FS_SCALE_ACC);
	printf("LSB_Sensitivity_GYRO: %f, LSB_Sensitivity_ACC: %f\n",LSB_Sensitivity_GYRO, LSB_Sensitivity_ACC);

	// //Interrupt PIN setting
	// uint8_t INT_LEVEL = 0x0; //0 - active high, 1 - active low
	// uint8_t LATCH_INT_EN = 0x0; //0 - INT 50us pulse, 1 - interrupt clear required
	// uint8_t INT_RD_CLEAR = 0x1; //0 - INT flag cleared by reading INT_STATUS, 1 - INT flag cleared by any read operation
	// MPU6050_Writebyte(MPU6050_INT_PIN_CFG, (INT_LEVEL<<7)|(LATCH_INT_EN<<5)|(INT_RD_CLEAR<<4)); //
	// HAL_Delay(50);

	// //Interrupt enable setting
	// uint8_t DATA_RDY_EN = 0x0; // 1 - enable, 0 - disable
	// MPU6050_Writebyte(MPU6050_INT_ENABLE, DATA_RDY_EN);
	// HAL_Delay(50);

	printf("MPU6050 setting is finished\n");
}
/*Get Raw Data from sensor*/
void MPU6050_Get6AxisRawData(Struct_MPU6050* mpu6050)
{
	uint8_t data[14];
	MPU6050_Readbytes(MPU6050_ACCEL_XOUT_H, 14, data);

	mpu6050->acc_x_raw = (data[0] << 8) | data[1];
	mpu6050->acc_y_raw = (data[2] << 8) | data[3];
	mpu6050->acc_z_raw = (data[4] << 8) | data[5];

	mpu6050->temperature_raw = (data[6] << 8) | data[7];

	mpu6050->gyro_x_raw = ((data[8] << 8) | data[9]);
	mpu6050->gyro_y_raw = ((data[10] << 8) | data[11]);
	mpu6050->gyro_z_raw = ((data[12] << 8) | data[13]);
}

void MPU6050_Get_LSB_Sensitivity(uint8_t FS_SCALE_GYRO, uint8_t FS_SCALE_ACC)
{
	switch(FS_SCALE_GYRO)
	{
	case 0:
		LSB_Sensitivity_GYRO = 131.f;
		break;
	case 1:
		LSB_Sensitivity_GYRO = 65.5f;
		break;
	case 2:
		LSB_Sensitivity_GYRO = 32.8f;
		break;
	case 3:
		LSB_Sensitivity_GYRO = 16.4f;
		break;
	}
	switch(FS_SCALE_ACC)
	{
	case 0:
		LSB_Sensitivity_ACC = 16384.f;
		break;
	case 1:
		LSB_Sensitivity_ACC = 8192.f;
		break;
	case 2:
		LSB_Sensitivity_ACC = 4096.f;
		break;
	case 3:
		LSB_Sensitivity_ACC = 2048.f;
		break;
	}
}

/*Convert Unit. acc_raw -> g, gyro_raw -> degree per second*/
void MPU6050_DataConvert(Struct_MPU6050* mpu6050)
{
	//printf("LSB_Sensitivity_GYRO: %f, LSB_Sensitivity_ACC: %f\n",LSB_Sensitivity_GYRO,LSB_Sensitivity_ACC);
	mpu6050->acc_x = (float)(mpu6050->acc_x_raw / LSB_Sensitivity_ACC);
	mpu6050->acc_y = (float)(mpu6050->acc_y_raw / LSB_Sensitivity_ACC);
	mpu6050->acc_z = (float)(mpu6050->acc_z_raw / LSB_Sensitivity_ACC);

	mpu6050->temperature = (float)(mpu6050->temperature_raw)/340+36.53;

	mpu6050->gyro_x = (float)(mpu6050->gyro_x_raw / LSB_Sensitivity_GYRO);
	mpu6050->gyro_y = (float)(mpu6050->gyro_y_raw / LSB_Sensitivity_GYRO);
	mpu6050->gyro_z = (float)(mpu6050->gyro_z_raw / LSB_Sensitivity_GYRO);
}


int MPU6050_DataReady(void)
{
	// return HAL_GPIO_ReadPin(MPU6050_INT_PORT, MPU6050_INT_PIN);
    HAL_Delay(1000);
    return 1;
}

void MPU6050_ProcessData(Struct_MPU6050* mpu6050)
{
	MPU6050_Get6AxisRawData(mpu6050);
	// MPU6050_DataConvert(mpu6050);
}

void MPU6050_Init (void)
{
	uint8_t check;
	uint8_t Data;

    // Mở kênh I2C (bus 1, địa chỉ 0x40)
    handle = i2cOpen(1, MPU6050_ADDR, 0);
    if (handle < 0) 
    {
        printf("Không thể mở kênh I2C\n");
        gpioTerminate();
        return ;
    }
	
	// check device ID WHO_AM_I
	MPU6050_Readbyte(MPU6050_WHO_AM_I, &check);
	if (check == 0x68)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		// Data = 0;
		MPU6050_Writebyte(MPU6050_PWR_MGMT_1, 0x00);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		// Data = 0x07;
		// HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, 0x19, 1, &Data, 1, 1000);
		MPU6050_Writebyte(MPU6050_SMPRT_DIV, 0x07);

		/* Set Gyroscopic configuration in GYRO_CONFIG Register
		XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 ̐/s
		Note:
			FS_SEL  Full Scale Range
			0    	+-250 degree/s
			1		+-500 degree/s
			2		+-1000 degree/s
			3		+-2000 degree/s	*/
		Data = 0x00;  
		// HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, 0x1B, 1, &Data, 1, 1000);
		MPU6050_Writebyte(MPU6050_GYRO_CONFIG, 0);

		/* Set accelerometer configuration in ACCEL_CONFIG Register
		XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ± 2g
		Note:
			FS_SEL  Full Scale Range
			0    	+-2g
			1		+-4g
			2		+-8g
			3		+-16g */
		Data = 0x00;  
		// HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, 0x1C, 1, &Data, 1, 1000);
		MPU6050_Writebyte(0x1C, 0);
	}

}

void MPU6050_Read_Accel (void)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H (0x3B) register
	// HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, 0x3B, 1, Rec_Data, 6, 1000);
	MPU6050_Readbytes(MPU6050_ACCEL_XOUT_H, 6, Rec_Data);

	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/

	Ax = (float)Accel_X_RAW/16384.0;
	Ay = (float)Accel_Y_RAW/16384.0;
	Az = (float)Accel_Z_RAW/16384.0;
}

void MPU6050_Read_Gyro (void)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from GYRO_XOUT_H register
	// HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, 0x43, 1, Rec_Data, 6, 1000);
	MPU6050_Readbytes(MPU6050_GYRO_XOUT_H, 6, Rec_Data);

	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into dps (ｰ/s)
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 131.0
	     for more details check GYRO_CONFIG Register              ****/

	Gx = (float)Gyro_X_RAW/131.0;
	Gy = (float)Gyro_Y_RAW/131.0;
	Gz = (float)Gyro_Z_RAW/131.0;
	// printf("Value X %f Y %f Z %f \n",Gx,Gy,Gz);

	// Tính Pitch và Roll
    float pitch_accel = atan(Ax / sqrt(Ay * Ay + Az * Az)) * RAD_TO_DEG;
    float roll_accel  = atan(Ay / sqrt(Ax * Ax + Az * Az)) * RAD_TO_DEG;

	printf("Value X %f Y %f \n",pitch_accel,roll_accel);
	// // Thời gian trôi qua giữa các lần đọc (ở đây giả định là 1 ms)
    // float dt = 1.1;

    // // Cập nhật giá trị pitch và roll bằng cách sử dụng complementary filter
    // static float pitch = 0, roll = 0;

    // pitch = ALPHA * (pitch + Gx * dt) + (1 - ALPHA) * pitch_accel;
    // roll = ALPHA * (roll + Gy * dt) + (1 - ALPHA) * roll_accel;

	// printf("Value X %f Y %f \n",pitch,roll);
}

void MPU6050_Read_All(void)
{
	uint8_t Rec_Data[14];
	MPU6050_Readbytes(MPU6050_ACCEL_XOUT_H, 14, Rec_Data);

	// Gia tốc (accel) từ 0x3B đến 0x40
    Accel_X_RAW = (Rec_Data[0] << 8) | Rec_Data[1];  // accel_x
    Accel_Y_RAW = (Rec_Data[2] << 8) | Rec_Data[3];  // accel_y
    Accel_Z_RAW = (Rec_Data[4] << 8) | Rec_Data[5];  // accel_z

    // Con quay hồi chuyển (gyro) từ 0x43 đến 0x48
    Gyro_X_RAW = (Rec_Data[8]  << 8) | Rec_Data[9];   // gyro_x
    Gyro_Y_RAW = (Rec_Data[10] << 8) | Rec_Data[11];  // gyro_y
    Gyro_Z_RAW = (Rec_Data[12] << 8) | Rec_Data[13];  // gyro_z

	Ax = (float)Accel_X_RAW/16384.0;
	Ay = (float)Accel_Y_RAW/16384.0;
	Az = (float)Accel_Z_RAW/16384.0;

	Gx = (float)Gyro_X_RAW/131.0;
	Gy = (float)Gyro_Y_RAW/131.0;
	Gz = (float)Gyro_Z_RAW/131.0;

	// Tính Pitch và Roll của Accel
    float pitch_accel = atan(Ax / sqrt(Ay * Ay + Az * Az)) * RAD_TO_DEG;
    float roll_accel  = atan(Ay / sqrt(Ax * Ax + Az * Az)) * RAD_TO_DEG;

	printf("Value X %f Y %f \n",pitch_accel,roll_accel);

	HAL_Delay(100);
}