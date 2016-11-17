#pragma once
#include <string>

class Player
{
    std::string name;
public:
    Player() {}
    virtual void idle() = 0;
};

class Orc: public Player
{
public:
    void idle();
};

class Human: public Player
{
public:
    void idle();
};
