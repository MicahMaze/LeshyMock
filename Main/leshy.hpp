/*
 WIP
 Leshy Mock
 Author: Micah Maze 2019
*/

#ifndef LESHY_MOCK
#define LESHY_MOCK

#include <cstdio>
#include <cstdlib>

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define CONCAT(x, y) CONCAT2(x, y)
#define CONCAT2(x, y) x ## y
#define IFVOID(type) ((#type)==("void")) ? true : false

#define LESHY_NAME(n) leshyvar_##n
#define LESHY_OBJECT(n) CONCAT(leshyobj_##n_, __LINE__)

class Expector
{
public:
    void SetExpected(int expected)
    {
        timesExpected = expected;
    }

    void UpdateCalled()
    {
        ++timesCalled;
    }

    void Enforce(char* name)
    {
        if (timesCalled < timesExpected)
        {
            printf("%s called less times than expected.\n", name);
            printf("Expected: %d\n", timesExpected);
            printf("Actual: %d\n", timesCalled);
            exit(EXIT_FAILURE);
        }
        else if (timesCalled > timesExpected && timesExpected > 0)
        {
            printf("%s called more times than expected.\n", name);
            printf("Expected: %d\n", timesExpected);
            printf("Actual: %d\n", timesCalled);
            exit(EXIT_FAILURE);
        }
    }

    int timesExpected = 0;
    int timesCalled = 0;
};

#define MOCK_CLASS(m, p) \
    class m : public p {\
    public:

#define MOCK_METHOD_INTERNAL(type, name, num_params) \
    class LESHY_OBJECT(name) { \
    public:\
    void SetReturn(type value) { \
    returnValue = value; \
    } \
    type GetReturn() { \
    return returnValue; \
    } \
    type returnValue; \
    Expector expector; \
    }; \
    LESHY_OBJECT(name) LESHY_NAME(name); \
    type name( \
    ) { \
    LESHY_NAME(name).expector.UpdateCalled(); \
    return LESHY_NAME(name).GetReturn(); \
    }

#define MOCK_METHOD_INTERNAL_VOID(name, num_params) \
    void name( \
    ) { \
    return; \
    }

#define EXPECT_INTERNAL(t, n) \
    LESHY_NAME(n).expector.SetExpected(t)

#define ENFORCE_EXPECT(n) \
    LESHY_NAME(n).expector.Enforce((char*)STRINGIZE(n))

//*************************
// User Methods
//*************************

#define MockClass(mock_name, parent_name) MOCK_CLASS(mock_name, parent_name)

#define EndMock };

#define MockMethod(type, name) MOCK_METHOD_INTERNAL(type, name, 0)

#define MockVoidMethod(name) MOCK_METHOD_INTERNAL_VOID(name, 0)

#define Return(value) SetReturn(value)

#define IfCalls(name, action) LESHY_NAME(name).action

#define Expect(times, name) EXPECT_INTERNAL(times, name)

#define ExpectOnce(name) EXPECT_INTERNAL(1, name)

#define Enforce(name) ENFORCE_EXPECT(name)
    

#endif // LESHY_MOCK
