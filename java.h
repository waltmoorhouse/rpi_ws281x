//
// Created by Walt Moorhouse on 9/5/19.
//

#ifndef WS281X_JNI_SUPPORT_H
#define WS281X_JNI_SUPPORT_H

typedef unsigned char               uint8_t;
typedef unsigned short int          uint16_t;
#ifndef __uint32_t_defined
typedef unsigned int                uint32_t;
# define __uint32_t_defined
#endif
#if __WORDSIZE == 64
typedef unsigned long int           uint64_t;
#else
__extension__
typedef unsigned long long int      uint64_t;
#endif

typedef uint32_t                    ws2811_led_t;

ws2811_led_t convertRGBtoLEDvalue(jint, jint, jint);

#endif //WS281X_JNI_SUPPORT_H
