add_library(Helpers STATIC
	Helpers/Misc.cpp
	Helpers/Pico.cpp
)
target_link_libraries(Helpers
	pico_stdlib 
	hardware_adc
)
target_include_directories(Helpers PRIVATE ${PROJECT_SOURCE_DIR}/include)


add_library(PwmDevices STATIC
	PwmDevices.cpp 
)
target_link_libraries(PwmDevices
	pico_stdlib 
	hardware_pwm
)
target_include_directories(PwmDevices PRIVATE ${PROJECT_SOURCE_DIR}/include)


add_library(ErrorHandler STATIC
	ErrorHandler/ErrorBlinker.cpp 
)
target_link_libraries(ErrorHandler
	pico_stdlib 
)
target_include_directories(ErrorHandler PRIVATE ${PROJECT_SOURCE_DIR}/include)
