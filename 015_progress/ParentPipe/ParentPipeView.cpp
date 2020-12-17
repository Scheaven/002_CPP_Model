
// ParentPipeView.cpp : CParentPipeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
		// ��׼��ӡ����
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CParentPipeView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_COMMAND(IDM_PIPE_CREATE, &CParentPipeView::OnPipeCreate)
		ON_COMMAND(IDM_PIPE_READ, &CParentPipeView::OnPipeRead)
		ON_COMMAND(IDM_PIPE_WRITE, &CParentPipeView::OnPipeWrite)
	END_MESSAGE_MAP()

	// CParentPipeView ����/����

	CParentPipeView::CParentPipeView()
	{
		// TODO: �ڴ˴���ӹ������
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
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// CParentPipeView ����

	void CParentPipeView::OnDraw(CDC* /*pDC*/)
	{
		CParentPipeDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	}


	// CParentPipeView ��ӡ


	void CParentPipeView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CParentPipeView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CParentPipeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CParentPipeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
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


	// CParentPipeView ���

#ifdef _DEBUG
	void CParentPipeView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CParentPipeView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CParentPipeDoc* CParentPipeView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParentPipeDoc)));
		return (CParentPipeDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CParentPipeView ��Ϣ�������


	void CParentPipeView::OnPipeCreate()
	{
		// TODO: �ڴ���������������

		SECURITY_ATTRIBUTES sa;
		sa.bInheritHandle=TRUE;
		sa.lpSecurityDescriptor=NULL;
		sa.nLength=sizeof(SECURITY_ATTRIBUTES);

		if (!CreatePipe(&m_hReadPipe,&m_hWritePipe,&sa,0))
		{
			MessageBox(_T("�����ܵ�����ʧ��"));
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
			MessageBox(_T("�����ӽ���ʧ��"));
			return;
		}

		else
		{
			CloseHandle(pi.hProcess);   //ע��˴��ͷ��������ԭ��
			CloseHandle(pi.hThread);
		}


	}


	void CParentPipeView::OnPipeRead()
	{
		// TODO: �ڴ���������������

		char buf[100];
		DWORD dwRead;
		if (!ReadFile(m_hReadPipe,buf,100,&dwRead,NULL))
		{
			MessageBox(_T("��ȡ����ʧ��"));
			return;
		}
		MessageBox(buf);
	}


	void CParentPipeView::OnPipeWrite()
	{
		// TODO: �ڴ���������������

		char buf[]="http://www.baidu.com";
		DWORD dwWrite;
		if (!WriteFile(m_hWritePipe,buf,strlen(buf),&dwWrite,NULL))
		{
			MessageBox(_T("����д��ʧ��"));
			return;
		}

	}
