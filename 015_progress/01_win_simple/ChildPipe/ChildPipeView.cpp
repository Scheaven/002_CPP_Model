// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// ChildPipeView.cpp : CChildPipeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ChildPipe.h"
#endif

#include "ChildPipeDoc.h"
#include "ChildPipeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildPipeView

IMPLEMENT_DYNCREATE(CChildPipeView, CView)

BEGIN_MESSAGE_MAP(CChildPipeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildPipeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_READ, &CChildPipeView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CChildPipeView::OnPipeWrite)
END_MESSAGE_MAP()

// CChildPipeView 构造/析构

CChildPipeView::CChildPipeView()
{
	// TODO: 在此处添加构造代码
	m_hPipeRead=NULL;
	m_hPipeWrite=NULL;

}

CChildPipeView::~CChildPipeView()
{
	if (m_hPipeWrite)
	{
		CloseHandle(m_hPipeWrite);
	}

	if (m_hPipeRead)
	{
		CloseHandle(m_hPipeRead);
	}
}

BOOL CChildPipeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChildPipeView 绘制

void CChildPipeView::OnDraw(CDC* /*pDC*/)
{
	CChildPipeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CChildPipeView 打印


void CChildPipeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChildPipeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CChildPipeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CChildPipeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CChildPipeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChildPipeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CChildPipeView 诊断

#ifdef _DEBUG
void CChildPipeView::AssertValid() const
{
	CView::AssertValid();
}

void CChildPipeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChildPipeDoc* CChildPipeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChildPipeDoc)));
	return (CChildPipeDoc*)m_pDocument;
}
#endif //_DEBUG


// CChildPipeView 消息处理程序


void CChildPipeView::OnPipeRead()
{
	// TODO: 在此添加命令处理程序代码

	char buf[100];
	ZeroMemory(buf,100);
	DWORD dwRead;
	if (!ReadFile(m_hPipeRead,buf,100,&dwRead,NULL))
	{
		MessageBox(_T("读取数据失败"));
		return;
	}
	MessageBox(buf);
}


void CChildPipeView::OnPipeWrite()
{
	// TODO: 在此添加命令处理程序代码

	char buf[]="匿名管道测试程序";
	DWORD dwWrite;
	if (!WriteFile(m_hPipeWrite,buf,strlen(buf)+1,&dwWrite,NULL))
	{
		MessageBox(_T("写入数据失败"));
		return;
	}
}


void CChildPipeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_hPipeRead=GetStdHandle(STD_INPUT_HANDLE);
	m_hPipeWrite=GetStdHandle(STD_OUTPUT_HANDLE);
}
