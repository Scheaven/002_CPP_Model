
// ParentPipeView.h : CParentPipeView ��Ľӿ�
//

#pragma once


class CParentPipeView : public CView
{
protected: // �������л�����
	CParentPipeView();
	DECLARE_DYNCREATE(CParentPipeView)

// ����
public:
	CParentPipeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

private:
	HANDLE m_hReadPipe;
	HANDLE m_hWritePipe;

// ʵ��
public:
	virtual ~CParentPipeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPipeCreate();
	afx_msg void OnPipeRead();
	afx_msg void OnPipeWrite();
};

#ifndef _DEBUG  // ParentPipeView.cpp �еĵ��԰汾
inline CParentPipeDoc* CParentPipeView::GetDocument() const
   { return reinterpret_cast<CParentPipeDoc*>(m_pDocument); }
#endif

