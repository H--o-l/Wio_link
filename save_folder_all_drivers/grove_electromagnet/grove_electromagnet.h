/*
 * grove_electromagnet.h
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


#ifndef __GROVE_ELECMAGNET_H__
#define __GROVE_ELECMAGNET_H__

#include "suli2.h"

//GROVE_NAME        "Grove-Electromagnet"
//SKU               101020073
//IF_TYPE           GPIO
//IMAGE_URL         https://raw.githubusercontent.com/Seeed-Studio/Grove_Drivers_for_Wio/static/images/grove-electromagnet.jpg
//DESCRIPTION       "Grove - Electromagnet is a type of magnet in which the magnetic field is produced by electric current and it can shuck 1KG weight and hold on."
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Electromagnet/
//ADDED_AT          "2015-10-01"
//AUTHOR            "SEEED"

class GroveElecMagnet
{
public:
    GroveElecMagnet(int pin);

    /**
     *
     *
     * @param onoff - 1: on/generate electromagnetism, 0: off
     *
     * @return bool
     */
    bool write_onoff(int onoff);

    /**
     * Read back the status of relay
     *
     * @param onoff - 1: on/high, 0: off/low
     *
     * @return bool
     */
    bool read_onoff_status(int *onoff);

private:
    IO_T *io;
};


#endif
