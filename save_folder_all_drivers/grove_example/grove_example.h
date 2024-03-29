/*
 * grove_example.h
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao (jacky.shaoxg@gmail.com)
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef __GROVE_EXAMPLE_H__
#define __GROVE_EXAMPLE_H__

#include "suli2.h"

//GROVE_NAME        "Grove_Example"
//SKU               71714fec-8911-11e5-af63-feff819cdc9f
//IF_TYPE           GPIO
//IMAGE_URL         http://www.seeedstudio.com/depot/includes/templates/bootstrap/images/ico/grove.png
//DESCRIPTION       "The Grove Example is test driver for develop, not public."
//WIKI_URL          https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Grove_Example
//ADDED_AT          "2015-09-01"
//AUTHOR            "SEEED"

class GroveExample
{
public:
    GroveExample(int pin);

    bool on_power_on();
    bool on_power_off();


    /**
     * This is the comment for read_temp, with the format showed here
     * Multipul lines are allowed.
     *
     * @param temp - desc for this variable
     *
     * @return bool
     */
    bool read_temp(int *temp);
    bool read_uint8_value(uint8_t *value);
    bool read_humidity(float *humidity);
    bool read_acc(float *ax, float *ay, float *az);
    bool read_compass(float *cx, float *cy, float *cz, int *degree);
    bool read_with_arg(float *cx, float *cy, float *cz, int *degree, int arg);

    /**
     * This is the description for write_acc_mode.
     *
     * @param mode - desc for param mode
     *
     * @return bool
     */
    bool write_acc_mode(uint8_t mode);
    bool write_float_value(float f);
    bool write_multi_value(int a, float b, uint32_t c);

    /**
     * This is the description for event 'fire'
     * Multipul lines are allowed.
     */
    DEFINE_EVENT(fire, SULI_EDT_INT);

    /**
     * This is the description for event 'event2'
     * Multipul lines are allowed.
     */
    DEFINE_EVENT(event2, SULI_EDT_INT);

    char *get_last_error() { return error_desc; };

    IO_T *io;
    TIMER_T *timer;
    TIMER_T *timer1;
    UART_T *debug_serial;
    int var;


    void _internal_function(int x);
    void _event_poster();

private:
    char *error_desc;
};

static void pin_interrupt_handler(void *para);
static void timer_handler(void *para);
static void timer1_handler(void *para);

#endif
