#include "MockFoo.h"
#include <iostream>

int main()
{
    MockFoo mockFoo;

    // Set Rules
    mockFoo.IfCalls(TestMethod1, Return(true));
    mockFoo.CallsOnce(TestMethod1);

    bool b = mockFoo.TestMethod1();
    std::cout << b << std::endl;

    // Enforce first call
    mockFoo.Enforce(TestMethod1);

    // Set new rules
    mockFoo.CallsNever(TestMethod2);

    b = mockFoo.TestMethod1();
    std::cout << b << std::endl;

    // Enforce second call
    mockFoo.Enforce(TestMethod1);

    mockFoo.CallsAtMost(TestMethod1, 3);

    mockFoo.TestMethod1();
    mockFoo.TestMethod1();

    printf("Test Passed!\n");
}
