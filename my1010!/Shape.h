#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

enum Colours {no_colour,red_colour,ora_colour,yel_colour,gre_colour,lblu_colour,dblu_colour,pur_colour};
class Block
{
public :
    Block(){set_block(no_colour);}
    void set_block(Colours block);//…Ë÷√∑ΩøÈ
    void set_random_colour();

    Colours get_block () const {return pieceblock;}


    Colours pieceblock;
};

#endif // SHAPE_H_INCLUDED
