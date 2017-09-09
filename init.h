
#ifndef INIT_H
#define INIT_H


class Init
{
public:
    Init();
    ~Init();

    bool succeed();

    qint32 errCode;
    QString errMsg;

    //static QString const name = "番茄倒计时";
    //static char[] * name = "番茄倒计时";

    QString name = "番茄倒计时";

private:
    bool m_success = false;
};


#endif //INIT_H
#ifndef INIT_H
#define INIT_H


class Init
{
public:
    Init();
};

#endif // INIT_H
