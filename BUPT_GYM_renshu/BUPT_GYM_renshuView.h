
// BUPT_GYM_renshuView.h : CBUPT_GYM_renshuView ��Ľӿ�
//

#pragma once


class CBUPT_GYM_renshuView : public CView
{
protected: // �������л�����
	CBUPT_GYM_renshuView();
	DECLARE_DYNCREATE(CBUPT_GYM_renshuView)

// ����
public:
	CBUPT_GYM_renshuDoc* GetDocument() const;

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

// ʵ��
public:
	virtual ~CBUPT_GYM_renshuView();
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
};

#ifndef _DEBUG  // BUPT_GYM_renshuView.cpp �еĵ��԰汾
inline CBUPT_GYM_renshuDoc* CBUPT_GYM_renshuView::GetDocument() const
   { return reinterpret_cast<CBUPT_GYM_renshuDoc*>(m_pDocument); }
#endif

