
// BUPT_GYM_renshuView.cpp : CBUPT_GYM_renshuView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BUPT_GYM_renshu.h"
#endif

#include "BUPT_GYM_renshuDoc.h"
#include "BUPT_GYM_renshuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBUPT_GYM_renshuView

IMPLEMENT_DYNCREATE(CBUPT_GYM_renshuView, CView)

BEGIN_MESSAGE_MAP(CBUPT_GYM_renshuView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBUPT_GYM_renshuView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBUPT_GYM_renshuView ����/����

CBUPT_GYM_renshuView::CBUPT_GYM_renshuView()
{
	// TODO: �ڴ˴���ӹ������

}

CBUPT_GYM_renshuView::~CBUPT_GYM_renshuView()
{
}

BOOL CBUPT_GYM_renshuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBUPT_GYM_renshuView ����

void CBUPT_GYM_renshuView::OnDraw(CDC* /*pDC*/)
{
	CBUPT_GYM_renshuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CBUPT_GYM_renshuView ��ӡ


void CBUPT_GYM_renshuView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBUPT_GYM_renshuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBUPT_GYM_renshuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBUPT_GYM_renshuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CBUPT_GYM_renshuView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBUPT_GYM_renshuView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBUPT_GYM_renshuView ���

#ifdef _DEBUG
void CBUPT_GYM_renshuView::AssertValid() const
{
	CView::AssertValid();
}

void CBUPT_GYM_renshuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBUPT_GYM_renshuDoc* CBUPT_GYM_renshuView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBUPT_GYM_renshuDoc)));
	return (CBUPT_GYM_renshuDoc*)m_pDocument;
}
#endif //_DEBUG


// CBUPT_GYM_renshuView ��Ϣ�������
