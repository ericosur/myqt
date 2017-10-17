#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#include <QObject>

class RCommon : public QObject
{
    Q_OBJECT

public:
    enum CommonDefine {
        CD_NULL,
        CD_START,
        CD_RUNNING,
        CD_PAUSE,
        CD_STOP,
        CD_MAX,
        CD_UNKNOWN,
    };
    Q_ENUMS(CommonDefine);

    enum ExtraDefine {
        ED_NULL,
        ED_ONE,
        ED_TWO,
        ED_THREE,
        ED_MAX
    };
    Q_ENUMS(ExtraDefine);

    enum MoreDefine {
        MD_EMPTY,
        MD_APPLE,
        MD_BALL,
        MD_CAT,
    };
    Q_ENUMS(MoreDefine);

public:
    RCommon();

    CommonDefine getStatus() const {
        return mStatus;
    }


private:
    CommonDefine mStatus = CD_NULL;
};

typedef RCommon::CommonDefine EnumCommonDefineType;

#endif  // __COMMON_DEF_H__
