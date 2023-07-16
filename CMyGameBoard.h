#pragma once
class CMyGameBoard
{
public: 
	// ����������� �� ��������� 
	CMyGameBoard(void);
	// ���������� 
	~CMyGameBoard(void);

	// ������� ��� ��������� ����������� ������ � ������ ���� 
	void SetupBoard(void);

	// �������� ���� � ������������ ������� �������� ���� 
	COLORREF GetBoardSpace(int row, int col);

	// ������� ��� ��������� ���������� � ���������� �������� ���� 
	int GetWidth(void) const { return m_nWidth; } 
	int GetHeight(void) const { return m_nHeight; } 
	int GetColumns(void) const { return m_nColumns; } 
	int GetRows(void) const { return m_nRows; }

	// ������� ��� �������� �������� ���� � ������������ ������ 
	void DeleteBoard(void);

private:

};

