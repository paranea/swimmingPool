
// BUPT_GYM_renshuDoc.h : CBUPT_GYM_renshuDoc ��Ľӿ�
//


#pragma once


class CBUPT_GYM_renshuDoc : public CDocument
{
protected: // �������л�����
	CBUPT_GYM_renshuDoc();
	DECLARE_DYNCREATE(CBUPT_GYM_renshuDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CBUPT_GYM_renshuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
