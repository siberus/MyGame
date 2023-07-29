
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDifficult3colors();
	afx_msg void OnUpdateDifficult3colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficult4colors();
	afx_msg void OnUpdateDifficult4colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficult5colors();
	afx_msg void OnUpdateDifficult5colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficult6colors();
	afx_msg void OnUpdateDifficult6colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficult7colors();
	afx_msg void OnUpdateDifficult7colors(CCmdUI* pCmdUI);

	void setColorCount(int numColors);
	void checkColorCount(CCmdUI* pCmdUI, int numColors);
};

#ifndef _DEBUG  // debug version in MyGameView.cpp
inline CMyGameDoc* CMyGameView::GetDocument() const
   { return reinterpret_cast<CMyGameDoc*>(m_pDocument); }
#endif

