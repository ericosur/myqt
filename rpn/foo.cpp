#include "foo.h"

/// refer to
/// https://en.wikipedia.org/wiki/Shunting-yard_algorithm
///

Foo::Foo()
{

}

void Foo::setRpn(const QStringList& sl)
{
    ActionHandler *ah = ActionHandler::getInstance();
    fpAct fp = NULL;

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
            if (fp != NULL) {
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

