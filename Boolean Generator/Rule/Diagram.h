///////////////////////////////////////////////
//	Diagram.h : declaration file
//	Function : Declaration header file of the 
//			   Cellular Automata dialog
//	Author : Colin Timmons
//	Date : 9 Nov 11
///////////////////////////////////////////////
#pragma once


// Diagram dialog

class Diagram : public CDialog
{
	DECLARE_DYNAMIC(Diagram)

public:
	 Diagram();
     BOOL Create(UINT nID, CWnd * pWnd) 
	 {
		CDialog::Create(nID,pWnd);
		return TRUE;
	 }
	//(CWnd* pParent = NULL);   // standard constructor
	 void OnCancel(){ DestroyWindow(); }
//	 virtual void PostNcDestroy() {delete this;}
	virtual ~Diagram();

// Dialog Data
	enum { IDD = IDD_DIAGRAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	//Member variable to store the width of the dialog
	int m_Width;

	//Member variable to store the height of the dialog
	int m_Height;

	int nCounter;

	//Member variable to store the system colour of the dialog
	COLORREF m_Colour;

	//Member variable to store the new colour of the graphing for the dialog
	COLORREF m_NewColour;

	//Method to initialize the dialog
	virtual BOOL OnInitDialog();

	//Method to position the dialog upon instatntiation
//	afx_msg void OnSize(UINT nType, int cx, int cy);

	//Overridden method to handle the repainting of the dialgo to system colours
	afx_msg void OnPaint();

public:
	//Method to set the pixels of the dialog based on the incoming row of data from the vector
	bool SetCellularAutomata(std::vector<char> & vec, int nRow, int nColumn, int drawRow, int bLogging);

	//Method to set the colour
	void SetColour(COLORREF nColour);

	//Method to clear the dialog back to the original blank appearance
	void ClearDialog();
	
	// Method to resize the dialog based on the number of rows and columns requested
	BOOL ResizeDialog(int nWidth, int nHeight);
//	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
