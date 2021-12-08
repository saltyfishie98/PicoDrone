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
	I2CComms.cpp 
)
target_link_libraries(I2CComms
	pico_stdlib 
	hardware_i2c
)
target_include_directories(I2CComms PRIVATE ${PROJECT_SOURCE_DIR}/include)