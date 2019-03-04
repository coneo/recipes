#ifndef _SCOPE_GUARD_H
#define _SCOPE_GUARD_H

#include <functional>

class ScopeGuard
{
public:
    ScopeGuard(std::function<void()> on_exit_scope)
        : _scope_func(on_exit_scope)
    {
    }

    ~ScopeGuard()
    {
        if (!_dismiss)
        {
            _scope_func();
        }
    }

    void dismiss()
    {
        _dismiss = true;
    }

private:
    std::function<void()> _scope_func;

    bool _dismiss = false;
};

#endif // _SCOPE_GUARD_H
