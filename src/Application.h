/*
The MIT License (MIT)

Copyright (c) 2020-2025 riraosan.github.io

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
#include <M5Unified.h>
#include <Button2.h>
#include <esp32-hal-log.h>

class Application {
 public:
  Application() {
  }

  static void avrc_rn_play_pos_callback(uint32_t play_pos) {
    log_i("Play position is %d (%d seconds)\n", play_pos, (int)round(play_pos / 1000.0));
  }

  static void avrc_rn_playstatus_callback(esp_avrc_playback_stat_t playback) {
    switch (playback) {
      case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_STOPPED:
        log_i("Stopped.");
        break;
      case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PLAYING:
        log_i("Playing.");
        break;
      case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PAUSED:
        log_i("Paused.");
        break;
      case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_ERROR:
        log_e("Error.");
        break;
      default:
        log_e("Got unknown playback status %d\n", playback);
    }
  }

  static void avrc_metadata_callback(uint8_t id, const uint8_t* text) {
    // log_i("==> AVRC metadata rsp");

    switch (id) {
      case 0x01:
        log_i("==>　曲名：%s", text);
        M5.Display.setCursor(0, 0);
        M5.Display.fillScreen(TFT_BLACK);
        M5.Display.printf("曲名：");
        M5.Display.println((char*)text);
        M5.Display.println();
        break;
      case 0x02:
        log_i("==>　アーティスト：%s", text);
        M5.Display.printf("アーティスト：");
        M5.Display.println((char*)text);
        M5.Display.println();
        break;
      case 0x04:
        log_i("==>　アルバム名：%s", text);
        M5.Display.printf("アルバム名：");
        M5.Display.println((char*)text);
        M5.Display.println();
        break;
      case 0x20:
        log_i("==>　ジャンル：%s", text);
        M5.Display.printf("ジャンル：");
        M5.Display.println((char*)text);
        M5.Display.println();
        break;
      default:
        // log_i("==>　Unknown：%s", text);
        break;
    }
  }

  static void on_data_receive_callback(void) {
    static int count;
    if (++count % 100 == 0) {
      // M5.dis.drawpix(0, 0x00FF00);
    } else {
      // M5.dis.drawpix(0, 0x000000);
    }
  }
#ifdef TEST
  BluetoothA2DPSink* getA2DPSink(void) {
    return &_a2dp_sink;
  }
#endif
  void initButtons(void) {
    _buttonA.begin(39);

    _buttonA.setClickHandler([this](Button2& b) {
      log_w("Button A Clicked");
      switch (_a2dp_sink.get_audio_state()) {
        case ESP_A2D_AUDIO_STATE_STARTED:
          log_w("Stop");
          _a2dp_sink.stop();
          break;
        case ESP_A2D_AUDIO_STATE_STOPPED:
        case ESP_A2D_AUDIO_STATE_REMOTE_SUSPEND:
          log_w("Play");
          _a2dp_sink.play();
          break;
        default:
          break;
      }
    });
  }

  void setup(void) {
    M5.begin();
    initButtons();

    M5.Display.setFont(&fonts::lgfxJapanGothicP_16);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Display.setCursor(0, 0);
    M5.Display.println("This is the Riraosan Player.");
    M5.Display.println("iPhoneより「Riraosan Player」に接続してください。");

    i2s_pin_config_t pin_config = {
        .bck_io_num   = 13,
        .ws_io_num    = 0,
        .data_out_num = 15,
        .data_in_num  = I2S_PIN_NO_CHANGE  // Use in i2s_pin_config_t for pins which should not be changed
    };

    // Settings for 32bit DAC Board
    i2s_config_t i2s_config = {
        .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate          = 44100,                       // corrected by info from bluetooth
        .bits_per_sample      = (i2s_bits_per_sample_t)16,   // set_bits_per_sample()
        .channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT,  // 2-channels
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,   // I2S communication format I2S
        .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,        // default interrupt priority
        .dma_buf_count        = 8,                           // default
        .dma_buf_len          = 64,                          // default
        .use_apll             = false,                       // I2S using APLL as main I2S clock, enable it to get accurate clock
        .tx_desc_auto_clear   = true                         // I2S auto clear tx descriptor if there is underflow condition
    };

    _a2dp_sink.set_pin_config(pin_config);
    _a2dp_sink.set_i2s_config(i2s_config);
    _a2dp_sink.set_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT);  // for I2S : PCM 44.1K-384K 32BIT

    _a2dp_sink.set_avrc_rn_playstatus_callback(avrc_rn_playstatus_callback);
    _a2dp_sink.set_avrc_rn_play_pos_callback(avrc_rn_play_pos_callback);
    _a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);

    _a2dp_sink.start("Riraosan Player", false);
  }

  void update(void) {
    _buttonA.loop();

    delay(10);
  }

 private:
  BluetoothA2DPSink _a2dp_sink;
  Button2 _buttonA;
};
