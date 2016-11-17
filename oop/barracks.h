#pragma once
#include <string>
#include "play.h"

class Barracks
{
public:
    virtual Player* createPlayer() = 0;
};

class HumanBarracks: public  Barracks
{
public:
    Player* createPlayer();
};

class OrcBarracks : public Barracks
{
public:
    Player* createPlayer();
};
