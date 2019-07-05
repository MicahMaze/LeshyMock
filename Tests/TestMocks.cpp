#include "MockFoo.h"
#include <cstdio>

int main()
{
    MockFoo mockFoo;

    // Set Rules
    mockFoo.IfCalls(TestMethod1, Return(true));
    mockFoo.CallsOnce(TestMethod1);

    bool b = mockFoo.TestMethod1();

    // Enforce first call
    mockFoo.Enforce(TestMethod1);

    // Set new rules
    mockFoo.CallsNever(TestMethod2);

    b = mockFoo.TestMethod1();

    // Enforce second call
    mockFoo.Enforce(TestMethod1);

    printf("Test Passed!\n");
}
