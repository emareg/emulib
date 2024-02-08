/* PID Template for generic PID controller
 *
 * Author: Emanuel Regnath (emanuel.regnath@tum.de)
 *
 * Features: generic types, integral limits, output limits
 *
 * Theory: the error e of a type is used to calculate the control
 *         value u of another type according to the equation
 *
 *  u[i] = kP * e   +   kI * Σ e[l]*dt   +   kD * (e[i]-e[i-1])/dt
 *
 */



#ifndef GENERIC_PID_CONTROLLER_H
#define GENERIC_PID_CONTROLLER_H


#define EPSILON 1.0e-12
typedef float Numeric_Type;

typedef Numeric_Type Input_Type;
typedef Numeric_Type Output_Type;
typedef Numeric_Type Gain_Type;
typedef Numeric_Type Time_Type;


class PID_Controller{

public:

    PID_Controller(Gain_Type kP, Gain_Type kI, Gain_Type kD,
                   Input_Type integral_limit_min = -1.0e32, Input_Type integral_limit_max = 1.0e32,
                   Output_Type output_limit_min = -1.0e32, Output_Type output_limit_max = 1.0e32);


    /** initializes internal state variables, such as the last error and the integral, to prevent
     * peaks at the first call of step */
    void initialize(Input_Type error, Input_Type error_integral);


    /** set a time constant for the low pass filter of the derivative calculation.
     * The default value of 0.0 deactivates the low pass filter */
    void set_Derivative_Low_Pass(Time_Type time_constant_tau);


    /** sets an overall sensitivity gain of the controller. The output will be scaled by this value,
     * which can be usefull to account for a dynamic process sensitivity without changing the relations
     * of the PID gains kP, kI, and kD. Defaults to 1.0 */
    void set_Sensitivity(Gain_Type sensitivity);


    /** sets the symmetry ratio of the control process. Useful for asymmetric processes, where increasing
     * the control variable has a different sensitivity than decreasing the control variable. Default 1.0.
     * For example, lifting something up requires more effort than letting it down, because of gravity */
    void set_Process_Symmetry(float ratio_increase_to_decrease);


    /** locks the pid configuration. After this call, changes of sensitivity or symmetry are not possible */
    void lock_Config();

    /** performs the PID calculation. It calculates integral part and derivative from previous calls. */
    Output_Type step(const Input_Type error, const Time_Type dt);

    // alternatives, which provide more information
    Output_Type step_given_pd(const Input_Type error, const Input_Type error_derivative, const Time_Type dt);
    Output_Type step_given_pi(const Input_Type error, const Input_Type error_integral, const Time_Type dt);
    Output_Type step_given_pid(const Input_Type error, const Input_Type error_integral, const Input_Type error_derivative);


private:
    bool isConfigLocked = false;

    Input_Type m_last_error;
    Input_Type m_last_derivative;
    Input_Type m_error_integral;

    const Gain_Type m_kP;
    const Gain_Type m_kI;
    const Gain_Type m_kD;

    Gain_Type m_sensitivity = 1.0;
    Numeric_Type m_symmetry = 1.0;

    Time_Type m_tau = 0.0;  // lpf time constant: 0.0 => no filtering

    const Input_Type INTEGRAL_LIMIT_MIN;
    const Input_Type INTEGRAL_LIMIT_MAX;
    const Output_Type OUTPUT_LIMIT_MIN;
    const Output_Type OUTPUT_LIMIT_MAX;

    Numeric_Type saturate(Numeric_Type val, const Numeric_Type min, const Numeric_Type max);
    Input_Type calculate_derivative(const Input_Type error, const Time_Type dt);
    Input_Type calculate_integral(const Input_Type error, const Time_Type dt);
    Output_Type calculate_output(const Input_Type error, const Input_Type error_integral, const Input_Type error_derivative);

};

#endif //GENERIC_PID_CONTROLLER_H