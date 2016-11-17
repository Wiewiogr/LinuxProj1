#include <string>
#include "barracks.h"
#include "play.h"

Player* HumanBarracks::createPlayer()
{
    return new Human();
}

Player* OrcBarracks::createPlayer()
{
    return new Orc();
}
