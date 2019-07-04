#ifndef MOCKFOO
#define MOCKFOO

#include "leshy.hpp"
#include "IFoo.h"

MockClass(MockFoo, IFoo)
    MockMethod(bool, TestMethod1);
    MockVoidMethod(TestMethod2);
EndMock

#endif // MOCKFOO
