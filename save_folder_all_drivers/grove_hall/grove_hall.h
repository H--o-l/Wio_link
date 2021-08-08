/*
 * grove_hall.h
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


#ifndef __GROVE_HALL_H__
#define __GROVE_HALL_H__

#include "suli2.h"

//GROVE_NAME        "Grove - Hall Sensor"
//SKU               101020046
//IF_TYPE           GPIO
//IMAGE_URL         https://statics3.seeedstudio.com/images/product/hall%20sensor.jpg
//DESCRIPTION       "The Hall Sensor measures the Hall Effect, which is a production of a voltage difference across an electrical conductor, transverse to an electric current in the conductor as well as a magnetic field perpendicular to the current."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Hall_Sensor/
//ADDED_AT          "2016-09-21"
//AUTHOR            "SEEED"

class GroveHall
{
public:
    GroveHall(int pin);

    /**
     * Read the state of the VOUT pin of this sensor.
     *
     * @param vout - 1: on, 0: off
     *
     * @return bool
     */
    bool read_vout(uint8_t *vout);

    /**
     * From "Grove - Hall Sensor", triggered when magnetic field being perpendicular to the Hall sensor.
     * Event data is the number of the PIN to which the grove is attached
     */
    DEFINE_EVENT(state_on, SULI_EDT_INT);

    /**
     * From "Grove - Hall Sensor", triggered when magnetic field disappears.
     */
    DEFINE_EVENT(state_off, SULI_EDT_INT);

    IO_T *io;
    uint32_t time;
};

static void hall_state_change_interrupt_handler(void *para);

#endif
