#pragma once
#include "CChess.h"
#define MAX_ROWS 15					 // 棋盘行数
#define MAX_COLS 15					 // 棋盘列数
#define MAX_CHESS MAX_ROWS *MAX_COLS // 最多落子数
#define WIN_NUM 5					 // 赢棋标准(连续五子)
class CChessManager
{
	CChess m_aChess[MAX_CHESS]; // 保存落子信息对象数组
	int m_nChess;				// 落子个数
	COLOR m_Color;				// 当前将要落子的颜色
	bool CheckRows();			// 检查行是否达到赢棋标准
	bool CheckCols();			// 检查列是否达到赢棋标准
	bool CheckLSlash();			// 检查左斜线"\"方向是否达到赢棋标准
	bool CheckRSlash();			// 检查右斜线"/"方向是否达到赢棋标准
public:
	CChessManager();
	~CChessManager();
	void NewGame()
	{
		m_nChess = 0;
		m_Color = BLACK;
	}																// 开始新的一局
	bool Xy2Xy(int x0, int y0, int &x1, int &y1);					// 物理坐标转为逻辑坐标，成功返回true
	int Add(int x, int y);											// 在物理坐标x、 y处落子，成功返回0;没点中返回1;重复返回2
	void Show(CDC *pDC);											// 显示所有棋子
	bool GameOver();												// 判断游戏是否结束
	COLOR GetWinner() { return m_aChess[m_nChess - 1].GetColor(); } // 取得获胜方棋子颜色
	CChess *GetQz(int x, int y);									// 取得指定 逻辑坐标的棋子，无则返回空
};