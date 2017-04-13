/**
    \file actionhandler.cpp
    \brief implementation of class ActionHandler
**/
#include "actionhandler.h"


ActionHandler* ActionHandler::_instance = NULL;
ActionHandler* ActionHandler::getInstance()
{
    if (_instance == NULL) {
        _instance = new ActionHandler;
    }
    return _instance;
}

ActionHandler::ActionHandler()
{
    initActionTable();
}

void ActionHandler::initActionTable()
{
    dict["+"] = &ActionHandler::actAdd;
    dict["-"] = &ActionHandler::actSub;
    dict["*"] = &ActionHandler::actMul;
    dict["/"] = &ActionHandler::actDiv;
}

fpAct ActionHandler::getAct(const QString& op)
{
    if (dict.contains(op)) {
        return dict.value(op);
    } else {
        return NULL;
    }
}

double ActionHandler::actAdd(double m, double n)
{
    return (m+n);
}

double ActionHandler::actSub(double m, double n)
{
    return (m-n);
}

double ActionHandler::actMul(double m, double n)
{
    return (m*n);
}

double ActionHandler::actDiv(double m, double n)
{
    return (m/n);
}
