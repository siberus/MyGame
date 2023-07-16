
// MyGameView.cpp : implementation of the CMyGameView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyGame.h"
#endif

#include "MyGameDoc.h"
#include "MyGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyGameView

IMPLEMENT_DYNCREATE(CMyGameView, CView)

BEGIN_MESSAGE_MAP(CMyGameView, CView)
END_MESSAGE_MAP()

// CMyGameView construction/destruction

CMyGameView::CMyGameView() noexcept
{
	// TODO: add construction code here

}

CMyGameView::~CMyGameView()
{
}

BOOL CMyGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMyGameView drawing

void CMyGameView::OnDraw(CDC* /*pDC*/)
{
	CMyGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMyGameView diagnostics

#ifdef _DEBUG
void CMyGameView::AssertValid() const
{
	CView::AssertValid();
}

void CMyGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyGameDoc* CMyGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyGameDoc)));
	return (CMyGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyGameView message handlers
