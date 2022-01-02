add_library(Helpers STATIC
	Misc.cpp
	Pico.cpp
)
target_link_libraries(Helpers
	pico_stdlib 
	hardware_adc
)
target_include_directories(Helpers PRIVATE ${PROJECT_SOURCE_DIR}/include)



add_library(PwmDevices STATIC
	GeneralDevices.cpp 
	Servo.cpp
	MotorESC.cpp
)
target_link_libraries(PwmDevices
	pico_stdlib 
	hardware_pwm
)
target_include_directories(PwmDevices PRIVATE ${PROJECT_SOURCE_DIR}/include)



add_library(ErrorHandler STATIC
	ErrorBlinker.cpp 
)
target_link_libraries(ErrorHandler
	pico_stdlib 
)
target_include_directories(ErrorHandler PRIVATE ${PROJECT_SOURCE_DIR}/include)



add_library(Quad STATIC
	Quad.cpp 
)
target_link_libraries(Quad
	pico_stdlib 
	PwmDevices
)
target_include_directories(Quad PRIVATE ${PROJECT_SOURCE_DIR}/include)


add_library(I2CComms STATIC
	I2C_Comms.cpp 
)
target_link_libraries(I2CComms
	pico_stdlib 
	hardware_i2c
)
target_include_directories(I2CComms PRIVATE ${PROJECT_SOURCE_DIR}/include)


add_library(MPU9250 STATIC
	MPU9250.cpp 
	MPU9250.c
)
target_link_libraries(MPU9250
	pico_stdlib 
	hardware_spi
)
target_include_directories(MPU9250 PRIVATE ${PROJECT_SOURCE_DIR}/include)