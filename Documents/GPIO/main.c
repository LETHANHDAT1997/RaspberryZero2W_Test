#include <stdio.h>
#include <pigpio.h>
#include <unistd.h> // Để sử dụng sleep

#define LED_PIN 22 // Sử dụng GPIO17 (chân vật lý 11)

int main() {
    // Khởi tạo pigpio
    if (gpioInitialise() < 0) 
    {
        printf("Không thể khởi tạo pigpio\n");
        return 1;
    }

    // Thiết lập chân GPIO là output
    gpioSetMode(LED_PIN, PI_OUTPUT);

    printf("Nhấp nháy LED. Nhấn Ctrl+C để dừng.\n");

    while (1) 
    {
        // Bật LED
        gpioWrite(LED_PIN, 1);
        printf("LED ON\n");
        // Hàm usleep tính bằng micro giây => 10^-6 giây
        usleep(50 * 1000); // Giữ LED bật trong 50 milis

        // Tắt LED
        gpioWrite(LED_PIN, 0);
        printf("LED OFF\n");
        usleep(50 * 1000); // Giữ LED tắt trong 50 milis
    }

    // Dọn dẹp pigpio (không bao giờ tới đây do vòng lặp vô hạn)
    gpioTerminate();

    return 0;
}
