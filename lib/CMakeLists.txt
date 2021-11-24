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
	PwmDevices/PwmDevices.cpp PwmDevices.hpp
	PwmDevices/Servo.cpp Servo.hpp
)
target_link_libraries(PwmDevices
	pico_stdlib 
	hardware_pwm
)