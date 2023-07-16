#pragma once
class CMyGameBoard
{
public: 
	// Конструктор по умолчанию 
	CMyGameBoard(void);
	// Деструктор 
	~CMyGameBoard(void);

	// Функция для рандомной расстановки блоков в начале игры 
	void SetupBoard(void);

	// Получаем цвет в определенном участке игрового поля 
	COLORREF GetBoardSpace(int row, int col);

	// Геттеры для получения информации о параметрах игрового поля 
	int GetWidth(void) const { return m_nWidth; } 
	int GetHeight(void) const { return m_nHeight; } 
	int GetColumns(void) const { return m_nColumns; } 
	int GetRows(void) const { return m_nRows; }

	// Функция для удаления игрового поля и освобождения памяти 
	void DeleteBoard(void);

private:

};

