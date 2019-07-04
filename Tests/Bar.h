#include "IFoo.h"

class Bar
{
public:
    Bar(IFoo& f)
    {
        foo = f;
    }

    void UseInteger()
    {
        int i = foo.GetInteger();

        if (i > 10)
        {
            i = foo.GetInteger();
            foo.DoStuff(i);
        }
        else if (i > 20)
        {
            foo.DoOtherStuff();
        }
    }

private:
    IFoo foo;
};
