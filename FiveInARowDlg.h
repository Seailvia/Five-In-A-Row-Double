
// FiveInARowDlg.h: 头文件
//

#pragma once
#include "CChessManager.h"

// CFiveInARowDlg 对话框
class CFiveInARowDlg : public CDialogEx
{
// 构造
	CChessManager m_Manager;//实现五子棋各项操作
	CFont m_FontTimer; //计时显示字体
	CFont m_FontOver;//游戏结束显示字体
	int m_iTime;//记录游戏开始时间，秒数
	bool m_bState;//游戏开始true;
public:
	CFiveInARowDlg(CWnd* pParent = nullptr);	// 标准构造函数
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);//鼠标左键消息处理函数
	bool NewGame(int x, int y);// 判断是否开始新游戏
	bool About(int x, int y);//判断是否显示游戏说明
	afx_msg void OnTimer(UINT_PTR nIDEvent); //处理计时器消息，显示游戏开始时间
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIVEINAROW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};


﻿// FiveInARowDlg.h: 头文件
