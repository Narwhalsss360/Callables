#include "VerifiableInvokable.h"
#include "InvokableVerifier.h"

VerifiableInvokable::VerifiableInvokable()
{
    InvokableVerifier::addInstance(this);
}

bool VerifiableInvokable::valid() const
{
    return false;
}   

VerifiableInvokable::operator bool()
{
    return valid();
}

const int VerifiableInvokable::code() const
{
    return VerifiableCode_Invalid;
}

VerifiableInvokable::~VerifiableInvokable()
{
    InvokableVerifier::removeInstance(this);
}