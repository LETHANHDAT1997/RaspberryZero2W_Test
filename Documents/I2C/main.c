#include <stdio.h>
#include <pigpio.h>

#define I2C_ADDR 0x40 // Địa chỉ I2C của thiết bị (ví dụ: 0x40)

int main() {
    // Khởi tạo pigpio
    if (gpioInitialise() < 0) 
    {
        printf("Không thể khởi tạo pigpio\n");
        return 1;
    }

    // Mở kênh I2C (bus 1, địa chỉ 0x40)
    int handle = i2cOpen(1, I2C_ADDR, 0);
    if (handle < 0) 
    {
        printf("Không thể mở kênh I2C\n");
        gpioTerminate();
        return 1;
    }

    // Ghi dữ liệu vào thiết bị I2C (ví dụ: ghi giá trị 0xA5 vào thanh ghi 0x01)
    int reg = 0x01;    // Thanh ghi
    int value = 0xA5;  // Giá trị cần ghi
    if (i2cWriteByteData(handle, reg, value) < 0) 
    {
        printf("Không thể ghi dữ liệu vào thiết bị I2C\n");
    } else 
    {
        printf("Ghi thành công: Thanh ghi 0x%02X, Giá trị 0x%02X\n", reg, value);
    }

    // Đọc dữ liệu từ thiết bị I2C (ví dụ: đọc từ thanh ghi 0x01)
    int read_value = i2cReadByteData(handle, reg);
    if (read_value < 0) 
    {
        printf("Không thể đọc dữ liệu từ thiết bị I2C\n");
    } else 
    {
        printf("Đọc thành công: Thanh ghi 0x%02X, Giá trị 0x%02X\n", reg, read_value);
    }

    // Đóng kênh I2C
    i2cClose(handle);

    // Dọn dẹp pigpio
    gpioTerminate();

    return 0;
}
