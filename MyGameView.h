
// MyGameView.h : interface of the CMyGameView class
//

#pragma once


class CMyGameView : public CView
{
protected: // create from serialization only
	CMyGameView() noexcept;
	DECLARE_DYNCREATE(CMyGameView)

// Attributes
public:
	CMyGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	void ResizeWindow();
	virtual ~CMyGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in MyGameView.cpp
inline CMyGameDoc* CMyGameView::GetDocument() const
   { return reinterpret_cast<CMyGameDoc*>(m_pDocument); }
#endif

