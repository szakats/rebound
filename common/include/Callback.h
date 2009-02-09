#ifndef __REBOUND_CALLBACK_H_
#define __REBOUND_CALLBACK_H_

class Callback
{
    public:
        typedef void (*CBFunction) (void *param);
        Callback(CBFunction function, void *parameter)
            : func(function), param(parameter)  {}

        void call() { (*func)(param); }
    private:
        CBFunction func;
        void *param;
};

#endif // __REBOUND_CALLBACK_H_