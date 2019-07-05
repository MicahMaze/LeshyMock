# Leshy Mock

Leshy Mock is a unit test mocking framework for C++.

## Example of Use

Tested class' Dependency
```cpp
class Foo : public IFoo
{
public:
    int GetInteger();
    void DoStuff(int value);
    bool DoOtherStuff();
};
```

Tested Class
```cpp
class Bar : public IBar
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
            foo.DoStuff(i);
            foo.DoStuff(i);
        }
        else if (i > 20)
        {
            foo.DoOtherStuff();
        }
    }

    IFoo foo;
};
```

Leshy Mock for dependency
```cpp
MockClass(MockFoo, IFoo)
    MockMethod(int, GetInteger)
    MockVoidMethod(DoStuff)
    MockMethod(bool, DoOtherStuff)
EndMock
```

Test
```cpp
TEST(BarTests, UseInteger)
{
    MockFoo mockFoo;
    Bar bar(mockFoo); // Use dependency injection for mocks

    mockFoo.IfCalls(GetInteger, Return(0)); // This ensures if GetInteger is called, it will return 0
    mockFoo.CallsOnce(GetInteger); // This sets a rule that GetInteger is called exactly one time
    mockFoo.CallsNever(DoStuff); // This sets a rule that DoStuff is never called
    mockFoo.CallsNever(DoOtherStuff); // This sets a rule that DoOtherStuff is never called

    bar.UseInteger(); // Call tested method

    mockFoo.Enforce(GetInteger); // Enforce all defined rules for GetInteger - Called once
    mockFoo.Enforce(DoStuff); // Enforce all defined rules for DoStuff - Never called
    
    mockFoo.IfCalls(GetInteger, Return(5)); // This ensures if GetInteger is called, it will return 5
    mockFoo.CalledExactly(DoStuff, 2); // This sets a rule that DoStuff is called exactly twice - Overrides previous rule

    bar.UseInteger(); // Call tested method

    mockFoo.Enforce(GetInteger); // Enforce all defined rules for GetInteger - Called Once
    mockFoo.Enforce(DoOtherStuff); // Finally enforce that DoOtherStuff was never called during this test
} // We forgot to enforce DoStuff before ending the test but its ok, all outstanding rules are automatically enforced on destruction
```
