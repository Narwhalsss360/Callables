#ifndef Callable_h
#define Callable_h

typedef void* any_ptr;

typedef void (*VoidFunctionVoid)();
typedef void (*VoidFunctionAny)(any_ptr);

struct Callable
{
	virtual void invoke(any_ptr = nullptr) = 0;

	virtual void operator()(any_ptr = nullptr);
};

struct VoidCallableVoid : Callable
{
	VoidCallableVoid(VoidFunctionVoid = nullptr);

	virtual void invoke(any_ptr = nullptr) override;

private:
	VoidFunctionVoid function;
};

struct VoidCallableAny : Callable
{
	VoidCallableAny(VoidFunctionAny = nullptr);

	virtual void invoke(any_ptr = nullptr) override;

private:
	VoidFunctionAny function;
};

template <typename Object>
struct VoidMemberVoid : VoidCallableVoid
{
	using MemberFunctionPointer = void (Object::*)();

	VoidMemberVoid(Object* instance = nullptr, MemberFunctionPointer member = nullptr)
		: VoidCallableVoid(), instance(instance), member(member)
	{
	}

	void invoke(any_ptr = nullptr) override
	{
		if (instance && member)
			(instance->*member)();
	}

private:
	Object* instance;
	MemberFunctionPointer member;
};

template <typename Object>
struct VoidMemberAny : VoidCallableAny
{
	using MemberFunctionPointer = void (Object::*)(any_ptr);

	VoidMemberAny(Object* instance = nullptr, MemberFunctionPointer member = nullptr)
		: VoidCallableVoid(), instance(instance), member(member)
	{
	}

	void invoke(any_ptr pointer = nullptr) override
	{
		if (instance && member)
			(instance->*member)(pointer);
	}

private:
	Object* instance;
	MemberFunctionPointer member;
};

#endif