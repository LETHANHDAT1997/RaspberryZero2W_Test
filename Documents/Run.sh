#!/bin/bash

# Khai báo biến lưu giữ giá đường dẫn
pathGPIO="./GPIO/"
pathPWM="./PWM/"
pathI2C="./I2C/"
pathSPI="./SPI/"
pathMPU6050="./MPU6050/"
pathC_Plus_Plus_Data_Structure_Algorihms="./C_Plus_Plus_Data_Structure_Algorihms/"
nameshell="Build_and_Run.sh"

# Khai báo biến lựa chọn
echo "Chọn một giá trị để thực hiện lệnh:"
echo "1 - Chạy GPIO"
echo "2 - Chạy I2C"
echo "3 - Chạy PWM"
echo "4 - Chạy SPI"
echo "5 - Chạy MPU6050"
echo "6 - Chạy C_Plus_Plus_Data_Structure_Algorihms"
read -p "Nhập giá trị (1-6): " value

# Kiểm tra giá trị và thực hiện lệnh tương ứng
if [ "$value" -eq 1 ]; then
    echo "Đang chạy lệnh GPIO..."
    if [ -d "$pathGPIO" ]; then
        cd $pathGPIO
        if [ -f "$nameshell" ]; then
            sudo sh $nameshell
        else
            echo "Lỗi: Không tìm thấy tệp $nameshell trong thư mục $pathGPIO."
        fi
    else
        echo "Lỗi: Thư mục $pathGPIO không tồn tại."
    fi
elif [ "$value" -eq 2 ]; then
    echo "Đang chạy lệnh I2C..."
    if [ -d "$pathI2C" ]; then
        cd $pathI2C
        if [ -f "$nameshell" ]; then
            sudo sh $nameshell
        else
            echo "Lỗi: Không tìm thấy tệp $nameshell trong thư mục $pathI2C."
        fi
    else
        echo "Lỗi: Thư mục $pathI2C không tồn tại."
    fi
elif [ "$value" -eq 3 ]; then
    echo "Đang chạy lệnh PWM..."
    if [ -d "$pathPWM" ]; then
        cd $pathPWM
        if [ -f "$nameshell" ]; then
            sudo sh $nameshell
        else
            echo "Lỗi: Không tìm thấy tệp $nameshell trong thư mục $pathPWM."
        fi
    else
        echo "Lỗi: Thư mục $pathPWM không tồn tại."
    fi
elif [ "$value" -eq 4 ]; then
    echo "Đang chạy lệnh SPI..."
    if [ -d "$pathSPI" ]; then
        cd $pathSPI
        if [ -f "$nameshell" ]; then
            sudo sh $nameshell
        else
            echo "Lỗi: Không tìm thấy tệp $nameshell trong thư mục $pathSPI."
        fi
    else
        echo "Lỗi: Thư mục $pathSPI không tồn tại."
    fi
elif [ "$value" -eq 5 ]; then
    echo "Đang chạy lệnh MPU6050..."
    if [ -d "$pathMPU6050" ]; then
        cd $pathMPU6050
        if [ -f "$nameshell" ]; then
            sudo sh $nameshell
        else
            echo "Lỗi: Không tìm thấy tệp $nameshell trong thư mục $pathMPU6050."
        fi
    else
        echo "Lỗi: Thư mục $pathMPU6050 không tồn tại."
    fi
elif [ "$value" -eq 6 ]; then
    echo "Đang chạy lệnh C_Plus_Plus_Data_Structure_Algorihms..."
    if [ -d "$pathC_Plus_Plus_Data_Structure_Algorihms" ]; then
        cd $pathC_Plus_Plus_Data_Structure_Algorihms
        if [ -f "$nameshell" ]; then
            sudo sh $nameshell
        else
            echo "Lỗi: Không tìm thấy tệp $nameshell trong thư mục $pathC_Plus_Plus_Data_Structure_Algorihms."
        fi
    else
        echo "Lỗi: Thư mục $pathC_Plus_Plus_Data_Structure_Algorihms không tồn tại."
    fi
else
    echo "Giá trị không hợp lệ! Vui lòng chọn từ 1 đến 6."
fi
