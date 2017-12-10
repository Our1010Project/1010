#include <stdlib.h>
#include <algorithm>
#include "Shape.h"

using namespace std;

void Block::set_block(Colours block)
{

    pieceblock=block;
}

void Block::set_random_colour()
{
int x = rand() % 7 + 1;
set_block(Colours (x));
}

