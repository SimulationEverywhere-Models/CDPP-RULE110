///////////////////////////////////////////////
//	Diagram.cpp : implementation file
//	Function : Implemetation class of the 
//			   Cellular Automata dialog
//	Author : Colin Timmons
//	Date : 9 Nov 11
///////////////////////////////////////////////

#include "stdafx.h"
#include "Rule.h"
#include "Diagram.h"
#include "afxdialogex.h"
#include <iostream> 
#include <fstream> 



// Diagram dialog

IMPLEMENT_DYNAMIC(Diagram, CDialog)
///////////////////////////////////////////////
//	Method: Diagram
//	Function: Overridden constructor for modeless
//			  operation
///////////////////////////////////////////////
Diagram::Diagram()
{
	m_Width = 600;
	m_Height = 600;
	nCounter = 0;
}
///////////////////////////////////////////////
//	Method: ~Diagram
//	Function: Std destructor for modeless
//			  operation
///////////////////////////////////////////////
Diagram::~Diagram()
{
}
///////////////////////////////////////////////
//	Method: DataExchange
//	Attributes: CDataExchange - messages input by user
//	Function: For transferring and validating data
//		      in a dialog box
//	Return: void
///////////////////////////////////////////////
void Diagram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
///////////////////////////////////////////////
//	Macro: BEGIN_MESSAGE_MAP
//	Function: Traps mesages and directs them to
//			  the approriate method
///////////////////////////////////////////////
BEGIN_MESSAGE_MAP(Diagram, CDialog)
//	ON_WM_SIZE()
	ON_WM_PAINT()
//	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
// Diagram message handlers
///////////////////////////////////////////////
//	Method: SetCelluarAutomata
//	Attributes: std::vector<char> & - data of the row
//				int - row, column and location number
//					  of the particular row being processed
//	Function: Sub-divides the dialog for display
//			  depending on the row and columns
//			  Sets blocks of pixels to represent the cells
//	Return: bool - true if successful
///////////////////////////////////////////////
bool Diagram::SetCellularAutomata(std::vector<char> & vec, int nRow, int nColumn, int drawRow, int bLogging )
{
	HDC hDC = ::GetDC(this->GetSafeHwnd());
	CRect myRect;
	GetWindowRect(&myRect);
	std::ofstream out;
	out.open("log.txt",std::ios::app);
	
	char chr[128];
		
	TRY
	{
		//Group the number of clumns into an amount of pixels
		int nWidthSize = myRect.Width() / nColumn;

		//Group the number of rows into an amount of pixels
		int nHeightSize = myRect.Height() / nRow;

		int r = 0;
		int s = nHeightSize * drawRow;
	
		std::vector<char>::iterator it = vec.begin();
		if( BST_CHECKED == bLogging)
			out << itoa(nCounter, chr, 10) << ' ';

		for(int i = 0; i < (int)vec.size(); ++i, ++it)
		{
		
			//Repaint if the contents of the vector is a 1
			if( *it == 1 )
			{
				for( int j = r; j < (nWidthSize+r); j++)
				{
					for( int k = s; k < (nHeightSize + s); k++)
					{
						SetPixelV(hDC, j, k, m_NewColour);
					
					}
				}
			}
			r += nWidthSize;
			if( BST_CHECKED == bLogging)
				out  << itoa(*it, chr, 10) ;
		}
	
		if( BST_CHECKED == bLogging )
				out <<"\n";
		if( nCounter == nColumn - 1)
			out << "\n";
		out.close();
		
		nCounter++;
		::ReleaseDC(this->GetSafeHwnd(), hDC);
		return true;
	}
	CATCH_ALL(e)
	{
		e->Delete();
		return false;
	}
	END_CATCH_ALL

}
///////////////////////////////////////////////
//	Method: OnInitDialog
//	Function: Initalization of the dialog after
//			  the constructor is called
//	Return: BOOL - true if successful 
///////////////////////////////////////////////
BOOL Diagram::OnInitDialog()
{	
	CDialog::OnInitDialog();

	//Load the title
	this->SetWindowTextA("Cellular Automata");
	HICON hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
	SetIcon( hIcon, true );
	SetWindowPos(NULL,10,10,m_Width,m_Height,SWP_SHOWWINDOW);

	 
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////
//	Method: SetColour
//	Attributes: COLORREF - value specifed from the
//						   parent dialog for colour
//						   of the graphing of the cellular
//						   automatavector
//	Function: Set the colorref value to a private variable
//	Return: void
///////////////////////////////////////////////
void Diagram::SetColour(COLORREF cColour)
{
	m_NewColour = cColour;

}
///////////////////////////////////////////////
//	Method: ClearDialog
//	Function: Clear the graph off the dialog and
//			  repaint the dialog with the default
//			  colour
//	Return: void
///////////////////////////////////////////////
void Diagram::ClearDialog()
{
	CDC *pDc = GetWindowDC();
	if(NULL != pDc)
	{
		CRect myRect;
		GetWindowRect(&myRect);
		
		pDc->FillSolidRect(&myRect, m_Colour );
		InvalidateRect(NULL, TRUE);
		UpdateWindow();
	}
	ReleaseDC( pDc ); 
	nCounter = 0;
	

}
///////////////////////////////////////////////
//	Method: OnPaint
//	Function: Overridden method to handle the
//			  repainting of the dialog to the
//			  default system colour
//	Return: void
///////////////////////////////////////////////
void Diagram::OnPaint()
{
	if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting
    }
    else
    {
        CPaintDC dc(this); // device context for painting

        CRect rc;
        GetWindowRect(&rc);
		m_Colour = dc.GetBkColor();
        dc.FillSolidRect(rc,m_Colour);
        
        CDialog::OnPaint();
    }
}
///////////////////////////////////////////////
//	Method: ResizeDialog
//	Function: Method to resize the dialog based
//			  on the number of rows and columns requested
//	Return: BOOL 
///////////////////////////////////////////////

//   columns requested
BOOL Diagram::ResizeDialog(int nWidth, int nHeight)
{

	if(nWidth < 600 || nHeight < 600)
		SetWindowPos(NULL,10,10,m_Width,m_Height,SWP_SHOWWINDOW);
	else
		SetWindowPos(NULL,10,10,nWidth,nHeight,SWP_SHOWWINDOW);
	

	InvalidateRect(NULL, TRUE);
	UpdateWindow();
	return TRUE;
	
}

