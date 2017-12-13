#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>


#include "main.h"
#include "my1010.h"


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    srand(time(NULL));
    My1010 *tetris = new My1010(wxT("my1010"));
    tetris->Centre();
    tetris->Show(true);

    return true;
}



namespace Data{
    void init_line(){
        for (int a=1; a<=width; a++){
            grid[0][a]=(rand()%no_of_color + 1);
        }
    }
    void init(){
        for (int a=0; a<=(height+1); a++){
            for (int b=0; b<width; b++){
                grid[a][b]=0;
            }
        }
    }
    void drop(){
        for (int b=0; b<width; b++){
            int a=0;
            while (grid[a][b]==0 && a<height){
                a=a+1;
            }
            grid[a-1][b]=grid[0][b];
        }
        init_line();
    }
}
