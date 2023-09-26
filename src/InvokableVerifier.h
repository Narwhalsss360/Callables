#ifndef InvokableVerifier_h
#define InvokableVerifier_h

#include "VerifiableInvokable.h"
#include "Function.h"
#include "Method.h"
#include <stdint.h>

class InvokableVerifier
{
public:
    static bool exists(VerifiableInvokable*);

    static bool verify(VerifiableInvokable*);

    template <typename ReturnType, typename... Args>
    static Invokable<ReturnType, Args...>& get(ReturnType (*function)(Args...))
    {
        VerifiableInvokable**& instances = getInstancesReference();
        uint8_t& instanceCount = getInstanceCountReference();

        Invokable<ReturnType, Args...>* found = nullptr;
        for (uint8_t i = 0; i < instanceCount; i++)
        {
            if (instances[i]->code() != VerifiableCode_Function)
                continue;

            Function<ReturnType, Args...>* invokable = (Function<ReturnType, Args...>*)instances[i];
            if (invokable->getFunction() != function)
                continue;

            found = invokable;
            break;
        }

        if (found == nullptr)
            found = new Function<ReturnType, Args...>(function);

        return *found;
    }

    template <typename Container, typename ReturnType, typename... Args>
    static Invokable<ReturnType, Args...>& get(Container* instance, ReturnType (Container::*method)(Args...))
    {
        VerifiableInvokable**& instances = getInstancesReference();
        uint8_t& instanceCount = getInstanceCountReference();

        Invokable<ReturnType, Args...>* found = nullptr;
        for (uint8_t i = 0; i < instanceCount; i++)
        {
            if (instances[i]->code() != VerifiableCode_Method)
                continue;

            Method<Container, ReturnType, Args...>* invokable = (Method<Container, ReturnType, Args...>*)instances[i];
            if (invokable->getInstance() != instance)
                continue;
            if (invokable->getMethod() != method)
                continue;

            found = invokable;
            break;
        }
        
        if (found == nullptr)
            found = new Method<Container, ReturnType, Args...>(instance, method);

        return *found;
    }

private:
    static VerifiableInvokable* getAt(uint8_t);

    static void addInstance(VerifiableInvokable*);

    static void removeInstance(VerifiableInvokable*);

    static VerifiableInvokable**& getInstancesReference();

    static uint8_t& getInstanceCountReference();

    friend class VerifiableInvokable;
};

#pragma region Global Functions
bool invokable_exists(VerifiableInvokable*);

bool invokable_verify(VerifiableInvokable*);

template <typename ReturnType, typename... Args>
Invokable<ReturnType, Args...>& invokable_get(ReturnType (*function)(Args...))
{
    return InvokableVerifier::get(function);
}

template <typename Container, typename ReturnType, typename... Args>
Invokable<ReturnType, Args...>& invokable_get(Container* instance, ReturnType (Container::*method)(Args...))
{
    return InvokableVerifier::get(instance, method);
}
#pragma endregion

#endif