#include "foo.h"
#include "actionhandler.h"

#include <QStringList>
// #include <QRegularExpression>
// #include <QRegularExpressionMatchIterator>
#include <QDebug>

/// refer to
/// https://en.wikipedia.org/wiki/Shunting-yard_algorithm
///

Foo* Foo::_instance = nullptr;
Foo* Foo::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Foo();
    }
    return _instance;
}

Foo::Foo()
{
}

void Foo::setRpn(const QStringList& sl)
{
    ActionHandler *ah = ActionHandler::getInstance();
    fpAct fp = nullptr;

    qDebug() << "sl:" << sl;
    stack.clear();
    bool ok;
    double r;
    for (int i = 0; i < sl.size(); i++) {
        QString tok = sl.at(i);
        double p = tok.toDouble(&ok);
        if (ok) {
            stack.push(p);
        } else {
            fp = ah->getAct(tok);
            if (fp != nullptr) {
                double m = stack.pop();
                double n = stack.pop();
                r = (*ah.*fp)(m, n);
                qDebug() << QString("%1 %2 %3 = %4").arg(m).arg(tok).arg(n).arg(r);
                stack.push(r);
            }
        }
    }

    r = stack.pop();
    qDebug() << "r:" << r;
}
