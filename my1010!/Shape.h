
#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include<map>
#include<string>

#include "main.h"


class Block
{
    public :
    void set_block(int x, int y, Data::Colours block);//…Ë÷√∑ΩøÈ
    void set_random_colour(int x, int y);
    
    Data::Colours get_block () const {return pieceblock;}
    
    
    Data::Colours pieceblock;
};

#endif // SHAPE_H_INCLUDED
