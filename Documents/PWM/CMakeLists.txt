# Đặt phiên bản tối thiểu của CMake yêu cầu
cmake_minimum_required(VERSION 3.10)

# Đặt tên cho project
project(MyPWM)

# Thêm tệp nguồn vào project
add_executable(MyPWM main.c)

# Liên kết các thư viện cần thiết
target_link_libraries(MyPWM pigpio pthread)


