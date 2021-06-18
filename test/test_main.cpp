
#include <Application.h>
#include <unity.h>

#include <memory>
// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void expand_bit_per_sample_test01(void) {
    std::unique_ptr<Application> pApp(new Application);
    pApp->setup();
    pApp->getA2DPSink()->set_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT);
    delay(10 * 1000);
    //To connect iPhone

    pApp.reset();
}

void expand_bit_per_sample_test02(void) {
    std::unique_ptr<Application> pApp(new Application);
    pApp->setup();
    pApp->getA2DPSink()->set_bits_per_sample(I2S_BITS_PER_SAMPLE_24BIT);
    delay(10 * 1000);
    //To connect iPhone

    pApp.reset();
}

void expand_bit_per_sample_test03(void) {
    std::unique_ptr<Application> pApp(new Application);
    pApp->setup();
    pApp->getA2DPSink()->set_bits_per_sample(I2S_BITS_PER_SAMPLE_32BIT);
    delay(10 * 1000);
    //To connect iPhone

    pApp.reset();
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();  // IMPORTANT LINE!
/*
    delay(2000);
    RUN_TEST(expand_bit_per_sample_test01);  //NG (because by Noise at ES9038Q2M VR1.07 DAC Board)

    delay(2000);
    RUN_TEST(expand_bit_per_sample_test02);  //NG (because by Noise at ES9038Q2M VR1.07 DAC Board)
*/
    delay(2000);
    RUN_TEST(expand_bit_per_sample_test03);  //OK (because by Clear Music Sound at ES9038Q2M VR1.07 DAC Board)

    UNITY_END();  // stop unit testing
}

void loop() {
}
