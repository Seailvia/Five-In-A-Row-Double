# 五子棋游戏 (FiveInARow)
基于 MFC (Microsoft Foundation Class) 框架开发的经典五子棋桌面游戏，采用 C++ 实现，支持双人对战、落子验证、胜负判定、游戏计时等核心功能。

## 功能特性
- 🎮 双人对战：黑白棋子交替落子，支持棋盘交叉点精准落子
- ✅ 落子验证：防止重复落子、非棋盘区域落子
- 🏆 胜负判定：自动检测横、竖、左斜、右斜四个方向的五子连珠
- ⏱️ 游戏计时：实时显示游戏时长
- 🎨 美观UI：自定义棋子绘制、胜利提示特效、背景图片渲染
- 🔄 重新开局：游戏结束后可一键重启新对局

## 技术栈
- 编程语言：C++
- 开发框架：MFC (Microsoft Foundation Class)
- 开发环境：Visual Studio (支持 MFC 开发的版本)
- 图形绘制：GDI (Graphics Device Interface)

## 项目结构
FiveInARow/
├── CChess.cpp/.h // 棋子类，管理棋子属性与绘制逻辑
├── CChessManager.cpp/.h // 游戏管理器，处理落子、胜负判断等核心逻辑
├── FiveInARow.cpp/.h // 应用程序入口，定义应用程序类行为
├── FiveInARowDlg.cpp/.h // 主对话框，处理界面交互、鼠标事件、计时、胜利提示
├── framework.h // MFC 框架头文件
├── pch.cpp/.h // 预编译头文件
├── resource.h // 资源定义（位图、对话框 ID 等）
└── targetver.h // Windows SDK 版本定义


## 核心类详细说明
### 1. CChess (棋子类)
#### 核心职责
- 管理单个棋子的属性（编号、逻辑坐标、颜色）
- 实现棋子的 GDI 绘制（位图掩码混合渲染）
- 提供棋子属性的访问接口

#### 关键成员
| 成员 | 类型 | 说明 |
|------|------|------|
| m_Num | int | 棋子编号 |
| m_x/m_y | int | 棋子在棋盘上的逻辑坐标 |
| m_Color | COLOR | 棋子颜色（BLACK/WHITE） |
| m_dx/m_dy | static int | 棋盘左上角屏幕坐标 |
| m_d | static double | 棋盘格子间距 |

#### 核心方法
```cpp
// 设置棋子属性
void Set(int num, int x, int y, COLOR color);
// 绘制棋子（掩码混合渲染）
void Show(CDC* pDC);
// 获取棋子颜色/坐标
COLOR GetColor();
int GetX();
int GetY();
```

### 2.CChessManager (游戏管理类)
#### 核心职责
- 游戏逻辑核心：落子验证、胜负判定、棋子管理
- 坐标转换：屏幕像素坐标 → 棋盘逻辑坐标
- 游戏状态重置：新游戏初始化

#### 关键常量
```cpp
#define MAX_ROWS 15    // 棋盘行数
#define MAX_COLS 15    // 棋盘列数
#define MAX_CHESS 225  // 最大棋子数
#define WIN_NUM 5      // 胜利条件（五子连珠）
```

#### 核心方法
```cpp
// 坐标转换：屏幕坐标转逻辑坐标
bool Xy2Xy(int x0, int y0, int &x1, int &y1);
// 添加棋子（落子逻辑）
int Add(int x, int y);
// 胜负判定总入口
bool GameOver();
// 方向判定（横/竖/左斜/右斜）
bool CheckRows();
bool CheckCols();
bool CheckLSlash();
bool CheckRSlash();
// 重置游戏
void NewGame();
```

### 3. CFiveInARowDlg (主对话框类)
#### 核心职责
- 界面交互：鼠标事件处理（落子、开始游戏、关于对话框）
- 计时功能：游戏时长统计与显示
- 胜利提示：自定义美观的胜利弹窗特效
- 绘图渲染：背景图片、棋子绘制

#### 核心方法
```cpp
// 鼠标左键弹起事件（核心交互入口）
afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
// 计时器事件（秒级计时）
afx_msg void OnTimer(UINT_PTR nIDEvent);
// 绘制界面（背景+棋子）
afx_msg void OnPaint();
// 开始新游戏判定
bool NewGame(int x, int y);
// 关于对话框判定
bool About(int x, int y);
// 自定义胜利提示
void ShowVictoryMessage(const CString &strWinner, const CString &strMessage);
```


