#ifndef __REBOUND_GAME_MODEL_H__
#define __REBOUND_GAME_MODEL_H__

#include "Controller.h"
#include "Event.h"

class GameModel
{
    public:
        GameModel();
        ~GameModel();

        void AddSample(MoveSample sample, int turn);
        void Start();
    private:
        friend class HitEvent;
        class HitEvent : public SingleEvent
        {
            public:
                HitEvent(uint32 delay, GameModel *model) : SingleEvent(delay), _model(model) {}
                void Call();
            private:
                GameModel *_model;
        };

        HitEvent *_hitEvent;
};

#endif //__REBOUND_GAME_MODEL_H__