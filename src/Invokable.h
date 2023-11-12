#ifndef Invokable_h
#define Invokable_h

#include "VerifiableInvokable.h"

template <typename ReturnType, typename... Args>
struct Invokable : public VerifiableInvokable
{
    Invokable()
        : VerifiableInvokable()
    {
    }

    /// @brief Invokes
    /// @param ...args args
    /// @return `ReturnType`
    virtual ReturnType invoke(Args... args) const = 0;

    ReturnType operator()(Args... args) const
    {
        return invoke(args...);
    }

    ~Invokable()
    {
    }
};

#endif