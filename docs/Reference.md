# Reference Guide

## Mock Class Setup

| Name | Description | Example |
|:-----|:------------|:--------|
| `MockClass(name, parent)` | Sets up a mock class where `name` is the mock class name and `parent` is the parent of the class to be mocked |` MockClass(MockFoo, Foo)` |
| `MockMethod(type, name, args...)` | Sets up `name` method with a return value of `type` to be mocked within the mock class | `MockMethod(bool, Method1, int)` |
| `MockVoidMethod(name, args...)` | Sets up void `name` method with to be mocked within the mock class | `MockVoidMethod(Method2, int)` |
| `EndMock` | Notifies the mock class that all mocked methods have been specified | `MockClass(...) MockMethod(...) EndMock` |

## Actions

Actions can be used within various other mock functions in order to have the method perform an action when called.

| Name | Description | Example |
|:-----|:------------|:--------|
| `Return(value)` | Force a mocked method to return a specified `value` | `mockFoo.IfCalls(Method1, Return(10))` |

## Rules

Rules set up certain boundries or expectations on a specific method. These rules are enforce when either `Enforce` is called on the method or the test ends.

| Name | Description | Example |
|:-----|:------------|:--------|
| `IfCalls(name, action)` | If method `name` is called, perform `action` | `mockFoo.IfCalls(Method, Return(10))` |
| `CallsExactly(name, times)` | Ensure that method `name` is called exactly `times` number of times | `mockFoo.CallsExactly(Method1, 2)` |
| `CallsAtLeast(name, times)` | Ensure that method `name` is called at least `times` number of times | `mockFoo.CallsAtLeast(Method1, 2)` |
| `CallsAtMost(name, times)` | Ensure that method `name` is called at most `times` number of times | `mockFoo.CallsAtMost(Method1, 2)` |
| `CallsOnce(name)` | Ensure that method `name` is called exactly once | `mockFoo.CallsOnce(Method1)` |
| `CallsNever(name)` | Ensure that method `name` is never called | `mockFoo.CallsNever(Method1)` |
| `Enforce(name)` | Enforce all rules that have been specified for method `name` | `mockFoo.Enforce(Method1)` |
| `ClearRules(name)` | Clear previously defined rules for method `name` so they will not be enforced again | `mockFoo.ClearRules(name)` |
