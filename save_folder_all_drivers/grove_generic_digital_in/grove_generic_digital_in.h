/*
 * grove_generic_digital_in.h
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


#ifndef __GROVE_GENERIC_DIGITAL_IN_H__
#define __GROVE_GENERIC_DIGITAL_IN_H__

#include "suli2.h"

//GROVE_NAME        "Generic Digital Input"
//SKU               7e3306bc-8911-11e5-af63-feff819cdc9f
//IF_TYPE           GPIO
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/wio_generic_din.png
//DESCRIPTION       "The Grove Generic Digital In check the digital input signal. It can connect to another device such as Arduino, Raspberry Pi and so on. It also push a Event when digital input change."
//WIKI_URL          https://github.com/Seeed-Studio/Grove_Drivers_for_Wio/wiki/Grove_Generic_Digital_In
//ADDED_AT          "2015-12-01"
//AUTHOR            "SEEED"

class GenericDIn
{
public:
    GenericDIn(int pin);

    /**
     * Read the input state of a generic digital input device
     *
     * @param input - 1: on, 0: off
     *
     * @return bool
     */
    bool read_input(uint8_t *input);

    /**
     * Read the count of rising edges since last read.
     *
     * @param rises - the count of rising edges
     *
     * @return bool
     */
    bool read_edge_rise_since_last_read(uint32_t *rises);

    /**
     * Read the count of falling edges since last read.
     *
     * @param falls - the count of falling edges
     *
     * @return bool
     */
    bool read_edge_fall_since_last_read(uint32_t *falls);

    /**
     * From "Generic Digital Input", triggered when the state of the PIN changed.
     * Event data is the number of the PIN to which the grove is attached
     */
    DEFINE_EVENT(input_changed, SULI_EDT_INT);
    /**
     * From "Generic Digital Input", triggered when the level of the PIN rised.
     */
    DEFINE_EVENT(input_rise, SULI_EDT_INT);
    /**
     * From "Generic Digital Input", triggered when the level of the PIN fell.
     */
    DEFINE_EVENT(input_fall, SULI_EDT_INT);


    IO_T *io;
    uint32_t time;
    uint32_t cnt_rise, cnt_fall;
};

static void input_changed_interrupt_handler(void *para);

#endif
