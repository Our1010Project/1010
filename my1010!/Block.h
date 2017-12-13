#ifndef _BLOCK_H
#define _BLOCK_H


namespace Game
{
  class Block{
  public:
    Block();
    Block(int cc,bool ww);

    int color; //��ѡ��int����Ϊ�����Ժ�����ܰ�ͼƬ��Ϊһ��ɫ�����ֻ������ɫ
                //0�е�Colorֵ�������浱ǰ�е������

    bool wait_to_clean;//ZWY
    bool already_scaned;//ZWY

  };

  constexpr int no_color{-1};//��������ɫ
  constexpr int row_number{7};//��0����Ϊ����
  constexpr int column_number{13};//��0����Ϊ12��
  const Block& default_block();//Ĭ��Block

}

#endif // _GAME
