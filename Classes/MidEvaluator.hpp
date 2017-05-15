//
//  MidEvaluator.hpp
//  OseroConsole
//
//  Created by 林　真史 on 2016/04/21.
//  Copyright © 2016年 林　真史. All rights reserved.
//

#ifndef MidEvaluator_hpp
#define MidEvaluator_hpp

#include "Evaluator.hpp"

class MidEvaluator : public Evaluator
{
private:
    
    struct EdgeParam
    {
        EdgeParam &operator +=(const EdgeParam &src)
        {
            stable += src.stable;
            wing += src.wing;
            mountain += src.mountain;
            Cmove += src.Cmove;
            
            return *this;
        }
        
        short stable; // �m���΂̌�
        short wing; // �E�C���O�̌�
        short mountain; // �R�̌�
        short Cmove; // �댯��C�ł��̌�
    };
    
    struct CornerParam
    {
        short corner; // ���ɂ����΂̐�
        short Xmove;  // �댯��X�ł��̌�
    };
    
    // �d�݌W�����K�肷���\����
    struct Weight
    {
        int mobility_w;
        int liberty_w;
        int stable_w;
        int wing_w;
        int Xmove_w;
        int Cmove_w;
    } EvalWeight;
    
    typedef ColorStorage<EdgeParam> EdgeStat;
    typedef ColorStorage<CornerParam> CornerStat;
    
    static const unsigned TABLE_SIZE = 6561; // 3^8
    static EdgeStat EdgeTable[TABLE_SIZE];
    static bool TableInit;
    
    void generateEdge(Color line[], unsigned index);
    EdgeParam evalEdge(Color line[], Color color) const;
    CornerStat evalCorner(const Board &) const;
    
    inline unsigned idxTop(const Board &) const;
    inline unsigned idxBottom(const Board &) const;
    inline unsigned idxRight(const Board &) const;
    inline unsigned idxLeft(const Board &) const;
    
    ColorStorage<unsigned> countLiberty(const Board& board) const;
    
    unsigned idxLine(Color l[])
    {
        return 3*(3*(3*(3*(3*(3*(3*(l[0]+1)+l[1]+1)+l[2]+1)+l[3]+1)+l[4]+1)+l[5]+1)+l[6]+1)+l[7]+1;
    }
    
public:
    
    MidEvaluator();
    int evaluate(const Board& board);
    
};



#endif /* MidEvaluator_hpp */
