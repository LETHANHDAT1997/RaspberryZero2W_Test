# Đặt phiên bản tối thiểu của CMake yêu cầu
cmake_minimum_required(VERSION 3.10)

# Đặt tên cho project
project(MyMPU6050)

# Thêm các thư mục chứa các file header cho toàn bộ dự án, lệnh này không cần target
include_directories(mpu6050)

# Thêm các thư mục con và xử lí các cấu trúc CMakeList bên trong thư mục con đó, thường phải đi kèm với include_directories hoặc target_include_directories, nếu không các thư viện hoặc executable được tạo ra không để làm gì cả   
add_subdirectory(mpu6050)

# Thêm tệp nguồn vào project
add_executable(MyMPU6050 main.c)

# Liên kết các thư viện cần thiết
target_link_libraries(MyMPU6050 pigpio pthread m)
target_link_libraries(MyMPU6050 Lib_mpu6050)
