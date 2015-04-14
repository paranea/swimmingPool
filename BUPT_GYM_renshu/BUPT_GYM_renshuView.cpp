
// BUPT_GYM_renshuView.cpp : CBUPT_GYM_renshuView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBUPT_GYM_renshuView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBUPT_GYM_renshuView 构造/析构

CBUPT_GYM_renshuView::CBUPT_GYM_renshuView()
{
	// TODO: 在此处添加构造代码

}

CBUPT_GYM_renshuView::~CBUPT_GYM_renshuView()
{
}

BOOL CBUPT_GYM_renshuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBUPT_GYM_renshuView 绘制

void CBUPT_GYM_renshuView::OnDraw(CDC* /*pDC*/)
{
	CBUPT_GYM_renshuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CBUPT_GYM_renshuView 打印


void CBUPT_GYM_renshuView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBUPT_GYM_renshuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBUPT_GYM_renshuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBUPT_GYM_renshuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CBUPT_GYM_renshuView 诊断

#ifdef _DEBUG
void CBUPT_GYM_renshuView::AssertValid() const
{
	CView::AssertValid();
}

void CBUPT_GYM_renshuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBUPT_GYM_renshuDoc* CBUPT_GYM_renshuView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBUPT_GYM_renshuDoc)));
	return (CBUPT_GYM_renshuDoc*)m_pDocument;
}
#endif //_DEBUG


// CBUPT_GYM_renshuView 消息处理程序
