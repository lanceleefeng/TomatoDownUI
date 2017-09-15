#include "config.h"

#ifndef QT_NO_DEBUG
bool Config::isDebug = false;
#else
bool Config::isDebug = true;
#endif

// 也可以
/*

#if defined(QT_NO_DEBUG)
bool Config::isDebug = false;
#else
bool Config::isDebug = true;
#endif

*/

QString Config::appName = "番茄倒计时";

int Config::width = 500;
int Config::height = 350;

/**
 * autoStart:           自动开始，启动后是否自动开始计时，默认 true
 * countDown:           倒计时，true 倒计时，false 正计时, 默认 true
 * autoHide:            自动隐藏，开始计时后自动隐藏窗口，默认 true
 * autoHideDelay:       延时，自动隐藏延时指定时间（毫秒），默认 300毫秒
 * autoHideFirstRun:    首次运行是否隐藏，true 隐藏，false 不隐藏，默认 false

 * singleWindow:        单窗口，只允许运行一个番茄倒计时窗口，默认 true，
 *                      不提供该选项，限制只能运行一个窗口 2017-9-15 23:02:36
 */
QMap<QString, QVariant> Config::defaultSetting = {
    //{"autoStart", false},
    {"autoStart", true},
    {"countDown", true},
    {"autoHide", true},
    //{"autoHideDelay", 300},
    //{"autoHideDelay", 600},
    //{"autoHideDelay", 1200},
    //{"autoHideDelay", 1000},
    {"autoHideDelay", 0},
    {"autoHideFirstRun", false},
    //{"singleWindow", true},
};


QString Config::defaultTimerKey = "walking";

int Config::progressMinValue = 30;
