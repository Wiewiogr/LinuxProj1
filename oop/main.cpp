#include <iostream>
#include "play.h"
#include "barracks.h"
#include <vector>

int main()
{
    Barracks *fabrics[2] = {new HumanBarracks, new OrcBarracks};
    std::vector<Player*> players;
    for(int i = 0 ; i < 10; i++)
        players.push_back(fabrics[i%2]->createPlayer());
    for(auto x : players)
        x->idle();
    return 0;
}
