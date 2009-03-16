#ifndef __REBOUND_SINGLETON_H__
#define __REBOUND_SINGLETON_H__

template< class T >
class Singleton
{
    public:
        static T & Instance()
        {
            static T * instance = new T;
            return *instance;
        }
};

#endif // __REBOUND_SINGLETON_H__