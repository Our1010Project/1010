#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <map>

#include <wx/wx.h>

namespace Data{
    enum Colours {no_colour,red_colour,ora_colour,yel_colour,gre_colour,lblu_colour,dblu_colour,pur_colour};
    const int width {10};
    const int height {10};
    const int no_of_color{7};
    
    extern std::map<int,std::string> clr;
    
    int grid[width][height+1];
    class form{
    public:
        void get(int a, int b);
        void init();
        void init_line();
        void drop();
    };
}


class MyApp : public wxApp
{
  public:
    virtual bool OnInit();

};

#endif // MAIN_H_INCLUDED
