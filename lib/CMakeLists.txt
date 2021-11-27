add_library(Helpers STATIC
	Helpers/Misc.cpp
	Helpers/Pico.cpp
)
target_link_libraries(Helpers
	pico_stdlib 
	hardware_adc
)
target_include_directories(Helpers PRIVATE ${PROJECT_SOURCE_DIR}/include)


add_library(Pwm50Devices STATIC
	Pwm50Devices/Pwm50Devices.cpp 
	Pwm50Devices/Servo.cpp
	Pwm50Devices/Motor.cpp
)
target_link_libraries(Pwm50Devices
	pico_stdlib 
	hardware_pwm
)
target_include_directories(Pwm50Devices PRIVATE ${PROJECT_SOURCE_DIR}/include)


add_library(ErrorHandler STATIC
	ErrorHandler/ErrorBlinker.cpp 
)
target_link_libraries(ErrorHandler
	pico_stdlib 
)
target_include_directories(ErrorHandler PRIVATE ${PROJECT_SOURCE_DIR}/include)
