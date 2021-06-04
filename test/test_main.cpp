
#include <Application.h>
#include <unity.h>

#include <memory>
// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void expand_audio_bits_per_sample_test(void) {
    std::unique_ptr<Application> pApp(new Application);

    BluetoothA2DPSink* a2dpSink = pApp->getA2DPSink();

    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_8BIT, I2S_BITS_PER_SAMPLE_8BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT, I2S_BITS_PER_SAMPLE_8BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_24BIT, I2S_BITS_PER_SAMPLE_8BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT, I2S_BITS_PER_SAMPLE_8BIT);

    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_8BIT, I2S_BITS_PER_SAMPLE_16BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT, I2S_BITS_PER_SAMPLE_16BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_24BIT, I2S_BITS_PER_SAMPLE_16BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT, I2S_BITS_PER_SAMPLE_16BIT);

    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_8BIT, I2S_BITS_PER_SAMPLE_24BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT, I2S_BITS_PER_SAMPLE_24BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_24BIT, I2S_BITS_PER_SAMPLE_24BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT, I2S_BITS_PER_SAMPLE_24BIT);

    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_8BIT, I2S_BITS_PER_SAMPLE_32BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT, I2S_BITS_PER_SAMPLE_32BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_24BIT, I2S_BITS_PER_SAMPLE_32BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT, I2S_BITS_PER_SAMPLE_32BIT);

    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_8BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_24BIT);
    a2dpSink->expand_audio_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT);

    pApp.reset();
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS(ボードがsoftwareリセットに対応していない場合に必要なdelay．)
    delay(2000);

    UNITY_BEGIN();  // IMPORTANT LINE!

    RUN_TEST(expand_audio_bits_per_sample_test);

    UNITY_END();  // stop unit testing
}

void loop() {
    ;
}
