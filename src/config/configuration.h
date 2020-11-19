#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__
#include "../io/mem-map.h"
#include <stdbool.h>
typedef struct Config{
    int SCREEN_H;
    int SCREEN_W;
    _Bool SCREENSAVER_ENABLED;
    int BUTTON_1_X;
    int BUTTON_1_Y;
    int BUTTON_1_W;
    int BUTTON_1_H;
    int BUTTON_2_X;
    int BUTTON_2_Y;
    int BUTTON_2_W;
    int BUTTON_2_H;
    int BUTTON_3_X;
    int BUTTON_3_Y;
    int BUTTON_3_W;
    int BUTTON_3_H;
    int BUTTON_4_X;
    int BUTTON_4_Y;
    int BUTTON_4_W;
    int BUTTON_4_H;
    int BUTTON_5_X;
    int BUTTON_5_Y;
    int BUTTON_5_W;
    int BUTTON_5_H;
    int BUTTON_6_X;
    int BUTTON_6_Y;
    int BUTTON_6_W;
    int BUTTON_6_H;
    int BUTTON_7_X;
    int BUTTON_7_Y;
    int BUTTON_7_W;
    int BUTTON_7_H;
    int BUTTON_8_X;
    int BUTTON_8_Y;
    int BUTTON_8_W;
    int BUTTON_8_H;
    int BUTTON_9_X;
    int BUTTON_9_Y;
    int BUTTON_9_W;
    int BUTTON_9_H;
    int BUTTON_0_X;
    int BUTTON_0_Y;
    int BUTTON_0_W;
    int BUTTON_0_H;
    char* BUTTON_1_PATH;
    char* BUTTON_2_PATH;
    char* BUTTON_3_PATH;
    char* BUTTON_4_PATH;
    char* BUTTON_5_PATH;
    char* BUTTON_6_PATH;
    char* BUTTON_7_PATH;
    char* BUTTON_8_PATH;
    char* BUTTON_9_PATH;
    char* BUTTON_0_PATH;
} config;

struct Config* ParseConfig(char* path);
#endif