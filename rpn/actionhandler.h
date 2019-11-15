/**
    \file actionhandler.h
    \brief header file for class ActionHandler
**/
#ifndef __ACTIONHANDLER_H__
#define __ACTIONHANDLER_H__

#include <QObject>
#include <QHash>
#include <QString>

class ActionHandler;
typedef double (ActionHandler::*fpAct)(double, double);

/**
    \brief ActionHandler

    Just connect a signal to ActionHandler::sltHandleMsg()
    and redirect a QString command string to this class.
**/
class ActionHandler
{
public:
    static ActionHandler* getInstance();
    fpAct getAct(const QString& op);

protected:
    static ActionHandler* _instance;
    explicit ActionHandler();

public:
    // action functions for commands
    double actAdd(double m, double n) {
        return m + n;
    }
    double actSub(double m, double n) {
        return m - n;
    }
    double actMul(double m, double n) {
        return m * n;
    }
    double actDiv(double m, double n) {
        return m / n;
    }

private:
    // a hash table for command vs action function
    QHash<QString, fpAct> dict = {
        {"+", &ActionHandler::actAdd},
        {"-", &ActionHandler::actSub},
        {"*", &ActionHandler::actMul},
        {"/", &ActionHandler::actDiv}
    };

};

#endif  // __ACTIONHANDLER_H__
