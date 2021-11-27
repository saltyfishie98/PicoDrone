include_directories(${PROJECT_SOURCE_DIR}/lib)

add_library(Helpers STATIC
	Helpers/Macros.hpp
	Helpers/Namespace_Arduino.hpp 	
	Helpers.hpp 					Helpers/Helpers.cpp
	Helpers/Namespace_Pico.hpp 		Helpers/Namespace_Pico.cpp
)
target_link_libraries(Helpers
	pico_stdlib 
	hardware_adc
)


add_library(Pwm50Devices STATIC
	Bases/Pwm50Devices.hpp 	Pwm50Devices/Pwm50Devices.cpp 
	Servo.hpp 		Pwm50Devices/Servo.cpp
	Motor.hpp 		Pwm50Devices/Motor.cpp
)
target_link_libraries(Pwm50Devices
	pico_stdlib 
	hardware_pwm
)


add_library(ErrorHandler STATIC
	Core/ErrorHandler.hpp
	Core/ErrorHandler/Errors.hpp
	Core/ErrorHandler/ErrMacros.hpp
	Core/ErrorHandler/ErrorBlinker.hpp Core/ErrorHandler/ErrorBlinker.cpp 
)
target_link_libraries(ErrorHandler
	pico_stdlib 
)