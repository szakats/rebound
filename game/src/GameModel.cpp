#include "common.h"

#include "GameModel.h"

GameModel::~GameModel()
{
    if(_hitEvent) delete _hitEvent;
}

GameModel::GameModel()
{

}

void GameModel::AddSample(MoveSample sample, int turn)
{

}

void GameModel::Start()
{

}

void GameModel::HitEvent::Call()
{
    _model->_hitEvent = NULL;
}