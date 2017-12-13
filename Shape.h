#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

enum Colours {no_colour,red_colour,ora_colour,yel_colour,gre_colour,lblu_colour,dblu_colour,pur_colour};
class Block
{
public :
    Block(){set_block(no_colour);}
    void set_block(Colours block);
    void set_random_colour();

    int x (int index) const {return coords[index];}
    Colours get_block () const {return pieceblock;}

    //Block move_left()const;
    //Block move_right()const;

    Colours pieceblock;

private:
    void set_x(int index,int x){coords[index]=x;}
    int coords[8];

};

#endif // SHAPE_H_INCLUDED
