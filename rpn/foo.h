#ifndef __FOO_H__
#define __FOO_H__

#include <QStack>
#include <QStringList>

class Foo
{

public:
    static Foo* getInstance();

    void setRpn(const QStringList& sl);

protected:
    static Foo* _instance;
    explicit Foo();

private:
    QStack<double> stack;
};


#endif	// __FOO_H__
