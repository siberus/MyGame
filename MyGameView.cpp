
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
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DIFFICULT_3COLORS, &CMyGameView::OnDifficult3colors)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULT_3COLORS, &CMyGameView::OnUpdateDifficult3colors)
	ON_COMMAND(ID_DIFFICULT_4COLORS, &CMyGameView::OnDifficult4colors)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULT_4COLORS, &CMyGameView::OnUpdateDifficult4colors)
	ON_COMMAND(ID_DIFFICULT_5COLORS, &CMyGameView::OnDifficult5colors)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULT_5COLORS, &CMyGameView::OnUpdateDifficult5colors)
	ON_COMMAND(ID_DIFFICULT_6COLORS, &CMyGameView::OnDifficult6colors)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULT_6COLORS, &CMyGameView::OnUpdateDifficult6colors)
	ON_COMMAND(ID_DIFFICULT_7COLORS, &CMyGameView::OnDifficult7colors)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULT_7COLORS, &CMyGameView::OnUpdateDifficult7colors)
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
	// В начале создаем указатель на Document
	CMyGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// Сохраняем текущее состояние контекста устройства
	int nDCSave = pDC->SaveDC();

	// Получаем размеры клиентской области 
	CRect rcClient; 
	GetClientRect(&rcClient); 
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);

	// Сначала отрисовываем фон 
	pDC->FillSolidRect(&rcClient, clr);

	// Создаем кисть для рисования 
	CBrush br; 
	br.CreateStockObject(HOLLOW_BRUSH); 
	CBrush* pbrOld = pDC->SelectObject(&br);

	// Рисуем блоки 
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{

			clr = pDoc->GetBoardSpace(row, col);

			// Вычисляем размер и позицию игрового пространства 
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			// Заполняем блок соответствующим цветом 
			pDC->FillSolidRect(&rcBlock, clr);

			// Рисуем контур 
			pDC->Rectangle(&rcBlock);
		}
	}
	// Восстанавливаем контекст устройства 
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

	// TODO: добавьте специализированный код или вызов базового класса
	ResizeWindow();
}


void CMyGameView::ResizeWindow()
{
	// Создаем указатель на Document 
	CMyGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Получаем размеры клиентской области 
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	// Изменяем размеры окна на основе размеров нашей доски 
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	// Функция MoveWindow() изменяет размер окна фрейма 
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CMyGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	// Вначале создаем указатель на Document 
	CMyGameDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc); 
	if (!pDoc) 
		return;

	// Получаем индекс строки и столбца элемента, по которому был осуществлен клик мышкой 
	int row = point.y / pDoc->GetHeight(); 
	int col = point.x / pDoc->GetWidth();

	// Удаляем блоки из Document 
	int count = pDoc->DeleteBlocks(row, col);

	// Проверяем, было ли удаление блоков 
	if (count > 0) 
	{ 
		// Перерисовываем View 
		Invalidate(); 
		UpdateWindow(); 
		
		// Проверяем, закончилась ли игра 
		if (pDoc->IsGameOver()) 
		{
			// Получаем количество оставшихся блоков 
			int remaining = pDoc->GetRemainingCount(); 
			CString message; 
			message.Format(_T("No more moves left\nBlocks remaining: %d"), 
				remaining); 
			
			// Отображаем пользователю результат игры 
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION); 
		} 
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMyGameView::setColorCount(int numColors) 
{
	// Сначала получаем указатель на документ 
	CMyGameDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc); 
	if(!pDoc) 
		return; 
	// Устанавливаем количество цветов 
	pDoc->SetNumColors(numColors); 
	// Перерисовываем View 
	Invalidate(); 
	UpdateWindow(); 
} 
void CMyGameView::checkColorCount(CCmdUI* pCmdUI, int numColors)
{
	// Сначала получаем указатель на Document 
	CMyGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); 
	if(!pDoc) 
		return; 
	// Проверка установленного уровня сложности 
	pCmdUI->SetCheck(pDoc->GetNumColors() ==numColors);
}
void CMyGameView::OnDifficult3colors()
{
	// TODO: добавьте свой код обработчика команд
	setColorCount(3);
}


void CMyGameView::OnUpdateDifficult3colors(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	checkColorCount(pCmdUI, 3);
}


void CMyGameView::OnDifficult4colors()
{
	// TODO: добавьте свой код обработчика команд
	setColorCount(4);
}


void CMyGameView::OnUpdateDifficult4colors(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	checkColorCount(pCmdUI, 4);
}


void CMyGameView::OnDifficult5colors()
{
	// TODO: добавьте свой код обработчика команд
	setColorCount(5);
}

void CMyGameView::OnUpdateDifficult5colors(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	checkColorCount(pCmdUI, 5);
}


void CMyGameView::OnDifficult6colors()
{
	// TODO: добавьте свой код обработчика команд
	setColorCount(6);
}


void CMyGameView::OnUpdateDifficult6colors(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	checkColorCount(pCmdUI, 6);
}


void CMyGameView::OnDifficult7colors()
{
	// TODO: добавьте свой код обработчика команд
	setColorCount(7);
}


void CMyGameView::OnUpdateDifficult7colors(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	checkColorCount(pCmdUI, 7);
}
