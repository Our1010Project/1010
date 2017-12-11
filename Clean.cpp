#include"Clean.h"

#include<vector>


namespace Game
{
    void Clean::clean(Block table[row_number][column_number]){}

    void Clean::scan(Block table[row_number][column_number],int i,int j,vector<int>&same_color_list)
    {
      if (same_color(table,i,j,i+1,j))             //上
        if (!table[i+1][j].already_scaned){
          same_color_list.push_back(i+1);
          same_color_list.push_back(j);
          table[i+1][j].already_scaned=true;
          scan(table,i+1,j,same_color_list);
        }
      if (same_color(table,i,j,i-1,j))             //下
        if (!table[i-1][j].already_scaned){
          same_color_list.push_back(i-1);
          same_color_list.push_back(j);
          table[i-1][j].already_scaned=true;
          scan(table,i-1,j,same_color_list);
        }
      if (same_color(table,i,j,i,j-1))             //左
        if (!table[i][j-1].already_scaned){
          same_color_list.push_back(i);
          same_color_list.push_back(j-1);
          table[i][j-1].already_scaned=true;
          scan(table,i,j-1,same_color_list);
        }
      if (same_color(table,i,j,i,j+1))             //右
        if (!table[i][j+1].already_scaned){
          same_color_list.push_back(i);
          same_color_list.push_back(j+1);
          table[i][j+1].already_scaned=true;
          scan(table,i,j+1,same_color_list);
        }

    }

    bool Clean::same_color(Block table[row_number][column_number],int i1,int j1,int i2,int j2)
    {
      if (1<=j2&&j2<column_number)
        if (1<=i2&&i2<=table[0][j2].color)
          if (table[i1][j1].color==table[i2][j2].color){
            return true;
          }
      return false;
    }

    bool Clean::can_be_cleaned(Block table[row_number][column_number])
    {
      bool cb_cleaned{false};
      for (int j=1;j<column_number;++j)
      for (int i=1;i<=table[0][j].color;++i){
        table[i][j].already_scaned=false;
        table[i][j].wait_to_clean=false;
      }

      for (int j=1;j<column_number;++j)
      for (int i=1;i<=table[0][j].color;++i){
        if (!table[i][j].already_scaned)
        {
          vector<int> same_color_list{i,j};
          table[i][j].already_scaned=true;
          scan(table,i,j,same_color_list);
          if (same_color_list.size()>=6){                                    //以后在这里可以加算分数
              cb_cleaned=true;
              for(int k=0;k<same_color_list.size();k+=2){
                table[same_color_list[k]][same_color_list[k+1]].wait_to_clean=true;
              }
          }
        }
      }

    }






}
