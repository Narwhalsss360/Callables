#ifndef InvokableVerifier_h
#define InvokableVerifier_h

#include "VerifiableInvokable.h"
#include "Function.h"
#include "Method.h"
#include <stdint.h>

/// @brief Used to verify that an invokable to safe to invoke.
class InvokableVerifier
{
public:

    /// @brief Checks if a pointer to an invokable is still valid.
    /// @param pointer pointer to invokable
    /// @return `bool` true if invokable at pointer is valid
    static bool exists(VerifiableInvokable* pointer);

    /// @brief Checks if pointer is valid and if invokable is safe to invoke.
    /// @param pointer 
    /// @return `bool` true if pointer is valud and is safe to invoke
    static bool verify(VerifiableInvokable* pointer);

    /// @brief Get global invokable for a function.
    /// @tparam ReturnType Return type of function
    /// @tparam ...Args Arguments of function
    /// @param function Pointer to function
    /// @return `Invokable` of function
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

    /// @brief Get global invokable for a method.
    /// @tparam ReturnType Return type of method
    /// @tparam ...Args Arguments of the method
    /// @param instance Pointer to instance 
    /// @param method Pointer to bound function
    /// @return `Invokable` of bound function
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

/// @brief Checks if a pointer to an invokable is still valid.
/// @param pointer pointer to invokable
/// @return `bool` true if invokable at pointer is valid
bool invokable_exists(VerifiableInvokable* pointer);

/// @brief Checks if pointer is valid and if invokable is safe to invoke.
/// @param pointer 
/// @return `bool` true if pointer is valud and is safe to invoke
bool invokable_verify(VerifiableInvokable* pointer);

/// @brief Get global invokable for a function.
/// @tparam ReturnType Return type of function
/// @tparam ...Args Arguments of function
/// @param function Pointer to function
/// @return `Invokable` of function
template <typename ReturnType, typename... Args>
Invokable<ReturnType, Args...>& invokable_get(ReturnType (*function)(Args...))
{
    return InvokableVerifier::get(function);
}

/// @brief Get global invokable for a method.
/// @tparam ReturnType Return type of method
/// @tparam ...Args Arguments of the method
/// @param instance Pointer to instance 
/// @param method Pointer to bound function
/// @return `Invokable` of bound function
template <typename Container, typename ReturnType, typename... Args>
Invokable<ReturnType, Args...>& invokable_get(Container* instance, ReturnType (Container::*method)(Args...))
{
    return InvokableVerifier::get(instance, method);
}
#pragma endregion

#endif