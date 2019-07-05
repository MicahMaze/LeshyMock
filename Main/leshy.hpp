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
        times_expected = expected;
    }

    void UpdateCalled()
    {
        called = true;
        ++times_called;
    }

    void Enforce(char* name, char* file_name, int line_number)
    {
        if (times_called < times_expected)
        {
            printf("%s:%d - %s called less times than expected.\n", file_name, line_number, name);
            printf("Expected: %d\n", times_expected);
            printf("Actual: %d\n", times_called);
            exit(EXIT_FAILURE);
        }
        else if (times_called > times_expected && called)
        {
            printf("%s:%d - %s called more times than expected.\n", file_name, line_number, name);
            printf("Expected: %d\n", times_expected);
            printf("Actual: %d\n", times_called);
            exit(EXIT_FAILURE);
        }

        called = false;
        times_called = 0;
    }

private:
    bool called = false;
    int times_expected = 0;
    int times_called = 0;
};

#define MOCK_CLASS(m, p) \
    class m : public p {\
    public:

#define MOCK_METHOD_INTERNAL(type, name, num_params, ...) \
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
    type name( __VA_ARGS__\
    ) { \
    LESHY_NAME(name).expector.UpdateCalled(); \
    return LESHY_NAME(name).GetReturn(); \
    }

#define MOCK_METHOD_INTERNAL_VOID(name, num_params) \
    class LESHY_OBJECT(name) { \
    public:\
    Expector expector; \
    }; \
    LESHY_OBJECT(name) LESHY_NAME(name); \
    void name( \
    ) { \
    return; \
    }

#define EXPECT_INTERNAL(t, n) \
    LESHY_NAME(n).expector.SetExpected(t)

#define ENFORCE_EXPECT(n) \
    LESHY_NAME(n).expector.Enforce((char*)STRINGIZE(n), (char*)__FILE__, __LINE__)

//*************************
// User Methods
//*************************

#define MockClass(mock_name, parent_name) MOCK_CLASS(mock_name, parent_name)

#define EndMock };

#define MockMethod(type, name, ...) MOCK_METHOD_INTERNAL(type, name, 0, __VA_ARGS__);

#define MockVoidMethod(name) MOCK_METHOD_INTERNAL_VOID(name, 0);

#define Return(value) SetReturn(value)

#define IfCalls(name, action) LESHY_NAME(name).action

#define CallsExactly(name, times) EXPECT_INTERNAL(times, name)

#define CallsOnce(name) EXPECT_INTERNAL(1, name)

#define CallsNever(name) EXPECT_INTERNAL(0, name)

#define Enforce(name) ENFORCE_EXPECT(name)


//*************************
// Wanted Functionality
//*************************
// CallsAtLeast
// CallsAtMost
// ClearRules
    

#endif // LESHY_MOCK
