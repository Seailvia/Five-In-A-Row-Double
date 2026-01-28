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

## 核心实现细节
### 1. 棋子绘制（掩码混合渲染）
通过 GDI 位图掩码技术实现棋子透明背景渲染，核心代码：

```cpp
void CChess::Show(CDC* pDC) {
    CBitmap bmpMask;  // 掩码位图
    bmpMask.LoadBitmap(IDB_BITMAP_MASK);  // 加载掩码位图资源
    CBitmap bmpQz;    // 棋子位图
    if (m_Color == WHITE)  // 判断棋子颜色
        bmpQz.LoadBitmap(IDB_BITMAP_BZ);  // 加载白色棋子位图
    else
        bmpQz.LoadBitmap(IDB_BITMAP_HZ);  // 加载黑色棋子位图
    BITMAP bm;  // 位图信息
    bmpQz.GetObject(sizeof(BITMAP), &bm);  // 获取位图信息
    CDC mDc0;  // 内存DC（掩码）
    mDc0.CreateCompatibleDC(pDC);
    CBitmap* pOldBitmapMask = mDc0.SelectObject(&bmpMask);
    CDC mDc1;  // 内存DC（棋子）
    mDc1.CreateCompatibleDC(pDC);
    CBitmap* pOldBitmapQz = mDc1.SelectObject(&bmpQz);
    // 掩码混合渲染
    pDC->BitBlt(m_dx + m_x * m_d, m_dy + m_y * m_d, bm.bmWidth, bm.bmHeight, &mDc0, 0, 0, SRCAND);
    pDC->BitBlt(m_dx + m_x * m_d, m_dy + m_y * m_d, bm.bmWidth, bm.bmHeight, &mDc1, 0, 0, SRCPAINT);
    // 恢复资源
    mDc1.SelectObject(pOldBitmapMask);
    mDc0.SelectObject(pOldBitmapQz);
}
```

### 2. 落子坐标转换
将屏幕像素坐标转换为棋盘 15x15 逻辑坐标，通过距离判断有效落子点：

```cpp
bool CChessManager::Xy2Xy(int x0, int y0, int &x1, int &y1)
{
    int x, y;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
        {
            x = CChess::m_dx + i * CChess::m_d + CChess::m_d * 0.5;
            y = CChess::m_dy + j * CChess::m_d + CChess::m_d * 0.5;
            if (sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0)) < 15)
            {
                x1 = i, y1 = j;
                return true;
            }
        }
    return false;
}
```

### 3. 胜负判定（横向示例）
遍历棋盘行，统计连续同色棋子数量，达到 5 则判定胜利：

```cpp
bool CChessManager::CheckRows()
{
    CChess *pQz;
    COLOR color;
    int iCount;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        iCount = 0;
        for (int j = 0; j < MAX_COLS; j++)
            if (pQz = GetQz(j, i))
            {
                if (iCount == 0)
                {
                    color = pQz->GetColor();
                    iCount++;
                }
                else if (color == pQz->GetColor())
                {
                    iCount++;
                    if (iCount == WIN_NUM)
                        return true;
                }
                else
                {
                    color = pQz->GetColor();
                    iCount = 1;
                }
            }
            else
                iCount = 0;
    }
    return false;
}
```

## 编译运行
### 环境要求
Visual Studio 2017/2019/2022（需安装 MFC 组件）

Windows 7/10/11 操作系统（32/64 位）

确保项目配置为「使用 MFC 的 DLL」或「使用 MFC 的静态库」

### 编译步骤
1. 克隆仓库到本地：

```bash
git clone https://github.com/your-username/FiveInARow.git
```

2. 用 Visual Studio 打开项目文件（.sln）

3. 确认项目属性配置：

- 「常规」→「MFC 的使用」：选择「使用 MFC 的 DLL」或「静态库」
- 「高级」→「字符集」：建议使用「使用多字节字符集」

4. 编译项目（Ctrl + Shift + B）

5. 运行生成的可执行文件（FiveInARow.exe）

## 游戏操作指南
1. 启动游戏后，点击界面指定 “开始” 区域（35,150 - 200,185 像素范围）开启新游戏

2. 鼠标左键点击棋盘交叉点落子，黑白棋子自动交替

3. 落子规则：

- 仅可在棋盘交叉点落子（距离交叉点 < 15 像素判定为有效）
- 不可在已有棋子位置重复落子

4. 五子连珠后游戏结束，弹出胜利提示（带文字特效），可选择：

- 「是」：重新开始新对局
- 「否」：保留当前界面

5. 点击 “关于” 区域（35,70 - 200,95 像素范围）查看游戏说明

6. 按 Esc 键可退出游戏

## 资源文件说明
| 资源 ID | 说明 |
|---------|------|
| IDB_BITMAP_BK | 游戏背景位图 |
| IDB_BITMAP_BZ | 白色棋子位图 |
| IDB_BITMAP_HZ | 黑色棋子位图 |
| IDB_BITMAP_MASK | 棋子掩码位图（用于透明渲染） |
| IDD_ABOUTBOX | 关于对话框资源 |
| IDD_FIVEINAROW_DIALOG | 主对话框资源 |
