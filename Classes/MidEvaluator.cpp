//
//  MidEvaluator.cpp
//  OseroConsole
//
//  Created by 林　真史 on 2016/04/21.
//  Copyright © 2016年 林　真史. All rights reserved.
//

#include "MidEvaluator.hpp"

using namespace Reversi;

bool MidEvaluator::TableInit = false;
MidEvaluator::EdgeStat MidEvaluator::EdgeTable[TABLE_SIZE];


MidEvaluator::MidEvaluator()
{
    if(!TableInit)
    {
        //
        //	�����N�����Ƀe�[�u���𐶐�
        //
        
        Color line[BOARD_SIZE];
        generateEdge(line, 0);
        
        TableInit = true;
    }
    
    // �d�݌W���̐ݒ� (�S�ǖʋ���)
    
    EvalWeight.mobility_w = 67;
    EvalWeight.liberty_w  = -13;
    EvalWeight.stable_w   = 101;
    EvalWeight.wing_w     = -308;
    EvalWeight.Xmove_w    = -449;
    EvalWeight.Cmove_w    = -552;
}

int MidEvaluator::evaluate(const Board& board)
{
    EdgeStat edgestat;
    CornerStat cornerstat;
    int result;
    
    //
    //	�ӂ̕]��
    //
    
    edgestat  = EdgeTable[idxTop(board)];
//    edgestat += EdgeTable[idxBottom(board)];
//    edgestat += EdgeTable[idxRight(board)];
//    edgestat += EdgeTable[idxLeft(board)];
    
    //
    //	���̕]��
    //
    
    cornerstat = evalCorner(board);
    
    // �m���΂Ɋւ��āA���̐΂�2�񐔂��Ă��܂��Ă����̂ŕ␳�B
    
    edgestat[BLACK].stable -= cornerstat[BLACK].corner;
    edgestat[WHITE].stable -= cornerstat[WHITE].corner;
    
    //
    //	�p�����[�^�̐��`����
    //
    
    result =
		  edgestat[BLACK].stable * EvalWeight.stable_w
    - edgestat[WHITE].stable * EvalWeight.stable_w
    + edgestat[BLACK].wing * EvalWeight.wing_w
    - edgestat[WHITE].wing * EvalWeight.wing_w
    + cornerstat[BLACK].Xmove * EvalWeight.Xmove_w
    - cornerstat[WHITE].Xmove * EvalWeight.Xmove_w
    + edgestat[BLACK].Cmove * EvalWeight.Cmove_w
    - edgestat[WHITE].Cmove * EvalWeight.Cmove_w
    ;
    
    // �J���x�E�����\�萔�̕]��
    
    if(EvalWeight.liberty_w != 0)
    {
        ColorStorage<unsigned> liberty = countLiberty(board);
        result += liberty[BLACK] * EvalWeight.liberty_w;
        result -= liberty[WHITE] * EvalWeight.liberty_w;
    }
    
    // ���݂̎��Ԃ̐F�ɂ��Ă̂݁A�����\�萔�𐔂���
    result +=
		  board.getCurrentColor()
    * board.getMovablePos().size()
    * EvalWeight.mobility_w;
    
    return board.getCurrentColor() * result;
    
}

void MidEvaluator::generateEdge(Color edge[], unsigned count)
{
    if(count == BOARD_SIZE)
    {
        //
        //	���̃p�^�[���͊��������̂ŁA�ǖʂ̃J�E���g
        //
        
        EdgeStat stat;
        
        stat[BLACK] = evalEdge(edge, BLACK);
        stat[WHITE] = evalEdge(edge, WHITE);
        
        EdgeTable[idxLine(edge)] = stat;
        
        return;
    }
    
    // �ċA�I�ɑS�Ẵp�^�[�����ԗ�
    
    edge[count] = EMPTY;
    generateEdge(edge, count +1);
    
    edge[count] = BLACK;
    generateEdge(edge, count +1);
    
    edge[count] = WHITE;
    generateEdge(edge, count +1);
    
    return ;
    
}

//
//	evalEdge
//	�ӂ̃p�����[�^�𐔂���
//

MidEvaluator::EdgeParam MidEvaluator::evalEdge(Color line[], Color color) const
{
    EdgeParam edgeparam = {0, 0, 0, 0};
    
    unsigned x;
    
    //
    //	�E�B���O���̃J�E���g
    //
    
    if(line[0] == EMPTY && line[7] == EMPTY)
    {
        x = 2;
        while(x <= 5)
        {
            if(line[x] != color) break;
            x++;
        }
        if(x == 6) // ���Ȃ��Ƃ��u���b�N���ł��Ă���
        {
            if(line[1] == color && line[6] == EMPTY)
                edgeparam.wing = 1;
            else if(line[1] == EMPTY && line[6] == color)
                edgeparam.wing = 1;
            else if(line[1] == color && line[6] == color)
                edgeparam.mountain = 1;
        }
        else // �����ȊO�̏ꍇ�ɁA���ɗאڂ����ʒu�ɒu���Ă�����
        {
            if(line[1] == color)
                edgeparam.Cmove++;
            if(line[6] == color)
                edgeparam.Cmove++;
        }
    }
    
    //
    //	�m���΂̃J�E���g
    //
    
    // �������E�����ɑ���
    for(x = 0; x < 8; x++)
    {
        if(line[x] != color) break;
        edgeparam.stable++;
    }
    
    if(edgeparam.stable < 8)
    {
        // �E�������̑������K�v
        for(x = 7; x > 0; x--)
        {
            if(line[x] != color) break;
            edgeparam.stable++;
        }
    }
    
    
    return edgeparam;
    
}

//
//	evalCorner
//	���̃p�����[�^�𒲂ׂ��B���̊֐��͊e�]�����Ɏg���B
//

MidEvaluator::CornerStat MidEvaluator::evalCorner(const Board &board) const
{
    CornerStat cornerstat;
    
    cornerstat[BLACK].corner=0; cornerstat[BLACK].Xmove=0;
    cornerstat[WHITE].corner=0; cornerstat[WHITE].Xmove=0;
    
    //	����
    cornerstat[board.getColor(Point(1, 1))].corner++;
    if(board.getColor(Point(1, 1)) == EMPTY) cornerstat[board.getColor(Point(2, 2))].Xmove++;
    
    //	����
    cornerstat[board.getColor(Point(1, 8))].corner++;
    if(board.getColor(Point(1, 8)) == EMPTY) cornerstat[board.getColor(Point(2, 7))].Xmove++;
    
    //	�E��
    cornerstat[board.getColor(Point(8, 7))].corner++;
    if(board.getColor(Point(8, 8)) == EMPTY) cornerstat[board.getColor(Point(7, 7))].Xmove++;
    
    //	�E��
    cornerstat[board.getColor(Point(8, 1))].corner++;
    if(board.getColor(Point(8, 1)) == EMPTY) cornerstat[board.getColor(Point(7, 2))].Xmove++;
    
    return cornerstat;
    
}

ColorStorage<unsigned> MidEvaluator::countLiberty(const Board &board) const
{
    ColorStorage<unsigned> liberty;
    
    liberty[BLACK] = 0; liberty[WHITE] = 0; liberty[EMPTY] = 0;
    
    for(unsigned int x = 1; x <= BOARD_SIZE; x++)
    {
        for(unsigned int y = 1; y <= BOARD_SIZE; y++)
        {
            Point p(x, y);
//            liberty[board.getColor(p)] += board.getLiberty(p);
        }
    }
    
    return liberty;
    
}


////////////////////////////////////////////////////////////////////////
//
//	�e�ӏ��ɂ��ẴC���f�b�N�X�̌v�Z
//	�p�t�H�[�}���X�����̂��ߌʂ̃C�����C���֐��Ńx�^�ɏ���
//

unsigned MidEvaluator::idxTop(const Board &board) const
{
    unsigned index;
    
    index =
    2187 * (board.getColor(Point(1, 1)) + 1)
    +729 * (board.getColor(Point(2, 1)) + 1)
    +243 * (board.getColor(Point(3, 1)) + 1)
    + 81 * (board.getColor(Point(4, 1)) + 1)
    + 27 * (board.getColor(Point(5, 1)) + 1)
    +  9 * (board.getColor(Point(6, 1)) + 1)
    +  3 * (board.getColor(Point(7, 1)) + 1)
    +  1 * (board.getColor(Point(8, 1)) + 1);
    
    return index;
}

unsigned MidEvaluator::idxBottom(const Board &board) const
{
    unsigned index;
    
    index =
    2187 * (board.getColor(Point(1, 8)) + 1)
    +729 * (board.getColor(Point(2, 8)) + 1)
    +243 * (board.getColor(Point(3, 8)) + 1)
    + 81 * (board.getColor(Point(4, 8)) + 1)
    + 27 * (board.getColor(Point(5, 8)) + 1)
    +  9 * (board.getColor(Point(6, 8)) + 1)
    +  3 * (board.getColor(Point(7, 8)) + 1)
    +  1 * (board.getColor(Point(8, 8)) + 1);
    
    return index;
    
}

unsigned MidEvaluator::idxRight(const Board &board) const
{
    unsigned index;
    
    index =
    2187 * (board.getColor(Point(8, 1)) + 1)
    +729 * (board.getColor(Point(8, 2)) + 1)
    +243 * (board.getColor(Point(8, 3)) + 1)
    + 81 * (board.getColor(Point(8, 4)) + 1)
    + 27 * (board.getColor(Point(8, 5)) + 1)
    +  9 * (board.getColor(Point(8, 6)) + 1)
    +  3 * (board.getColor(Point(8, 7)) + 1)
    +  1 * (board.getColor(Point(8, 8)) + 1);
    
    return index;
    
}

unsigned MidEvaluator::idxLeft(const Board &board) const
{
    unsigned index;
    
    index =
    2187 * (board.getColor(Point(1, 1)) + 1)
    +729 * (board.getColor(Point(1, 2)) + 1)
    +243 * (board.getColor(Point(1, 3)) + 1)
    + 81 * (board.getColor(Point(1, 4)) + 1)
    + 27 * (board.getColor(Point(1, 5)) + 1)
    +  9 * (board.getColor(Point(1, 6)) + 1)
    +  3 * (board.getColor(Point(1, 7)) + 1)
    +  1 * (board.getColor(Point(1, 8)) + 1);
    
    return index;
    
}
