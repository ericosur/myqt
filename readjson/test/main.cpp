#include "../readjson.h"
#include "test.h"
#include "foobar.h"

#include <QCoreApplication>
#include <QDebug>

void hashtest();

class Base
{
public:
    int Val() const {
        return val;
    }
    void setVal(int v) {
        val = v;
    }
    int val = 0;
};

class Foo : public Base
{
};

class Bar : public Base
{
};

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();
    enum_test();
    hashtest();
    testvm();

#if 0
    Foo foo;
    Bar bar;
    foo.setVal(100);
    bar.setVal(200);
    qDebug() << foo.Val();
    qDebug() << bar.Val();
#endif
    return 0;
}
