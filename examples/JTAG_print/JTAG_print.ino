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

//============================================================================
// Example:
//    JTAG UART demonstration. To use this example, you need to open a 
// NIOS II command shell and run nios2-terminal.exe.
//    Please note that by default, the JTAG UART has a FIFO depth of 16. 
//============================================================================


//============================================================================
// setup()
//============================================================================

void setup() {

} // End of setup()


//============================================================================
// loop()
//============================================================================

uint8_t start_value = 0;

void loop() {
  JTAG.write("JTAG loop: ");
  JTAG.println(start_value);
  ++start_value;
  delay (1000);
} // End of loop()
