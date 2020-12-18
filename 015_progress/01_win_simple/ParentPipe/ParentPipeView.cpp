
// ParentPipeView.cpp : CParentPipeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ParentPipe.h"
#endif

#include "ParentPipeDoc.h"
#include "ParentPipeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParentPipeView

IMPLEMENT_DYNCREATE(CParentPipeView, CView)

	BEGIN_MESSAGE_MAP(CParentPipeView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CParentPipeView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_COMMAND(IDM_PIPE_CREATE, &CParentPipeView::OnPipeCreate)
		ON_COMMAND(IDM_PIPE_READ, &CParentPipeView::OnPipeRead)
		ON_COMMAND(IDM_PIPE_WRITE, &CParentPipeView::OnPipeWrite)
	END_MESSAGE_MAP()

	// CParentPipeView 构造/析构

	CParentPipeView::CParentPipeView()
	{
		// TODO: 在此处添加构造代码
		m_hReadPipe=NULL;
		m_hWritePipe=NULL;

	}

	CParentPipeView::~CParentPipeView()
	{
		if (m_hWritePipe)
		{
			CloseHandle(m_hWritePipe);
		}

		if (m_hReadPipe)
		{
			CloseHandle(m_hReadPipe);
		}
	}

	BOOL CParentPipeView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// CParentPipeView 绘制

	void CParentPipeView::OnDraw(CDC* /*pDC*/)
	{
		CParentPipeDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
	}


	// CParentPipeView 打印


	void CParentPipeView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CParentPipeView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CParentPipeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CParentPipeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CParentPipeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CParentPipeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CParentPipeView 诊断

#ifdef _DEBUG
	void CParentPipeView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CParentPipeView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CParentPipeDoc* CParentPipeView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParentPipeDoc)));
		return (CParentPipeDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CParentPipeView 消息处理程序


	void CParentPipeView::OnPipeCreate()
	{
		// TODO: 在此添加命令处理程序代码

		SECURITY_ATTRIBUTES sa;
		sa.bInheritHandle=TRUE;
		sa.lpSecurityDescriptor=NULL;
		sa.nLength=sizeof(SECURITY_ATTRIBUTES);

		if (!CreatePipe(&m_hReadPipe,&m_hWritePipe,&sa,0))
		{
			MessageBox(_T("匿名管道创建失败"));
			return;
		}

		STARTUPINFO sui;
		PROCESS_INFORMATION pi;
		ZeroMemory(&sui,sizeof(STARTUPINFO));
		sui.cb=sizeof(STARTUPINFO);
		sui.dwFlags=STARTF_USESTDHANDLES;
		sui.hStdInput=m_hReadPipe;
		sui.hStdOutput=m_hWritePipe;
		sui.hStdError=GetStdHandle(STD_ERROR_HANDLE);

		if(!CreateProcess("..\\Debug\\PipeChild.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&sui,&pi))
		{
			CloseHandle(m_hReadPipe);
			CloseHandle(m_hWritePipe);
			m_hWritePipe=NULL;
			m_hReadPipe=NULL;
			MessageBox(_T("创建子进程失败"));
			return;
		}

		else
		{
			CloseHandle(pi.hProcess);   //注意此处释放两句柄的原因
			CloseHandle(pi.hThread);
		}


	}


	void CParentPipeView::OnPipeRead()
	{
		// TODO: 在此添加命令处理程序代码

		char buf[100];
		DWORD dwRead;
		if (!ReadFile(m_hReadPipe,buf,100,&dwRead,NULL))
		{
			MessageBox(_T("读取数据失败"));
			return;
		}
		MessageBox(buf);
	}


	void CParentPipeView::OnPipeWrite()
	{
		// TODO: 在此添加命令处理程序代码

		char buf[]="http://www.baidu.com";
		DWORD dwWrite;
		if (!WriteFile(m_hWritePipe,buf,strlen(buf),&dwWrite,NULL))
		{
			MessageBox(_T("数据写入失败"));
			return;
		}

	}
