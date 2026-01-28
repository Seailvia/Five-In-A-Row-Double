#include "pch.h"
#include "CChess.h"
//#include "stdafx.h"
#include "CChess.h"
#include "Resource.h"

int CChess::m_dx = 271;		//该坐标可根据背景图调整
int CChess::m_dy = 68;		//该坐标可根据背景图调整
double CChess::m_d = 36.5;	//该间距可根据背景图调整
CChess::CChess() {
}
CChess::~CChess() {
}

void CChess::Set(int num, int x, int y, COLOR color) {

	m_Num = num;	//设置落子序号
	m_x = x;		//设置落子逻辑坐标x
	m_y = y;		//设置落子逻辑坐标y
	m_Color = color;//设置落子颜色
}

void CChess::Show(CDC* pDC) {
	CBitmap bmpMask;//棋子位图掩码
	bmpMask.LoadBitmap(IDB_BITMAP_MASK);//载入棋子掩码位图资源
	CBitmap bmpQz;//棋子位图
	if (m_Color == WHITE)//判断棋子颜色
		bmpQz.LoadBitmap(IDB_BITMAP_BZ);//载入白色棋子位图资源
	else
		bmpQz.LoadBitmap(IDB_BITMAP_HZ);//载入黑色棋子位图资源
	BITMAP bm;	//位图信息
	bmpQz.GetObject(sizeof(BITMAP), &bm);//取得位图信息
	CDC mDc0;	//内存DC,用来显示棋子位图掩码
	mDc0.CreateCompatibleDC(pDC);//创建用来显示棋子位图掩码的DC
	CBitmap* pOldBitmapMask = mDc0.SelectObject(&bmpMask);
	CDC mDc1;	//内存DC,用来显示棋子位图
	mDc1.CreateCompatibleDC(pDC);//创建用来显示棋子位图的DC
	CBitmap* pOldBitmapQz = mDc1.SelectObject(&bmpQz);
	//将掩码位图(棋子区域黑色，其他区域白色)与棋盘与运算，将棋子区域置黑，其他区域不变
	pDC->BitBlt(m_dx + m_x * m_d, m_dy + m_y * m_d, bm.bmWidth, bm.bmHeight, &mDc0, 0, 0, SRCAND);
	//将棋子位图(棋子区域正常，其他区域黑色)与棋盘异或运算，显示棋子，dth bm. bmHeight,
	pDC->BitBlt(m_dx + m_x * m_d, m_dy + m_y * m_d, bm.bmWidth, bm.bmHeight, &mDc1, 0, 0, SRCPAINT);
	mDc1.SelectObject(pOldBitmapMask);
	mDc0.SelectObject(pOldBitmapQz);
}