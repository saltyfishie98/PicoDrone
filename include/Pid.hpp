#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PID_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PID_HPP_

#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>

namespace PicoPilot {
	class Pid {
	  public:
		struct Configs {
			float Kp = 5.f;
			float Ki = 0.5f;
			float Kd = 2.5f;

			float tau = 0.02f;

			float outMin = -511.f;
			float outMax = 511.f;

			float integralMin = -500.f;
			float integralMax = 500.f;
		};

		static Pid create(const Configs& configurations) noexcept;

		Pid() = default;

		template <typename T_out>
		T_out update(const float& setpoint, const float& measurement) noexcept {
			float sampleTime = (float)absolute_time_diff_us(m_last, absolute_time_t()) / 1000000.f;
			m_last = get_absolute_time();

			float error = setpoint - measurement;
			float proportional = m_configs.Kp * error;
			m_integrator = m_integrator + 0.5f * m_configs.Ki * sampleTime * (error + m_prevError);
			m_differentiator = -(2.0f * m_configs.Kd * (measurement - m_prevMeasurement) +
								 (2.0f * m_configs.tau - sampleTime) * m_differentiator) /
							   (2.0f * m_configs.tau + sampleTime);
			// Note: derivative on measurement, therefore minus sign in front of equation!

			// Anti-wind-up via integrator clamping
			if (m_integrator > m_configs.integralMax) {
				m_integrator = m_configs.integralMax;
			} else if (m_integrator < m_configs.integralMin) {
				m_integrator = m_configs.integralMin;
			}

			m_prevError = error;
			m_prevMeasurement = measurement;

			T_out out = proportional + m_integrator + m_differentiator;

			if (out > m_configs.outMax) {
				out = m_configs.outMax;
			} else if (out < m_configs.outMin) {
				out = m_configs.outMin;
			}

			// printf("setpoint: %f\n", setpoint);
			// printf("measurement: %f\n", measurement);
			// printf("error: %f\n", error);
			// printf("proportional: %f\n", proportional);
			// printf("integrator: %f\n", m_integrator);
			// printf("differentiator: %f\n", m_differentiator);
			// printf("raw output: %d\n\n", out);

			return out;
		}

	  protected:
		Pid(Configs&& configurations) : m_configs(configurations) {}

	  private:
		Configs m_configs;
		float m_integrator = 0.f;
		float m_differentiator = 0.f;
		float m_prevError = 0.f;
		float m_prevMeasurement = 0.f;
		absolute_time_t m_last = get_absolute_time();
	};
} // namespace PicoPilot

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PID_HPP_