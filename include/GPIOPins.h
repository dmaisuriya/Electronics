#pragma once

namespace Pins {
    // intialising all the GPIO pins for the OLED SPI display
    constexpr int CLK_PIN = 22;
    constexpr int SDA_PIN = 21;
    constexpr int RES_PIN = 19;
    constexpr int DC_PIN = 18;
    constexpr int CS_PIN = 23;

    // intialising all the GPIO pins for the ADC's SPI communication
    constexpr int CS2_PIN = 27;
    constexpr int DOUT_PIN = 13;
    constexpr int CLK2_PIN = 14;
}
