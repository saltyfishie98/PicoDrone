add_library(Helpers Helpers.hpp
	Helpers/Macros.hpp
	Helpers/Namespace_Arduino.hpp
	Helpers/Namespace_Pico.hpp Helpers/Namespace_Pico.cpp
)
target_link_libraries(Helpers
	pico_stdlib 
	hardware_adc
)


add_library(PwmDevices 
	PwmDevices.hpp PwmDevices/PwmDevices.cpp 
	Servo.hpp PwmDevices/Servo.cpp
	Motor.hpp PwmDevices/Motor.cpp
)
target_link_libraries(PwmDevices
	pico_stdlib 
	hardware_pwm
)


add_library(ErrorHandler ErrorHandler.hpp
	ErrorHandler/Errors.hpp
	ErrorHandler/ErrMacros.hpp
	ErrorHandler/ErrorBlinker.hpp ErrorHandler/ErrorBlinker.cpp 
)
target_link_libraries(ErrorHandler
	pico_stdlib 
)