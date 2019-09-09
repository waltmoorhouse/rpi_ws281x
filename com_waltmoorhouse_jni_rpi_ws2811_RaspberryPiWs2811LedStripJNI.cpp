//
// Created by Walt Moorhouse on 9/5/19.
//

#include "build/generated/com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI.h"
#include "java.h"
#include <cstring>
#include <iomanip>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ws2811.h"

#ifdef __cplusplus
}
#endif

ws2811_t ledString =
    {
        .freq = WS2811_TARGET_FREQ,
        .dmanum = 10,
        .channel =
            {
                [0] =
                    {
                        .gpionum = 18,
                        .invert = 0,
                        .count = 30,
                        .strip_type = WS2811_STRIP_RGB,
                        .brightness = 255,
                    },
                [1] =
                    {
                        .gpionum = 0,
                        .invert = 0,
                        .count = 0,
                        .brightness = 0,
                    },
            },
    };

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    initInternal
 * Signature: (IIIIIIZ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_initInternal
        (JNIEnv * env, jobject jobj, jstring jStripType, jint ledCount, jint gpioPin, jint frequencyHz, jint dma,
                jint brightness, jint pwmChannel, jboolean invert) {

    ledString.freq = frequencyHz;
    ledString.dmanum = dma;
    ledString.channel[0].gpionum = gpioPin;
    ledString.channel[0].count = ledCount;
    ledString.channel[0].invert = invert;
    ledString.channel[0].brightness = brightness;
    const char *stripType = env->GetStringUTFChars(jStripType, 0);
    if (!strcmp("RGB", stripType)) {
        ledString.channel[0].strip_type = WS2811_STRIP_RGB;
    }
    else if (!strcmp("RBG", stripType)) {
        ledString.channel[0].strip_type = WS2811_STRIP_RBG;
    }
    else if (!strcmp("GRB", stripType)) {
        ledString.channel[0].strip_type = WS2811_STRIP_GRB;
    }
    else if (!strcmp("GBR", stripType)) {
        ledString.channel[0].strip_type = WS2811_STRIP_GBR;
    }
    else if (!strcmp("BRG", stripType)) {
        ledString.channel[0].strip_type = WS2811_STRIP_BRG;
    }
    else if (!strcmp("BGR", stripType)) {
        ledString.channel[0].strip_type = WS2811_STRIP_BGR;
    }
    else if (!strcmp("RGBW", stripType)) {
        ledString.channel[0].strip_type = SK6812_STRIP_RGBW;
    }
    else if (!strcmp("GRBW", stripType)) {
        ledString.channel[0].strip_type = SK6812_STRIP_GRBW;
    }
    env->ReleaseStringUTFChars(jStripType, stripType);

    return env->NewStringUTF(ws2811_get_return_t_str(ws2811_init(&ledString)));
}

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    setPixel
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_setPixel__ILjava_lang_String_2
(JNIEnv * env, jobject jobj, jint led, jstring hexVal){
    ledString.channel[0].leds[led] = convertHexToLEDvalue(env, hexVal);
}

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    setPixel
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_setPixel__IIII
(JNIEnv * env, jobject jobj, jint led, jint red, jint green, jint blue) {
    ledString.channel[0].leds[led] = convertRGBtoLEDvalue(red, green, blue);
}

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    setStrip
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_setStrip__Ljava_lang_String_2
(JNIEnv * env, jobject jobj, jstring hexVal) {
    int numLeds = ledString.channel[0].count;
    ws2811_led_t color = convertHexToLEDvalue(env, hexVal);

    for (int i=0; i<numLeds; i++) {
        ledString.channel[0].leds[i] = color;
    }
}

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    setStrip
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_setStrip__III
(JNIEnv * env, jobject jobj, jint red, jint green, jint blue) {
    int numLeds = ledString.channel[0].count;
    ws2811_led_t color = convertRGBtoLEDvalue(red, green, blue);

    for (int i=0; i<numLeds; i++) {
        ledString.channel[0].leds[i] = color;
    }
}

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    render
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_render
        (JNIEnv * env, jobject jobj) {
    return env->NewStringUTF(ws2811_get_return_t_str(ws2811_render(&ledString)));
}

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    clear
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_clear
        (JNIEnv * env, jobject jobj) {
    int numLeds = ledString.channel[0].count;

    for (int i=0; i<numLeds; i++) {
        ledString.channel[0].leds[i] = 0;
    }
    return env->NewStringUTF(ws2811_get_return_t_str(ws2811_render(&ledString)));
}

/*
 * Class:     com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI
 * Method:    disconnect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_waltmoorhouse_jni_rpi_ws2811_RaspberryPiWs2811LedStripJNI_disconnect
(JNIEnv * env, jobject jobj) {
    ws2811_fini(&ledString);
}

ws2811_led_t convertHexToLEDvalue(JNIEnv * env, jstring hexVal) {
    ws2811_led_t colorValue;
    std::stringstream colorStream;
    const char *hexValString = env->GetStringUTFChars(hexVal, 0);
    colorStream << hexValString;
    colorStream >> std::hex >> colorValue;
    return colorValue;
}

ws2811_led_t convertRGBtoLEDvalue(jint red, jint green, jint blue) {
    ws2811_led_t colorValue;
    std::stringstream colorStream, redStream, blueStream, greenStream;
    redStream << std::setfill ('0') << std::setw(2) << std::hex << red;
    greenStream << std::setfill ('0') << std::setw(2) << std::hex << green;
    blueStream << std::setfill ('0') << std::setw(2) << std::hex << blue;
    colorStream << redStream.str() << greenStream.str() << blueStream.str();
    colorStream >> std::hex >> colorValue;
    return colorValue;
}