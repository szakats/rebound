#ifndef __REBOUND_GAME_H_
#define __REBOUND_GAME_H

#include <Callback.h>
#include <set>

class Game
{
    public:
        void run();
        
    private:
        typedef std::set<Callback *> UpdateSetType;
        UpdateSetType updateSet;
};

#endif // __REBOUND_GAME_H__