#include <stdio.h>
#include <pigpio.h>
#include <unistd.h> // Để sử dụng sleep()

#define PWM_PIN 18  // Sử dụng GPIO18 (chân vật lý 12)

int main() {
    // Khởi tạo pigpio
    if (gpioInitialise() < 0) {
        printf("Không thể khởi tạo pigpio\n");
        return 1;
    }

    // Thiết lập tần số PWM (ví dụ: 1000 Hz)
    if (gpioSetPWMfrequency(PWM_PIN, 1000) < 0) {
        printf("Không thể thiết lập tần số PWM\n");
        gpioTerminate();
        return 1;
    }

    printf("Điều khiển độ sáng LED bằng PWM. Nhấn Ctrl+C để thoát.\n");

    while (1) {
        // Tăng độ sáng từ 0% đến 100%
        for (int duty_cycle = 0; duty_cycle <= 255; duty_cycle += 5) {
            gpioPWM(PWM_PIN, duty_cycle); // Thiết lập PWM với duty cycle
            usleep(20000);                // Đợi 20ms
        }

        // Giảm độ sáng từ 100% xuống 0%
        for (int duty_cycle = 255; duty_cycle >= 0; duty_cycle -= 5) {
            gpioPWM(PWM_PIN, duty_cycle); // Thiết lập PWM với duty cycle
            usleep(20000);                // Đợi 20ms
        }
    }

    // Dọn dẹp pigpio (không bao giờ tới đây do vòng lặp vô hạn)
    gpioTerminate();

    return 0;
}
