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

enum Constraint
{
    exactly = 0,
    at_most,
    at_least
};

class Expector
{
public:
    ~Expector()
    {
        if (ruleSet)
        {
            if (times_called < times_expected && constraint != at_most && !enforced)
            {
                PrintFail((char*)"called less times than expected.", (char*)"", 0);
            }
            else if (times_called > times_expected && constraint != at_least && called)
            {
                PrintFail((char*)"called more times than expected.", (char*)"", 0);
            }
        }
    }

    void SetName(char* n)
    {
        name = n;
    }

    void SetExpected(int expected, Constraint c)
    {
        ruleSet = true;
        enforced = false;
        constraint = c;
        times_expected = expected;
    }

    void UpdateCalled()
    {
        called = true;
        ++times_called;
    }

    void Enforce(char* file_name, int line_number)
    {
        if (ruleSet)
        {
            if (times_called < times_expected && constraint != at_most)
            {
                PrintFail((char*)"called less times than expected.", file_name, line_number);
            }
            else if (times_called > times_expected && constraint != at_least && called)
            {
                PrintFail((char*)"called more times than expected.", file_name, line_number);
            }

            enforced = true;
            called = false;
            times_called = 0;
        }
    }

    void ClearRules()
    {
        ruleSet = false;
        enforced = false;
        called = false;
        times_expected = 0;
        times_called = 0;
    }

private:
    void PrintFail(char* msg, char* file_name, int line_number)
    {
        if (line_number != 0)
        {
            printf("%s:%d - ", file_name, line_number);
        }

        printf("%s\n", msg);
        printf("Expected: %d\n", times_expected);
        printf("Actual: %d\n", times_called);
        exit(EXIT_FAILURE);
    }

    char* name;
    bool ruleSet = false;
    bool enforced = false;
    bool called = false;
    int times_expected = 0;
    int times_called = 0;
    Constraint constraint = exactly;
};

#define MOCK_CLASS(m, p) \
    class m : public p {\
    public: 

#define MOCK_METHOD_INTERNAL(type, name, num_params, ...) \
    class LESHY_OBJECT(name) { \
    public:\
    LESHY_OBJECT(name)() { \
    expector.SetName((char*)STRINGIZE(name)); \
    }  \
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

#define EXPECT_INTERNAL(t, n, c) \
    LESHY_NAME(n).expector.SetExpected(t, c)

#define ENFORCE_EXPECT(n) \
    LESHY_NAME(n).expector.Enforce((char*)__FILE__, __LINE__)

#define CLEAR_RULES(n) \
    LESHY_NAME(n).expector.ClearRules()

//*************************
// User Methods
//*************************

#define MockClass(mock_name, parent_name) MOCK_CLASS(mock_name, parent_name)

#define EndMock };

#define MockMethod(type, name, ...) MOCK_METHOD_INTERNAL(type, name, 0, __VA_ARGS__);

#define MockVoidMethod(name) MOCK_METHOD_INTERNAL_VOID(name, 0);

#define Return(value) SetReturn(value)

#define IfCalls(name, action) LESHY_NAME(name).action

#define CallsExactly(name, times) EXPECT_INTERNAL(times, name, exactly)

#define CallsOnce(name) EXPECT_INTERNAL(1, name, exactly)

#define CallsNever(name) EXPECT_INTERNAL(0, name, exactly)

#define CallsAtLeast(name, times) EXPECT_INTERNAL(times, name, at_least)

#define CallsAtMost(name, times) EXPECT_INTERNAL(times, name, at_most)

#define Enforce(name) ENFORCE_EXPECT(name)

#define ClearRules(name) CLEAR_RULES(name)

//*************************
// Wanted Functionality
//*************************

#endif // LESHY_MOCK
