#include "rcommon.h"

RCommon::RCommon()
{

}

QString RCommon::sayHello(ExtraDefine ed)
{
    QString ret;
    switch (ed) {
        case ED_NULL:
            ret = "ed_null";
            break;
        case ED_ONE:
            ret = "ed_one";
            break;
        case ED_TWO:
            ret = "ed_two";
            break;
        case ED_THREE:
            ret = "ed_three";
            break;
        case ED_MAX:
            ret = "ed_max";
            break;
        default:
            break;
    }

    return ret;
}