#include <common.h>
#include <Game.h>

void Game::run()
{
    // main loop
    //while(not finished)

    for(UpdateSetType::iterator itr = updateSet.begin(); itr != updateSet.end(); ++itr)
    {
        (*itr)->call();
    }
}