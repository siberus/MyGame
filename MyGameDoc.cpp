
// MyGameDoc.cpp : implementation of the CMyGameDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyGame.h"
#endif

#include "MyGameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyGameDoc

IMPLEMENT_DYNCREATE(CMyGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyGameDoc, CDocument)
END_MESSAGE_MAP()


// CMyGameDoc construction/destruction

CMyGameDoc::CMyGameDoc() noexcept
{
	// TODO: add one-time construction code here
	m_board  = new CMyGameBoard();

}

CMyGameDoc::~CMyGameDoc()
{
	//  Удалить текущую доску
	delete m_board;
	//  Удалить всё из «стека отмены» 
	ClearUndo();
	//  Удалить всё из «стека повтора»
	ClearRedo();

}

BOOL CMyGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// Установка (или сброс) параметров доски 
	m_board->SetupBoard();

	//  Очистка стеков «Отмена/Повтор»
	ClearUndo();
	ClearRedo();
	// (SDI documents will reuse this document)

	return TRUE;
}
void CMyGameDoc::SetNumColors(int nColors) 
{
	// Сначала задаем количество цветов... 
	m_board->SetNumColors(nColors); 
	
	// ...затем устанавливаем параметры игровой доски 
	m_board->SetupBoard(); 
}


int CMyGameDoc::DeleteBlocks(int row, int col)
{
	//  Сохранение текущего состояния доски в «стеке Отмены»
	m_undo.push(new CMyGameBoard(*m_board));
	//  «Очищаем стек Повтора»
	ClearRedo();
	//  Затем удаляем блоки
	int blocks = m_board->DeleteBlocks(row, col);
	//  Очищаем «стек Отмены» в конце игры
	if (m_board->IsGameOver())
		ClearUndo();
	//  Возвращаем количество блоков
	return blocks;
}

void CMyGameDoc::UndoLast()
{
	//Смотрим, есть ли у нас что-нибудь в «стеке Отмены»
	if (m_undo.empty())
		return;
	//  Помещаем текущую доску в «стек Повтора»
	m_redo.push(m_board);
	//  Берем верхний элемент «стека Отмены» и назначаем его текущим
	m_board = m_undo.top();
	m_undo.pop();
}

bool CMyGameDoc::CanUndo()
{
	//  Сначала убеждаемся, что у нас есть возможность сделать «Отмену» действия
	return !m_undo.empty();
}

void CMyGameDoc::RedoLast()
{
	//Смотрим, есть ли у нас что-нибудь в «стеке Повтора»
	if (m_redo.empty())
		return;
	//  Помещаем текущую доску в «стек Отмены»
	m_undo.push(m_board);
	//  Берем верхний элемент «стека Повтора» и назначаем его текущим
	m_board = m_redo.top();
	m_redo.pop();
}

bool CMyGameDoc::CanRedo()
{
	//  Сможем ли сделать «Повтор» действия (не пуст ли стек)
	return !m_redo.empty();
}

void CMyGameDoc::ClearUndo()
{
	//  Очищаем стек «Отмены»
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CMyGameDoc::ClearRedo()
{
	//  Очищаем стек «Повтора»
	while (!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}


// CMyGameDoc serialization

void CMyGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMyGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void CMyGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyGameDoc diagnostics

#ifdef _DEBUG
void CMyGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyGameDoc commands
