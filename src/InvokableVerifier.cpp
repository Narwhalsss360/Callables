#include "InvokableVerifier.h"
#include <stdint.h>

VerifiableInvokable** instances = nullptr;
uint8_t instanceCount = 0;

#pragma region Public API
bool InvokableVerifier::exists(VerifiableInvokable* pointer)
{
    for (uint8_t i = 0; i < instanceCount; i++)
        if (instances[i] == pointer)
            return true;
    return false;
}

bool InvokableVerifier::verify(VerifiableInvokable* pointer)
{
    for (uint8_t i = 0; i < instanceCount; i++)
        if (instances[i] == pointer)
            return pointer->valid();
    return false;
}

bool invokable_exists(VerifiableInvokable* pointer)
{
    return InvokableVerifier::exists(pointer);
}

bool invokable_verify(VerifiableInvokable* pointer)
{
    return InvokableVerifier::verify(pointer);
}
#pragma endregion

#pragma region Instance Management
VerifiableInvokable* InvokableVerifier::getAt(uint8_t index)
{
    return instances[index];
}

void InvokableVerifier::addInstance(VerifiableInvokable* pointer)
{
    if (instances == nullptr)
    {
        instances = new VerifiableInvokable*[1];
        instances[0] = pointer;
        instanceCount++;
        return;
    }

    for (uint8_t i = 0; i < instanceCount; i++)
        if (instances[i] == pointer)
            return;

    VerifiableInvokable** newAllocation = new VerifiableInvokable*[instanceCount + 1];
    for (uint8_t i = 0; i < instanceCount; i++)
        newAllocation[i] = instances[i];
    newAllocation[instanceCount] = pointer;
    instanceCount++;

    delete[] instances;
    instances = newAllocation;
}

void InvokableVerifier::removeInstance(VerifiableInvokable* pointer)
{
    int16_t index = -1;

    for (uint8_t i = 0; i < instanceCount; i++)
    {
        if (instances[i] == pointer)
        {
            index = i;
            break;
        }
    }
    
    if (index == -1)
        return;

    VerifiableInvokable** newAllocation = new VerifiableInvokable*[instanceCount - 1];

    for (uint8_t iDestination = 0, iSource = 0;
    iSource < instanceCount;
    iDestination++, iSource = (iSource == index -1 ? iSource + 2 : iSource + 1))
    {
        newAllocation[iDestination] = instances[iSource];
    }

    instanceCount--;
    delete[] instances;
    instances = newAllocation;
}

VerifiableInvokable**& InvokableVerifier::getInstancesReference()
{
    return instances;
}

uint8_t& InvokableVerifier::getInstanceCountReference()
{
    return instanceCount;
}
#pragma endregion