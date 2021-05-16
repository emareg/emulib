/* LED-Library by Emanuel Regnath (emanuel.regnath@tum.de)    Date: 2015-05-20
 *
 * Description:
 * Portable LED Library that features switching, blinking and morse (non-blocking)
 *
 * Setup:
 * To port the lib to your system, simply overwrite the 2 functions LED_HAL_init
 * and LED_HAL_set in the .cpp file and adjust the HAL part in the .hpp file
 *
 * Usage:
 * 1. call LED_init which will configure the LED port and pin
 * 2. call LED_switch or LED_blink or LED_morse to select the operation mode
 * 3. frequently call LED_tick and LED_sync to manage LED timings.
 */


#ifdef __cplusplus
extern "C" {
#endif

// HAL: adjust these types to your system
// ----------------------------------------------------------------------------

typedef unsigned int Time_Type;     // max. value: 7 * BLINK_TIME
#define BLINK_TIME (Time_Type)250   // arbitrary time basis (dot time in morse mode)
typedef int Led_Id_Type;            // any led identifier e.g. struct with port and pin 

// ----------------------------------------------------------------------------


typedef enum LED_State_Enum {ON, OFF} LED_State_Type;

typedef enum LED_Blink_Enum {
	SLOW = BLINK_TIME*3, 
	FAST = BLINK_TIME, 
	FLASH = BLINK_TIME/2
} LED_Blink_Type;


/* configures which LED to use */
void LED_init(Led_Id_Type id);

/* increases the internal timing counter
* elapsed_time should be a divider of BLINK_TIME. */
void LED_tick(Time_Type elapsed_time);

/* perform LED switching in blink or morse mode */
void LED_sync();

/* switch LED on or off (will stop blink or morse mode) */  
void LED_switchOn();
void LED_switchOff();

/* select blink mode */
void LED_blink(LED_Blink_Type speed);
void LED_blinkPulse(Time_Type on_time, Time_Type off_time);

/* select morse mode */
void LED_morse(char* msg_string);   // ensure 0-terminated string!


#ifdef __cplusplus
}
#endif
