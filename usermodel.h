
#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "settingmodel.h"


class UserModel {

public:
    static int uid;

    static QVariantMap getSetting();
};


#endif //USER_MODEL_H
