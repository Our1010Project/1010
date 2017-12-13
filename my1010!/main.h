#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <map>

#include <wx/wx.h>

namespace Data{
    const int width {10};
    const int height {10};
    const int no_of_color{7};
    std::map<int,std::string> clr;
    
    int grid[width][height+1];
    class form{
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
