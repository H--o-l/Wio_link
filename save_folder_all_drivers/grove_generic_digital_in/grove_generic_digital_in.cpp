/*
 * grove_generic_digital_in.cpp
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

#include "suli2.h"
#include "grove_generic_digital_in.h"



GenericDIn::GenericDIn(int pin)
{
    this->io = (IO_T *)malloc(sizeof(IO_T));

    suli_pin_init(io, pin, SULI_INPUT);
    time = millis();
    cnt_rise = cnt_fall = 0;

    suli_pin_attach_interrupt_handler(io, &input_changed_interrupt_handler, SULI_CHANGE, this);
}

bool GenericDIn::read_input(uint8_t *input)
{
    *input = suli_pin_read(io);
    return true;
}

bool GenericDIn::read_edge_rise_since_last_read(uint32_t *rises)
{
    *rises = cnt_rise;
    cnt_rise = 0;
    return true;
}

bool GenericDIn::read_edge_fall_since_last_read(uint32_t *falls)
{
    *falls = cnt_fall;
    cnt_fall = 0;
    return true;
}

static void input_changed_interrupt_handler(void *para)
{
    GenericDIn *g = (GenericDIn *)para;
    if (millis() - g->time < 100)
    {
        return;
    }
    g->time = millis();

    POST_EVENT_IN_INSTANCE(g, input_changed, g->io);

    if (suli_pin_read(g->io))
    {
        g->cnt_rise++;
        POST_EVENT_IN_INSTANCE(g, input_rise, g->io);
    } else
    {
        g->cnt_fall++;
        POST_EVENT_IN_INSTANCE(g, input_fall, g->io);
    }
}

