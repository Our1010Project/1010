#include <stdlib.h>
#include <algorithm>
#include "Shape.h"

using namespace std;

void Block::set_block(Colours block)
{
     static const int coordsTable[8][2] =
        { { 0, int(no_colour) }, { 0, int(red_colour) }, { 0, int(ora_colour) }, { 0, int(yel_colour) },
        { 0, int(gre_colour) },{ 0, int(lblu_colour) },{ 0, int(dblu_colour) },{ 0, int(pur_colour) } };

    for (int i=0;i<8;i++)
    {
        coords[i]=coordsTable[i][0];//store block x-coordinate
    }
     pieceblock=block;
}

void Block::set_random_colour()
{
int x = rand() % 7 + 1;
set_block(Colours (x));
}
/*
Block Block::move_left() const
{
    Block result;
    result.pieceblock=Block::pieceblock;
    result.set_x(pieceblock,result.x(pieceblock)-1);
    return result;
}

Block Block::move_right() const
{
    Block result;
    result.pieceblock=Block::pieceblock;
    result.set_x(pieceblock,result.x(pieceblock)+1);
    return result;
}*/
