#include "config.h"

#ifdef QT_NO_DEBUG
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

// QMap会根据键自动排序，看来得用list
//QMap<QString, QString> Config::languages = {
//    {"en_us","English"},
//    {"zh_cn", "简体中文"},
//    {"zh_tw", "繁體中文"},
//};


QStringList Config::languages = {
    "en_us", "zh_cn", "zh_tw",
};

QStringList Config::languageNames = {
    "English", "中文（简体）", "中文（繁體）",
};


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

    {"language", "en_us"},
    //{"language", "zh_cn"},
    //{"language", "zh_tw"},

    //{"autoStart", false},
    {"autoStart", true},

    {"countDown", true},

    //{"autoHide", false},
    {"autoHide", true},

    //{"autoHideDelay", 300},
    //{"autoHideDelay", 600},
    //{"autoHideDelay", 1200},
    //{"autoHideDelay", 1000},
    {"autoHideDelay", 0},
    {"firstRunHide", false},
    //{"singleWindow", true},
    {"tomatoTime", "25"},
    {"tipTime", "3"},
    {"breakTime", "5"},
};


QString Config::defaultTimerKey = "walking";

// ctrl+shift+S 造成按键时切换输入法..
QMap<QString, QString> Config::hotKeys = {
    {"tick", "ctrl+alt+S"},
    {"break", "ctrl+alt+Z"},
};

int Config::progressMinValue = 30;

QMap<QString, int> Config::delayedTime = {
    {"saveSetting", 500},
};

