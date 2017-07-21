/*
 * leds.h
 *
 *  Created on: Jul 21, 2017
 *      Author: F27284C
 */

#ifndef LEDS_H_
#define LEDS_H_


void back_light_on(void);
void back_light_off(void);
void back_light_toggle(void);

void high_beam_on(void);
void high_beam_off(void);
void high_beam_toggle(void);

void low_beam_on(void);
void low_beam_off(void);
void low_beam_toggle(void);

void turn_indicator_on(void);
void turn_indicator_off(void);
void turn_indicator_toggle(void);

void dlr_on(void);
void dlr_on_turn_indicator(void);
void dlr_off(void);
void dlr_dimming(uint32_t pwm);
void dlr_toggle(void);

#endif /* LEDS_H_ */
