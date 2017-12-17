#include <stdlib.h>
#include <algorithm>
#include "Shape.h"

using namespace std;

Property::Property()
    :colour{default_property().colour},
     wait_to_clean{default_property().wait_to_clean},
     already_scaned{default_property().already_scaned}
{}

Property::Property(Colours cc,bool ww,bool aa):colour{cc},wait_to_clean{ww},already_scaned{aa}{}

const Property& default_property()
{
    static Property pp{no_colour,false,false};
    return pp;
}

Block::Block(){set_block(default_property());}

void Block::set_block(Property block)
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
set_block(Property(Colours (x),false,false));
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
