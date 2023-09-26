#ifndef Function_h
#define Function_h

#include "Invokable.h"

template <typename ReturnType, typename... Args>
struct Function : public Invokable<ReturnType, Args...>
{
    using function_t = ReturnType (*)(Args...);

    Function(function_t function = nullptr)
        : Invokable<ReturnType, Args...>(), function(function)
    {
    }

    ReturnType invoke(Args... args) const override
    {
        return function(args...);
    }

    bool valid() const override
    {
        return function != nullptr;
    }

    virtual const int code() const override
    {
        return VerifiableCode_Function;
    }

    function_t getFunction() const
    {
        return function;
    }

private:
    function_t function;
};

template <typename ReturnType, typename... Args>
Function<ReturnType, Args...> Function_Infered(ReturnType (*f)(Args...))
{
    return Function<ReturnType, Args...>(f);
}

#endif