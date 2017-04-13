#ifndef __FOO_H__
#define __FOO_H__

#include <QString>
#include <QStringList>
#include <QStack>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

#include "actionhandler.h"

class Foo
{
public:
    Foo();

    void setRpn(const QStringList& sl);

protected:

private:
    QStack<double> stack;
};


#endif	// __FOO_H__
