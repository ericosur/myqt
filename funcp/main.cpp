#include <iostream>

using namespace std;

// a function pointer take parameters (int, int)
// and return int
typedef int (*MyFuncP)(int, int) ;

// a function that takes "MyFuncP"
void use_add(MyFuncP f)
{
    // call parameter f
    cout << f(1, 2) << endl;
}

// function defined as 'MyFuncP'
int named_add(int m, int n)
{
    return (m+n);
}

int main()
{
    use_add( /* in-place anonymous function here // C++11 feature */
            [](int x, int y){return (x+y);}
    );

    use_add(named_add);

    return 0;
}
