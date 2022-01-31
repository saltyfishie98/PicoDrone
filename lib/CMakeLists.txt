add_library(Helpers STATIC
	Misc.cpp
	Pico.cpp
	../include/Helpers/Pico.hpp
)
target_link_libraries(Helpers
	pico_stdlib 
	hardware_adc
	hardware_spi
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



add_library(MPU9250 STATIC
	CpMpu9250.cpp 
	CpMpu9250.c
	MPU9250.cpp
)
target_link_libraries(MPU9250
	pico_stdlib 
	hardware_spi
	Helpers
)
target_include_directories(MPU9250 PRIVATE ${PROJECT_SOURCE_DIR}/include)



add_library(Remote STATIC
	Remote.cpp 
)
target_link_libraries(Remote
	pico_stdlib 
	LoRa_pico_lib
	LoRa_print
)
target_include_directories(Remote PRIVATE ${PROJECT_SOURCE_DIR}/include)



add_library(Pid STATIC
	Pid.cpp 
)
target_link_libraries(Pid
	pico_stdlib 
)
target_include_directories(Pid PRIVATE ${PROJECT_SOURCE_DIR}/include)