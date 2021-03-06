#include <stdlib.h>
#include <time.h>

#include "Item.h"
#include "Coin.h"
#include "../game.h"

Coin::Coin() {
    switch(rand() % 3) {
        case 0:
            setChar('.');
            setValue(25);
            break;
        case 1:
            setChar('o');
            setValue(100);
            break;
        case 2:
            setChar('O');
            setValue(250);
            break;
    }

    uint_fast8_t randx = (rand() % (game_area.right() -1) + 1);
    uint_fast8_t randy = (rand() % (game_area.bot()   -1) + 1);
    setPos({ randx, randy });
}
