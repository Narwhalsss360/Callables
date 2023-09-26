#ifndef Method_h
#define Method_h

#include "Invokable.h"

template <typename Container, typename ReturnType, typename... Args>
struct Method : public Invokable<ReturnType, Args...>
{
    using method_t = ReturnType (Container::*)(Args...);

    Method(Container* instance = nullptr, method_t method = nullptr)
        : Invokable<ReturnType, Args...>(), instance(instance), method(method)
    {
    }

    ReturnType invoke(Args... args) const override
    {
        return (instance->*method)(args...);
    }

    bool valid() const override
    {
        return instance != nullptr && method != nullptr;
    }

    virtual const int code() const override
    {
        return VerifiableCode_Method;
    }

    Container* getInstance() const
    {
        return instance;
    }

    void setInstance(Container* instance)
    {
        this->instance = instance;
    }

    method_t getMethod() const
    {
        return method;
    }

private:
    Container* instance;
    method_t method;
};

template <typename Container, typename ReturnType, typename... Args>
Method <Container, ReturnType, Args...>&& Method_Infered(Container* instance, ReturnType (Container::*method)(Args...))
{
    return Method <Container, ReturnType, Args...>(instance, method);
}

#endif