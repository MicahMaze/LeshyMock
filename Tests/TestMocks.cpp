#include "MockFoo.h"
#include <cstdio>

int main()
{
    MockFoo mockFoo;

    mockFoo.IfCalls(TestMethod1, Return(true));
    mockFoo.CallsOnce(TestMethod1);

    bool b = mockFoo.TestMethod1();

    mockFoo.Enforce(TestMethod1);
    mockFoo.CallsNever(TestMethod2);

    b = mockFoo.TestMethod1();

    mockFoo.Enforce(TestMethod1);

    printf("Test Passed!\n");
}
