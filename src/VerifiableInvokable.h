#ifndef VerifiableInvokable_h
#define VerifiableInvokable_h

#pragma region Codes
constexpr int VerifiableCode_Invalid = 0;
constexpr int VerifiableCode_Function = 1;
constexpr int VerifiableCode_Method = 2;
#pragma endregion

struct VerifiableInvokable
{
    VerifiableInvokable();

    virtual bool valid() const;

    virtual const int code() const;

    operator bool();

    ~VerifiableInvokable();
};

#endif