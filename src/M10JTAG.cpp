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

#include "M10JTAG.h"


//----------------------------------------------------------------------------
// jtag_putchar()
//
// Parameters:
//      char_in   : char to be printed to the JTAG UART
//
// Return Value:
//      None
//
// Remarks:
//      function to print char to JTAG UART
//----------------------------------------------------------------------------
 
void jtag_putchar (uint8_t char_in)
{ 
    JTAG_UART = char_in;
    nop_delay (1);
} // End of jtag_putchar()


//----------------------------------------------------------------------------
// jtag_print_dec_S32()
//
// Parameters:
//      num : 32 bit signed value to be printed 
//
// Return Value:
//      None
//
// Remarks:
//      Function to print out 32 bit signed value to JTAG console
//----------------------------------------------------------------------------
static void jtag_print_dec_S32 (int32_t num)
{
    uint8_t i;
    uint8_t tmp [10];
    
    if (num < 0) {
        jtag_putchar ('-');
        num = ~num;
        ++num;
    }
    
    for (i = 0; i < 10; ++i) {
        tmp[i] = num % 10;
        num /= 10;
        if (num == 0) {
            break;
        }
    } // End of for loop        

    do {
        jtag_putchar (digital_to_ascii(tmp[i]));
    } while (i--);
    
} // End of jtag_print_dec_S32()


//----------------------------------------------------------------------------
// jtag_print_hex()
//
// Parameters:
//      num : 32 bit unsigned value to be printed 
//
// Return Value:
//      None
//
// Remarks:
//      Function to print out 32 bit unsigned value in hex format
//  to JTAG console
//----------------------------------------------------------------------------

static void jtag_print_hex (uint32_t num)
{
    uint8_t i;
    uint8_t tmp [8];
    
    for (i = 0; i < 8; ++i) {
        tmp[i] = (uint8_t)(num & 0xF);
       // EA = 0;
        num = num / 16;
       // EA = 1;
       //  __asm__ ("nop");
       
        if (num == 0) {
            break;
        }
    } // End of for loop        
    
    
    do {
        jtag_putchar (digital_to_ascii(tmp[i]));
    } while (i--);
        
} // End of jtag_print_hex()


//----------------------------------------------------------------------------
// jtag_print_oct()
//
// Parameters:
//      num : 32 bit unsigned value to be printed 
//
// Return Value:
//      None
//
// Remarks:
//      Function to print out 32 bit unsigned value in octal format
//  to JTAG console
//----------------------------------------------------------------------------

static void jtag_print_oct (uint32_t num)
{
    uint8_t i;
    uint8_t tmp [11];
    
    for (i = 0; i < 11; ++i) {
        tmp[i] = (uint8_t)(num & 0x7);
        num = num / 8;
        if (num == 0) {
            break;
        }
    } // End of for loop
    
    do {
        jtag_putchar (digital_to_ascii(tmp[i]));
    } while (i--);
        
} // End of jtag_print_oct()


//----------------------------------------------------------------------------
// jtag_print_bin()
//
// Parameters:
//      num : 32 bit unsigned value to be printed 
//
// Return Value:
//      None
//
// Remarks:
//      Function to print out 32 bit unsigned value in binary format
//  to JTAG console
//----------------------------------------------------------------------------

static void jtag_print_bin (uint32_t num)
{
    uint8_t i;
    uint8_t tmp [32];
    
    for (i = 0; i < 32; ++i) {
        tmp[i] = (uint8_t)(num & 0x1);
        num = num / 2;
        if (num == 0) {
            break;
        }
    } // End of for loop        
    
    do {
        jtag_putchar (digital_to_ascii(tmp[i]));
    } while (i--);
        
} // End of jtag_print_bin()

//----------------------------------------------------------------------------
// jtag_print_int()
//
// Parameters:
//      num : 32 bit integer to be printed
//      fmt : DEC, HEX or OCT
//
// Return Value:
//      None
//
// Remarks:
//      Function to print out 32 bit integer value to JTAG console
//----------------------------------------------------------------------------

static void jtag_print_int (int32_t num, uint8_t fmt) __reentrant
{
    if (fmt == BIN) {
        jtag_print_bin((uint32_t) num);
    } else if (fmt == HEX) {
        jtag_print_hex((uint32_t) num);
    } else if (fmt == OCT) {
        jtag_print_oct ((uint32_t) num);
    } else {
        jtag_print_dec_S32 (num);    
    }
} // jtag_print_int()

//----------------------------------------------------------------------------
// jtag_printLn()
//
// Parameters:
//      num : 32 bit integer to be printed
//      fmt : DEC, HEX or OCT
//
// Return Value:
//      None
//
// Remarks:
//      Function to print out 32 bit integer value to JTAG console, plus 
//  a carriage return
//----------------------------------------------------------------------------

static void jtag_printLn(int32_t data, uint8_t fmt) __reentrant 
{
   jtag_print_int (data, fmt);
   //jtag_putchar ('\r');
   jtag_putchar ('\n');
} // End of jtag_printLn()

//----------------------------------------------------------------------------
// jtag_write()
//
// Parameters:
//      buf    : string to write to console
//      length : buffer size
//
// Return Value:
//      None
//
// Remarks:
//      Function to print out string buffer to JTAG console
//----------------------------------------------------------------------------

static void jtag_write (uint8_t* buf, uint16_t length)    
{
    if (length) {
        while (length) {
            jtag_putchar ((*buf++));
            --length;
        } // End of while loop
    } else {
        while (*buf) {
            jtag_putchar ((*buf++));
           
        } // End of while loop
    }
    
} // End of jtag_write()


//----------------------------------------------------------------------------
// jtag_write_reentrant()
//
// Parameters:
//      buf    : string to write to console
//      length : buffer size
//
// Return Value:
//      None
//
// Remarks:
//      Reentry function wrapper to jtag_write()
//----------------------------------------------------------------------------

static void jtag_write_reentrant (uint8_t* buf, uint16_t length) __reentrant
{
    jtag_write (buf, length);
    
} // End of jtag_write_reentrant()


//----------------------------------------------------------------------------
// JTAG_UART_STRUCT
//----------------------------------------------------------------------------


const JTAG_UART_STRUCT JTAG = {
  ._print = jtag_print_int,
  ._println = jtag_printLn,
  ._write = jtag_write_reentrant
};

