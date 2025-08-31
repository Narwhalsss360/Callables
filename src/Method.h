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

    /// @brief Invokes
    /// @param ...args args
    /// @return 
    ReturnType invoke(Args... args) const override
    {
        return (instance->*method)(args...);
    }

    /// @brief Verifies the instance pointer and the method pointer.
    /// @return 
    bool valid() const
    {
        return instance != nullptr && method != nullptr;
    }
    ///
    /// @brief Gets the instance.
    /// @return `Container` instance
    Container* getInstance() const
    {
        return instance;
    }

    /// @brief Sets the instance.
    /// @param instance instance
    void setInstance(Container* instance)
    {
        this->instance = instance;
    }

    /// @brief Get the method (bound) function pointer.
    /// @return `method_t` method
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
