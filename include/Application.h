/*
The MIT License (MIT)

Copyright (c) 2020-2021 riraosan.github.io

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Arduino.h>
#include <BluetoothA2DPSink.h>
#include <esp32-hal-log.h>

class Application {
   public:
    Application() {
        //init...
    }

    ~Application() {}

    static void avrc_metadata_callback(uint8_t id, const uint8_t* text) {
        log_i("==> AVRC metadata rsp: attribute id 0x%x, %s\n", id, text);
    }

    static void on_data_receive_callback(void) {
        static int count;
        if (++count % 100 == 0) {
            digitalWrite(_BLUE_LED_PORT, HIGH);
        } else {
            digitalWrite(_BLUE_LED_PORT, LOW);
        }
    }
#ifdef TEST
    BluetoothA2DPSink* getA2DPSink(void) {
        return &_a2dp_sink;
    }
#endif
    void setup(void) {
        pinMode(_BLUE_LED_PORT, OUTPUT);
        pinMode(_GREEN_LED_PORT, OUTPUT);

        i2s_pin_config_t pin_config = {
            .bck_io_num   = 26,
            .ws_io_num    = 22,
            .data_out_num = 25,
            .data_in_num  = I2S_PIN_NO_CHANGE  //Use in i2s_pin_config_t for pins which should not be changed
        };

        //Settings for ES9038Q2M VR1.07 DAC Board(eBay item number:263908779821)
        i2s_config_t i2s_config = {
            .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
            .sample_rate          = 44100,                       // corrected by info from bluetooth
            .bits_per_sample      = (i2s_bits_per_sample_t)0,    // set expand_audio_bits_per_sample()
            .channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT,  // 2-channels
            .communication_format = I2S_COMM_FORMAT_I2S,         // I2S communication format I2S
            .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,        // default interrupt priority
            .dma_buf_count        = 8,                           // default
            .dma_buf_len          = 64,                          // default
            .use_apll             = false,                       // I2S using APLL as main I2S clock, enable it to get accurate clock
            .tx_desc_auto_clear   = true                         // I2S auto clear tx descriptor if there is underflow condition
        };

        _a2dp_sink.set_pin_config(pin_config);
        _a2dp_sink.set_i2s_config(i2s_config);
        _a2dp_sink.expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT);  //for I2S : PCM 44.1K-384K 32BIT
        _a2dp_sink.set_on_data_received(on_data_receive_callback);
        _a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
        _a2dp_sink.start("Riraosan Player", true);
    }

    void handle(void) {
        if (_a2dp_sink.get_audio_state() == ESP_A2D_AUDIO_STATE_STARTED) {
            delay(1000);
            log_i("changing state...");
        }
    }

   private:
    BluetoothA2DPSink _a2dp_sink;
    constexpr static int _BLUE_LED_PORT  = 32;
    constexpr static int _GREEN_LED_PORT = 33;
};
