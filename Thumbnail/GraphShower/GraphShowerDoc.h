// GraphShowerDoc.h : CGraphShowerDoc ��Ľӿ�
//


#pragma once


class CGraphShowerDoc : public CDocument
{
protected: // �������л�����
	CGraphShowerDoc();
	DECLARE_DYNCREATE(CGraphShowerDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CGraphShowerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


