#include <stdlib.h>
#include <algorithm>
#include "Shape.h"

using namespace std;

void Block::set_block(int x, int y, Data::Colours block)
{
    pieceblock=block;
}

void Block::set_random_colour(int x,int y) {
    int c = rand() % 7 + 1;
    set_block(x,y,Data::Colours (c));
};


