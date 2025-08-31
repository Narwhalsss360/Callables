#ifndef Invokable_h
#define Invokable_h

template <typename ReturnType, typename... Args>
struct Invokable
{
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
