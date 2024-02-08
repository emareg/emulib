#include "pidc.h"


PID_Controller::PID_Controller(Gain_Type kP, Gain_Type kI, Gain_Type kD,
               Input_Type integral_limit_min, Input_Type integral_limit_max,
               Output_Type output_limit_min, Output_Type output_limit_max)
    : m_kP(kP)
    , m_kI(kI)
    , m_kD(kD)
    , INTEGRAL_LIMIT_MIN(integral_limit_min)
    , INTEGRAL_LIMIT_MAX(integral_limit_max)
    , OUTPUT_LIMIT_MIN(output_limit_min)
    , OUTPUT_LIMIT_MAX(output_limit_max)
{ }


void PID_Controller::init(Input_Type error, Input_Type error_integral){
    m_last_error = error;
    m_error_integral = error_integral;
    m_last_derivative = 0.0;
}


void PID_Controller::set_Derivative_Low_Pass(Time_Type time_constant_tau){
    m_tau = time_constant_tau;
}


void PID_Controller::set_Sensitivity(Gain_Type sensitivity){
    m_sensitivity = sensitivity;
}


void PID_Controller::set_Process_Symmetry(float ratio_increase_to_decrease){
    m_symmetry = ratio_increase_to_decrease;
}


Output_Type PID_Controller::step(const Input_Type error, const Time_Type dt){
    Output_Type output = 0.0;
    Input_Type error_derivative = 0.0;

    // derivative part
    calculate_derivative(error, dt);

    // integral part
    calculate_integral(error, dt);

    // let the magic happen
    output = Output_Type( m_kP * error +
                          m_kI * m_error_integral +
                          m_kD * error_derivative );
    // scale output
    output *= m_sensitivity;

    // saturate output
    if(output < OUTPUT_LIMIT_MIN){ output = OUTPUT_LIMIT_MIN; }
    if(output > OUTPUT_LIMIT_MAX){ output = OUTPUT_LIMIT_MAX; }

    // save old values
    m_last_error = error;

    return output;
}


Output_Type PID_Controller::step_given_pd(const Input_Type error, const Input_Type error_derivative, const Time_Type dt){
    calculate_integral(error, dt);

    return calculate_output(error, m_error_integral, error_derivative);
}


Output_Type PID_Controller::step_given_pi(const Input_Type error, const Input_Type error_integral, const Time_Type dt){
    Input_Type error_derivative = calculate_derivative(error, dt);
    return calculate_output(error, error_integral, error_derivative);
}


Output_Type PID_Controller::step_given_pid(const Input_Type error,
                                           const Input_Type error_integral,
                                           const Input_Type error_derivative){

    return calculate_output(error, error_integral, error_derivative);
}


Output_Type PID_Controller::calculate_output(const Input_Type error,
                                      const Input_Type error_integral,
                                      const Input_Type error_derivative){

    Output_Type output = Output_Type( m_kP * error +
                                      m_kI * error_integral +
                                      m_kD * error_derivative );

    output *= m_sensitivity;
    output = saturate(output, OUTPUT_LIMIT_MIN, OUTPUT_LIMIT_MAX);

    // save old value
    m_last_error = error;

    return output;
}


Input_Type PID_Controller::calculate_derivative(const Input_Type error, const Time_Type dt){
    Input_Type error_derivative = 0.0;
    if( dt > EPSILON ){
        error_derivative = (error - m_last_error) / dt;

        // apply discrete low pass filter if tau is set
        if (m_tau != 0.0){
            error_derivative = m_last_derivative + (dt / (m_tau + dt)) * (error_derivative - m_last_derivative);
        }
    }
    m_last_derivative = error_derivative;
    return error_derivative;
}


Input_Type PID_Controller::calculate_integral(const Input_Type error, const Time_Type dt){
    m_error_integral += error * dt;

    // saturate integral (prevent windup)
    if(m_error_integral < INTEGRAL_LIMIT_MIN){ m_error_integral = INTEGRAL_LIMIT_MIN; }
    if(m_error_integral > INTEGRAL_LIMIT_MAX){ m_error_integral = INTEGRAL_LIMIT_MAX; }

    return m_error_integral;
}


Numeric_Type PID_Controller::saturate(Numeric_Type val, const Numeric_Type min, const Numeric_Type max){
    if(val < min){ val = min; }
    if(val > max){ val = max; }
    return val;
}