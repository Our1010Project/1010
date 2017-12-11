#ifndef _CLEAN_H
#define _CLEAN_H

#include"Block.h"

#include<vector>

using std::vector;

namespace Game
{
  class Clean{
  private:
    void clean(Block table[row_number][column_number]);
    void scan(Block table[row_number][column_number],int i,int j,vector<int>& same_color_list);

    bool can_be_cleaned(Block table[row_number][column_number]);
    bool same_color(Block table[row_number][column_number],int i1,int j1,int i2,int j2);//(i1,j1):当前，(i2,j2):周围格子
 };
}

#endif // _ACTION_H
