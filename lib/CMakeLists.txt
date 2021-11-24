# add_library(Helpers Helpers.hpp
# )

add_library(PwmDevices 
	PwmDevices/PwmDevices.cpp PwmDevices.hpp
	PwmDevices/Servo.cpp Servo.hpp
)
target_link_libraries(PwmDevices
	pico_stdlib 
	hardware_pwm
)