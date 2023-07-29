
// MyGameDoc.h : interface of the CMyGameDoc class
//


#pragma once

#include "CMyGameBoard.h"

class CMyGameDoc : public CDocument
{
protected: // create from serialization only
	CMyGameDoc() noexcept;
	DECLARE_DYNCREATE(CMyGameDoc)

// Attributes
public:

// Operations
public:

	// Геттеры для получения информации о параметрах игрового поля 
	COLORREF GetBoardSpace(int row, int col) 
	{ 
		return m_board.GetBoardSpace(row, col); 
	} 
	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	void SetWidth(int nWidth) { m_board.SetWidth(nWidth); }
	int GetHeight(void) { return m_board.GetHeight(); }
	void SetHeight(int nHeight) { m_board.SetHeight(nHeight); }
	int GetColumns(void) { return m_board.GetColumns(); }
	void SetColumns(int nColumns) { m_board.SetColumns(nColumns); }
	int GetRows(void) { return m_board.GetRows(); }
	void SetRows(int nRows) { m_board.SetRows(nRows); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }
	bool IsGameOver() { return m_board.IsGameOver(); }
	int DeleteBlocks(int row, int col)
	{
		return m_board.DeleteBlocks(row, col);
	}
	int GetRemainingCount()
	{
		return m_board.GetRemainingCount();
	}
	int GetNumColors() { return m_board.GetNumColors(); }
	void SetNumColors(int nColors);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMyGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Экземпляр объекта нашей игровой доски 
	CMyGameBoard m_board;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
