/*
 * grove_temp.cpp
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
#include "grove_temp.h"
#include "math.h"

GroveTemp::GroveTemp(int pin)
{
    this->io = (ANALOG_T *)malloc(sizeof(ANALOG_T));

    suli_analog_init(io, pin);
}

bool GroveTemp::read_temp(float *temperature)
{
    int B=4275;                  //B value of the thermistor NCP18WF104F03RC
    int R0 = 100000;
    float R;

    float v = suli_analog_voltage(io);
    if (v == 0.0f) v = 0.000001f;

    R = (float)(SULI_PLATFORM_VCC / v - 1) * R0; //get the resistance of the sensor;

    *temperature = 1 / (log(R / R0) / B + 1 / 298.15) - 273.15; //convert to temperature via datasheet ;

    return true;
}

