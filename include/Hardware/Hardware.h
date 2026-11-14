#pragma once

class Hardware {
public:
    // intialising all the GPIO pins for the OLED SPI display
    static constexpr int CLK_PIN = 22;
    static constexpr int SDA_PIN = 21;
    static constexpr int RES_PIN = 19;
    static constexpr int DC_PIN = 18;
    static constexpr int CS_PIN = 23;

    // intialising all the GPIO pins for the ADC's SPI communication
    static constexpr int CS2_PIN = 27;
    static constexpr int DOUT_PIN = 13;
    static constexpr int CLK2_PIN = 14;

    // other pins
    static constexpr int MENU_PIN = 26;
    static constexpr int MENU_SCROLL_PIN = 25;
    static constexpr int VSCALE_PIN = 33;

    void PinSetup();
};