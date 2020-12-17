// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ChildPipeView.cpp : CChildPipeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChildPipeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_PIPE_READ, &CChildPipeView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CChildPipeView::OnPipeWrite)
END_MESSAGE_MAP()

// CChildPipeView ����/����

CChildPipeView::CChildPipeView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChildPipeView ����

void CChildPipeView::OnDraw(CDC* /*pDC*/)
{
	CChildPipeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CChildPipeView ��ӡ


void CChildPipeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChildPipeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CChildPipeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CChildPipeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CChildPipeView ���

#ifdef _DEBUG
void CChildPipeView::AssertValid() const
{
	CView::AssertValid();
}

void CChildPipeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChildPipeDoc* CChildPipeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChildPipeDoc)));
	return (CChildPipeDoc*)m_pDocument;
}
#endif //_DEBUG


// CChildPipeView ��Ϣ�������


void CChildPipeView::OnPipeRead()
{
	// TODO: �ڴ���������������

	char buf[100];
	ZeroMemory(buf,100);
	DWORD dwRead;
	if (!ReadFile(m_hPipeRead,buf,100,&dwRead,NULL))
	{
		MessageBox(_T("��ȡ����ʧ��"));
		return;
	}
	MessageBox(buf);
}


void CChildPipeView::OnPipeWrite()
{
	// TODO: �ڴ���������������

	char buf[]="�����ܵ����Գ���";
	DWORD dwWrite;
	if (!WriteFile(m_hPipeWrite,buf,strlen(buf)+1,&dwWrite,NULL))
	{
		MessageBox(_T("д������ʧ��"));
		return;
	}
}


void CChildPipeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	m_hPipeRead=GetStdHandle(STD_INPUT_HANDLE);
	m_hPipeWrite=GetStdHandle(STD_OUTPUT_HANDLE);
}
