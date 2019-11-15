/**
    \file actionhandler.cpp
    \brief implementation of class ActionHandler
**/
#include "actionhandler.h"

#include <QDebug>

ActionHandler* ActionHandler::_instance = nullptr;
ActionHandler* ActionHandler::getInstance()
{
    if (_instance == nullptr) {
        _instance = new ActionHandler();
    }
    return _instance;
}

ActionHandler::ActionHandler()
{
}


fpAct ActionHandler::getAct(const QString& op)
{
    if (dict.contains(op)) {
        return dict.value(op);
    }
    return nullptr;
}
