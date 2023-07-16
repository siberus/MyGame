
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

void CMyGameView::OnDraw(CDC* pDC)
{
	// � ������ ������� ��������� �� Document
	CMyGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// ��������� ������� ��������� ��������� ����������
	int nDCSave = pDC->SaveDC();

	// �������� ������� ���������� ������� 
	CRect rcClient; 
	GetClientRect(&rcClient); 
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);

	// ������� ������������ ��� 
	pDC->FillSolidRect(&rcClient, clr);

	// ������� ����� ��� ��������� 
	CBrush br; 
	br.CreateStockObject(HOLLOW_BRUSH); 
	CBrush* pbrOld = pDC->SelectObject(&br);

	// ������ ����� 
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{

			clr = pDoc->GetBoardSpace(row, col);

			// ��������� ������ � ������� �������� ������������ 
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			// ��������� ���� ��������������� ������ 
			pDC->FillSolidRect(&rcBlock, clr);

			// ������ ������ 
			pDC->Rectangle(&rcBlock);
		}
	}
	// ��������������� �������� ���������� 
	pDC->RestoreDC(nDCSave); 
	br.DeleteObject();
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


void CMyGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	ResizeWindow();
}


void CMyGameView::ResizeWindow()
{
	// ������� ��������� �� Document 
	CMyGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// �������� ������� ���������� ������� 
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	// �������� ������� ���� �� ������ �������� ����� ����� 
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	// ������� MoveWindow() �������� ������ ���� ������ 
	GetParentFrame()->MoveWindow(&rcWindow);
}