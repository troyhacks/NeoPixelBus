/*-------------------------------------------------------------------------
NeoMethods includes all the classes that describe pulse/data sending methods using
bitbang, SPI, or other platform specific hardware peripheral support.  

Written by Michael C. Miller.

I invest time and resources providing this open source code,
please support me by donating (see https://github.com/Makuna/NeoPixelBus)

-------------------------------------------------------------------------
This file is part of the Makuna/NeoPixelBus library.

NeoPixelBus is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

NeoPixelBus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with NeoPixel.  If not, see
<http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------*/
#pragma once

// helper constants for method speeds and invert
#include "methods/NeoBits.h"

// Generic Two Wire (clk and data) methods
//
#include "methods/DotStarGenericMethod.h"
#include "methods/Lpd8806GenericMethod.h"
#include "methods/Lpd6803GenericMethod.h"
#include "methods/Ws2801GenericMethod.h"
#include "methods/P9813GenericMethod.h"
#include "methods/Tlc5947GenericMethod.h"
#include "methods/Tlc59711GenericMethod.h"
#include "methods/Sm16716GenericMethod.h"
#include "methods/Mbi6033GenericMethod.h"
#include "methods/Hd108GenericMethod.h"

//Adafruit Pixie via UART, not platform specific
//
#include "methods/PixieStreamMethod.h"

// Platform specific and One Wire (data) methods
//
#if defined(ARDUINO_ARCH_ESP8266)

#include "methods/ESP/ESP8266/NeoEsp8266DmaMethod.h"
#include "methods/ESP/ESP8266/NeoEsp8266I2sDmx512Method.h"
#include "methods/ESP/ESP8266/NeoEsp8266UartMethod.h"
#include "methods/ESP/NeoEspBitBangMethod.h"

#elif defined(ARDUINO_ARCH_ESP32)

#if ESP_IDF_VERSION_MAJOR < 5

#include "methods/ESP/ESP32/Core_2_x/NeoEsp32RmtMethod.h"

#else // ESP_IDF_VERSION_MAJOR < 5

#define NEOPIXEL_ESP32_RMT_DEFAULT  // core3 will have RMT default, maybe change after an updated i2s

#if !defined(CONFIG_IDF_TARGET_ESP32C2)
#include "methods/ESP/ESP32/NeoEsp32RmtXMethod.h" // every other SOC
#else //CONFIG_IDF_TARGET_ESP32C2
#include "methods/ESP/ESP32/NeoEsp32SpiMethod.h" // ESP32C2
#endif //CONFIG_IDF_TARGET_ESP32C2

#endif // ESP_IDF_VERSION_MAJOR < 5

// once we have a core3 i2s, then fix this
#if !defined(CONFIG_IDF_TARGET_ESP32C6) && !defined(CONFIG_IDF_TARGET_ESP32H2)
#include "methods/ESP/ESP32/Core_2_x/NeoEsp32I2sMethod.h"
#include "methods/ESP/ESP32/Core_2_x/NeoEsp32I2sXMethod.h"
#endif

#include "methods/ESP/ESP32/DotStarEsp32DmaSpiMethod.h"
#include "methods/ESP/ESP32/NeoEsp32LcdXMethod.h"


#include "methods/ESP/NeoEspBitBangMethod.h"

#elif defined(ARDUINO_ARCH_NRF52840) // must be before __arm__

#include "methods/ARM/NeoNrf52xMethod.h"

#elif defined(ARDUINO_ARCH_RP2040) // must be before __arm__

#include "methods/RP2040/NeoRp2040x4Method.h"

#elif defined(__arm__) // must be before ARDUINO_ARCH_AVR due to Teensy incorrectly having it set

#include "methods/ARM/NeoArmMethod.h"

#elif defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

#include "methods/AVR/NeoAvrMethod.h"

#else
#error "Platform Currently Not Supported, please add an Issue at Github/Makuna/NeoPixelBus"
#endif
