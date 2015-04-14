
// BUPT_GYM_renshuDoc.cpp : CBUPT_GYM_renshuDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BUPT_GYM_renshu.h"
#endif

#include "BUPT_GYM_renshuDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBUPT_GYM_renshuDoc

IMPLEMENT_DYNCREATE(CBUPT_GYM_renshuDoc, CDocument)

BEGIN_MESSAGE_MAP(CBUPT_GYM_renshuDoc, CDocument)
END_MESSAGE_MAP()


// CBUPT_GYM_renshuDoc 构造/析构

CBUPT_GYM_renshuDoc::CBUPT_GYM_renshuDoc()
{
	// TODO: 在此添加一次性构造代码

}

CBUPT_GYM_renshuDoc::~CBUPT_GYM_renshuDoc()
{
}

BOOL CBUPT_GYM_renshuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CBUPT_GYM_renshuDoc 序列化

void CBUPT_GYM_renshuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CBUPT_GYM_renshuDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CBUPT_GYM_renshuDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CBUPT_GYM_renshuDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBUPT_GYM_renshuDoc 诊断

#ifdef _DEBUG
void CBUPT_GYM_renshuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBUPT_GYM_renshuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBUPT_GYM_renshuDoc 命令
