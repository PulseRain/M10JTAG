/*
###############################################################################
# Copyright (c) 2017, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License (LGPL) as 
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################
*/

#ifndef M10JTAG_H
#define M10JTAG_H

#include "Arduino.h"

typedef struct {
   void (*_print) (int32_t num, uint8_t fmt) __reentrant;
   void (*_println) (int32_t data, uint8_t fmt) __reentrant;
   void (*_write) (uint8_t* buf, uint16_t length) __reentrant;
} JTAG_UART_STRUCT;

extern const JTAG_UART_STRUCT JTAG;

#endif
