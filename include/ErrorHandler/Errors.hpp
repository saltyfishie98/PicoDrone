#ifndef C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRORS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRORS_HPP_

//// Approximated Error location ////////////////////////////////////////////////
#define ERR_NONE 0
#define ERR_ADC	 1
#define ERR_PWM	 2

// clang-format off

//// Error Details ////////////////////////////////////////////////
// General Details
#define ERR_DT_GPIO_PIN_NUM_EXCEED 	1

// Pwm
#define ERR_DT_PWM_INVALID_PERCENT 	2

// Adc
#define ERR_DT_ADC_INVALID_PIN 		2

//clang-format on
#endif // C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRORS_HPP_