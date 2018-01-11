#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

enum Colours {no_colour,red_colour,ora_colour,yel_colour,gre_colour,lblu_colour,dblu_colour,pur_colour};
class Property
{
public:
    Property();
    Property(Colours cc,bool ww,bool aa);

    Colours colour;

    bool wait_to_clean;
    bool already_scaned;

};

const Property& default_property();

class Block
{
public :
    Block();
    void set_block(Property block);
    void set_random_colour(int dif);

    int x (int index) const {return coords[index];}
    Property get_block () const {return pieceblock;}

    //Block move_left()const;
    //Block move_right()const;

    Property pieceblock;

private:
    void set_x(int index,int x){coords[index]=x;}
    int coords[8];

};

#endif // SHAPE_H_INCLUDED
