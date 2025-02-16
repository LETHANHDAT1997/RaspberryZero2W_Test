#include <stdio.h>
#include <pigpio.h>

#define SPI_CHANNEL 0 // SPI Channel 0 (CE0)
#define SPI_SPEED 500000 // Tốc độ SPI: 500 kHz

int main() 
{
    // Khởi tạo pigpio
    if (gpioInitialise() < 0) 
    {
        printf("Không thể khởi tạo pigpio\n");
        return 1;
    }

    // Mở kết nối SPI trên kênh 0 với tốc độ 500 kHz
    int handle = spiOpen(SPI_CHANNEL, SPI_SPEED, 0); // Mode = 0 (SPI_MODE_0)
    if (handle < 0) 
    {
        printf("Không thể mở kênh SPI\n");
        gpioTerminate();
        return 1;
    }

    printf("Bắt đầu giao tiếp SPI\n");

    // Gửi dữ liệu qua SPI
    char tx_data[3] = {0x01, 0x02, 0x03}; // Dữ liệu gửi đi
    char rx_data[3];                      // Bộ đệm nhận dữ liệu

    int result = spiXfer(handle, tx_data, rx_data, 3); // Gửi và nhận 3 byte
    if (result < 0) 
    {
        printf("Không thể truyền dữ liệu qua SPI\n");
    } 
    else 
    {
        printf("Gửi: ");
        for (int i = 0; i < 3; i++) 
        {
            printf("0x%02X ", tx_data[i]);
        }
        printf("\nNhận: ");
        for (int i = 0; i < 3; i++) 
        {
            printf("0x%02X ", rx_data[i]);
        }
        printf("\n");
    }

    // Đóng kênh SPI
    spiClose(handle);

    // Dọn dẹp pigpio
    gpioTerminate();

    return 0;
}
