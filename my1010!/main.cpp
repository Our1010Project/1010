#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>


#include "main.h"
#include "my1010.h"
#include "Shape.h"

IMPLEMENT_APP(MyApp)

using namespace std;

bool MyApp::OnInit()
{
    srand(time(NULL));
    My1010 *tetris = new My1010(wxT("my1010"));
    tetris->Centre();
    tetris->Show(true);
    return true;
}



namespace Data{
    void form::init_line(){
        for (int a=1; a<=width; a++){
            grid[0][a]=(rand()%no_of_color + 1);
            Block::set_block(Data::Colours (grid[0][a]))
        }
    }
    void form::init(){
        for (int a=0; a<=(height+1); a++){
            for (int b=0; b<width; b++){
                grid[a][b]=0;
            }
        }
    }
    void form::drop(){
        for (int b=0; b<width; b++){
            int a=0;
            while (grid[a][b]==0 && a<height){
                a=a+1;
            }
            grid[a-1][b]=grid[0][b];
        }
        init_line();
    }
    std::map<int,std::string> clr{
        {0, "no_colour"},
        {1, "red_colour"},
        {2, "ora_coulor"},
        {3,"yel_colour"},
        {4, "gre_colour"},
        {5, "lblu_colour"},
        {6, "dblu_colour"},
        {7, "pur_colour"}
    };
}
