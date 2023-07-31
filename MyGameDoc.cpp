
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
	//  ������� ������� �����
	delete m_board;
	//  ������� �� �� ������ ������� 
	ClearUndo();
	//  ������� �� �� ������ �������
	ClearRedo();

}

BOOL CMyGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// ��������� (��� �����) ���������� ����� 
	m_board->SetupBoard();

	//  ������� ������ �������/������
	ClearUndo();
	ClearRedo();
	// (SDI documents will reuse this document)

	return TRUE;
}
void CMyGameDoc::SetNumColors(int nColors) 
{
	// ������� ������ ���������� ������... 
	m_board->SetNumColors(nColors); 
	
	// ...����� ������������� ��������� ������� ����� 
	m_board->SetupBoard(); 
}


int CMyGameDoc::DeleteBlocks(int row, int col)
{
	//  ���������� �������� ��������� ����� � ������ �������
	m_undo.push(new CMyGameBoard(*m_board));
	//  �������� ���� �������
	ClearRedo();
	//  ����� ������� �����
	int blocks = m_board->DeleteBlocks(row, col);
	//  ������� ����� ������� � ����� ����
	if (m_board->IsGameOver())
		ClearUndo();
	//  ���������� ���������� ������
	return blocks;
}

void CMyGameDoc::UndoLast()
{
	//�������, ���� �� � ��� ���-������ � ������ �������
	if (m_undo.empty())
		return;
	//  �������� ������� ����� � ����� �������
	m_redo.push(m_board);
	//  ����� ������� ������� ������ ������� � ��������� ��� �������
	m_board = m_undo.top();
	m_undo.pop();
}

bool CMyGameDoc::CanUndo()
{
	//  ������� ����������, ��� � ��� ���� ����������� ������� ������� ��������
	return !m_undo.empty();
}

void CMyGameDoc::RedoLast()
{
	//�������, ���� �� � ��� ���-������ � ������ �������
	if (m_redo.empty())
		return;
	//  �������� ������� ����� � ����� �������
	m_undo.push(m_board);
	//  ����� ������� ������� ������ ������� � ��������� ��� �������
	m_board = m_redo.top();
	m_redo.pop();
}

bool CMyGameDoc::CanRedo()
{
	//  ������ �� ������� ������� �������� (�� ���� �� ����)
	return !m_redo.empty();
}

void CMyGameDoc::ClearUndo()
{
	//  ������� ���� ��������
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CMyGameDoc::ClearRedo()
{
	//  ������� ���� ��������
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
