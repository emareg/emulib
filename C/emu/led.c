/* LED-Library by Emanuel Regnath (emanuel.regnath@tum.de)    Date: 2015-05-20
 *
 * Description:
 * Portable LED Library that features switching, blinking and morse (non-blocking)
 *
 * Setup:
 * To port the lib to your system, simply overwrite the 2 functions LED_HAL_init
 * and LED_HAL_set in the .c file and adjust the HAL part in the .h file
 *
 * Usage:
 * 1. call LED_init which will configure the LED port and pin
 * 2. call LED_switch or LED_blink or LED_morse to select the operation mode
 * 3. frequently call LED_tick and LED_sync to manage LED timings.
 */

// #include <Arduino.h>  // only required for example HAL
#include "led.h"


Led_Id_Type led_id;

// HAL: adjust these functions to your system
// ----------------------------------------------------------------------------
void LED_HAL_init(Led_Id_Type led_id){	
	// pinMode(led_id, OUTPUT);  // led_id is stored 
}

void LED_HAL_set(LED_State_Type state){
	// switch(state){
	// 	case ON: digitalWrite(led_id, HIGH); break;
	// 	case OFF: digitalWrite(led_id, LOW); break;
	// }
}
// ----------------------------------------------------------------------------


typedef enum Mode_Enum {FIXED, BLINK, MORSE} LED_Mode_Type;
LED_Mode_Type led_mode = FIXED;


LED_State_Type led_state = OFF;

Time_Type time_counter = 0;


typedef struct Pulse_Struct {
	Time_Type time_mark_on;
	Time_Type time_mark_off;
} Pulse_Type;
Pulse_Type current_pulse = {0, 0};


// official morse timings
const Time_Type MORSE_DIT_TIME = BLINK_TIME;
const Time_Type MORSE_DAH_TIME = BLINK_TIME * 3;
const Time_Type MORSE_PAUSE_TIME = BLINK_TIME * 7;

// official morse codes:
char morse_alphabet[26] = {  // first 1 bit defines length
	0b101,    // a: .-
	0b11000,  // b: -...
	0b11010,  // c: -.-.
	0b1100,   // d: -..
	0b10,     // e: .
	0b10010,  // f: ..-.
	0b1110,   // g: --.
	0b10000,  // h: ....
	0b100,    // i: ..
	0b10111,  // j: .---
	0b1101,   // k: -.-
	0b10100,  // l: .-..
	0b111,    // m: --
	0b110,    // n: -.
	0b1111,   // o: ---
	0b10110,  // p: .--.
	0b11101,  // q: --.-
	0b1010,   // r: .-.
	0b1000,   // s: ...
	0b11,     // t: -
	0b1001,   // u: ..-
	0b10001,  // v: ...-
	0b1011,   // w: .--
	0b11001,  // x: -..-
	0b11011,  // y: -.--
	0b11100,  // z: --..
};

char morse_numbers[10] = {
	0b111111, // 0: -----
	0b101111, // 1: .----
	0b100111, // 2: ..---
	0b100011, // 3: ...--
	0b100001, // 4: ....-
	0b100000, // 5: .....
	0b110000, // 6: -....
	0b111000, // 7: --...
	0b111100, // 8: ---..
	0b111110  // 9: ----.
};

char pattern = 0;
unsigned int pattern_length = 0;

char *message;
unsigned int message_length = 0;
unsigned int current_character_pos = 0;



void LED_init(Led_Id_Type id){
	led_id = id;
	LED_HAL_init(id);
}

void LED_set(LED_State_Type state){
	led_state = state;
	LED_HAL_set(led_state);
}


// switch functions
void LED_switchOn(){
	led_mode = FIXED;
	LED_set(ON);
}
void LED_switchOff(){
	led_mode = FIXED;
	LED_set(OFF);
}


// blink functions
void LED_blink(LED_Blink_Type speed){
	LED_blinkPulse(speed, speed);
}

void LED_blinkPulse(Time_Type on_time, Time_Type off_time){
	led_mode = BLINK;
	current_pulse.time_mark_on = on_time;
	current_pulse.time_mark_off = current_pulse.time_mark_on + off_time;
}


// morse functions
void LED_loadNextCharacter(){
	if (current_character_pos >= message_length){
		current_character_pos = 0;
	}

	pattern_length = 1;
	char current_character = message[current_character_pos];

	if ( current_character >= 'a' && current_character <= 'z' ){  // a-z
		pattern = morse_alphabet[ current_character - 'a' ];
	} else if (current_character >= 'A' && current_character <= 'Z' ) { // A-Z
		pattern = morse_alphabet[ current_character - 'A' ];
	} else if (current_character >= '0' && current_character <= '9') {  // 0-9
		pattern = morse_numbers[ current_character - '0' ];
	} else if (current_character <= 32){  // space or escape chars
		pattern = 1;  // pause
	} else {
		pattern = 0b101000; // wait signal
	}

	while( pattern >> (pattern_length + 1) ){
		++pattern_length;
	}  
	current_character_pos++;
}

void LED_morseNextPulse(){
	if( pattern_length == 0){
		LED_loadNextCharacter();
	}
	--pattern_length;

	if( pattern == 1 ){
		current_pulse.time_mark_on = 0;
		current_pulse.time_mark_off = MORSE_DAH_TIME + MORSE_DIT_TIME;  // + pause from last char = 7 * DIT_TIME 
	} else {
		if( pattern & (1 << pattern_length) ){
			current_pulse.time_mark_on = MORSE_DAH_TIME;
		} else {
			current_pulse.time_mark_on = MORSE_DIT_TIME;
		}
	
		if( pattern_length == 0){
			if (current_character_pos < message_length) {
				current_pulse.time_mark_off = current_pulse.time_mark_on + MORSE_DAH_TIME;	
			} else {
				current_pulse.time_mark_off = current_pulse.time_mark_on + MORSE_PAUSE_TIME;
			}
		} else {
			current_pulse.time_mark_off = current_pulse.time_mark_on + MORSE_DIT_TIME;
		}
	}
}

void LED_morse(char* msg_string){
	led_mode = MORSE;
	message_length = 0;
	message = msg_string;
	while (message[message_length] != 0){
	  ++message_length;
	}
	LED_loadNextCharacter();
}




// sync functions
void LED_tick(Time_Type elapsed_time) {
	time_counter = time_counter + elapsed_time;
}

void LED_sync() {
	if(led_mode == FIXED){
		return;	 // no timing needed
	}
	if( led_state == OFF ){
		if (time_counter >= current_pulse.time_mark_off) {
			time_counter = 0;
			if (led_mode == MORSE){
			  LED_morseNextPulse();
			}
			if (current_pulse.time_mark_on > 0) { LED_set(ON); }
		} else if (time_counter < current_pulse.time_mark_on) {
			LED_set(ON);
		}
	} else if ( led_state == ON ){
		if (time_counter >= current_pulse.time_mark_on) {
			LED_set(OFF);
		}
	}
}


