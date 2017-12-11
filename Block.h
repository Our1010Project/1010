#ifndef _BLOCK_H
#define _BLOCK_H


namespace Game
{
  class Block{
  public:
    Block();
    Block(int cc,bool ww);

    int color; //我选了int，因为这样以后可能能把图片作为一个色块而不只是用颜色
                //0行的Color值用来保存当前列的最高行

    bool wait_to_clean;//ZWY
    bool already_scaned;//ZWY

  };

  constexpr int no_color{-1};//不具有颜色
  constexpr int row_number{7};//除0行外为六行
  constexpr int column_number{13};//除0列外为12列
  const Block& default_block();//默认Block

}

#endif // _GAME
