#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#include <QObject>

class RCommon : public QObject
{
    Q_OBJECT

public:
    enum CommonDefine {
        CD_NULL = 0,
        CD_START,
        CD_RUNNING,
        CD_PAUSE,
        CD_STOP,
        CD_MAX,
        CD_UNKNOWN,
    };
    Q_ENUM(CommonDefine);

    enum ExtraDefine {
        ED_NULL = 10,
        ED_ONE,
        ED_TWO,
        ED_THREE,
        ED_MAX
    };
    Q_ENUM(ExtraDefine);

    enum MoreDefine {
        MD_EMPTY = 100,
        MD_APPLE,
        MD_BALL,
        MD_CAT,
    };
    Q_ENUM(MoreDefine);

    Q_INVOKABLE QString sayHello(ExtraDefine ed);

public:
    RCommon();
};

typedef RCommon::CommonDefine EnumCommonDefineType;

#endif  // __COMMON_DEF_H__
