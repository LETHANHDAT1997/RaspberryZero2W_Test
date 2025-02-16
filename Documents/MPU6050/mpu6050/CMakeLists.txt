# Tạo thư viện bằng các mã nguồn bên trong thư mục funtion_1
add_library(Lib_mpu6050 mpu6050.c)

target_link_libraries(Lib_mpu6050 m)

# target_include_directories(Lib_mpu6050 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
