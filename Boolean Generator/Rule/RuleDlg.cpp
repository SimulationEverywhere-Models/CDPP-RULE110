///////////////////////////////////////////////
//	RuleDlg.cpp : implementation file
//	Function : Implemetation class of the 
//			   controlling parent dialog
//	Author : Colin Timmons
//	Date : 9 Nov 11
///////////////////////////////////////////////

#include "stdafx.h"
#include "Rule.h"
#include "RuleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRuleDlg dialog



///////////////////////////////////////////////
//	Method: CRuleDlg
//	Attributes: Std CWnd CDialog inheritance
//	Function: Constructor
///////////////////////////////////////////////
CRuleDlg::CRuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRuleDlg::IDD, pParent)
	,nRule(0)
	,nRow(0)
	,nColumn(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_Neighbour, 0x00, sizeof(m_Neighbour) );
	
}
///////////////////////////////////////////////
//	Method: DataExchange
//	Attributes: CDataExchange - messages input by user
//	Function: For transferring and validating data
//		      in a dialog box
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Rule);
	DDX_Control(pDX, IDC_EDIT2, m_Row);
	DDX_Control(pDX, IDC_EDIT3, m_Column);
	DDX_Control(pDX, IDC_EDIT4, m_RowValue);
	DDX_Control(pDX, IDC_BUTTON6, m_Pattern);
	DDX_Control(pDX, IDC_BUTTON1, m_Generate);
	DDX_Control(pDX, IDC_CHECK1, m_Logging);
}
///////////////////////////////////////////////
//	Macro: BEGIN_MESSAGE_MAP
//	Function: Traps mesages and directs them to
//			  the approriate method
///////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CRuleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRuleDlg::OnBnClickedButton1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CRuleDlg::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CRuleDlg::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CRuleDlg::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRuleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRuleDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRuleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CRuleDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CRuleDlg::OnBnClickedButton6)
END_MESSAGE_MAP()
///////////////////////////////////////////////
//	Method: OnInitDialog
//	Function: Initalization of the dialog after
//			  the constructor is called
//	Return: BOOL - true if successful 
///////////////////////////////////////////////
BOOL CRuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	HICON hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
	SetIcon( hIcon, true );
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//Load the title
	this->SetWindowTextA("Rule Generator - Colin Timmons");
	DrawRuleDialog();
			
	m_RowValue.EnableWindow(FALSE);
	this->SetWindowPos(NULL,650,200,600,250,SWP_SHOWWINDOW);
	m_Rule.SetFocus();
	//this->MoveWindow( 650, 200, 600, 250, 1 );
	return TRUE;  // return TRUE  unless you set the focus to a control
}
///////////////////////////////////////////////
//	Method: OnBnClickedButton1
//	Function: Event handler for the Generate 
//			  command button which passes the
//			  calculated information for plotting
//			  on the cellular autimata dialog
//	Return: void 
///////////////////////////////////////////////
void CRuleDlg::OnBnClickedButton1()
{
	HWND hwnd = ::FindWindowA(NULL, "Cellular Automata");
	if( hwnd == NULL )
	{
		vecRow.clear();		
		DrawRuleDialog();
	}
	
	CString szString;
	
	m_RowValue.GetWindowTextA(szString);
	if( szString.IsEmpty() )
	{
		//default is 1;
		m_RowValue.SetWindowTextA("1");
		m_RowValue.EnableWindow(true);
		nRow = 1;
		m_Row.SetWindowTextA("1");
		nColumn = 1;
		m_Column.SetWindowTextA("1");
		szString = "1";
	}
				
	if( !CreateVector( szString ) )
			return;
	if( nRow > 600 || nColumn > 600 )
		dlgDiagram->ResizeDialog( nRow, nColumn);
	if( !dlgDiagram->SetCellularAutomata(vecRow, nRow, nColumn, 0, m_Logging.GetCheck() ) )
	{
			dlgDiagram->OnCancel();
			return;
	}

	int x = 0;
	int row = 0;
	bool bCheck = false;

	for(int k = 1; k < nRow ; ++k)
	{

		for( int nCounter = 1; nCounter < nColumn - 1; ++nCounter )
		{
		
			//So check the binary rule against the vector's previous row
			//Returns the three cells binary value depending on the given rule
			bCheck = DetermineRule( nCounter );

			std::vector<char>::iterator it;
			it = vecNextRow.begin();
			//the iterator i gives us the position in the row
			std::advance( it, nCounter);

			if(bCheck)
			{
				//Result. Populate the vector data counter with a 1
				*it = 1;
			}
			else
				*it = 0;

		}
		
		//clear and swap the vector information for the next row
		vecRow = vecNextRow;
		vecNextRow.clear();
		vecNextRow.resize( nColumn );
		if(	!dlgDiagram->SetCellularAutomata(vecRow, nRow, nColumn, k, m_Logging.GetCheck() ) )
		{
			dlgDiagram->OnCancel();
			return;
		}
	}
}
///////////////////////////////////////////////
//	Method: StringToInt
//	Attributes: CString - string that wishes to
//						  converted
//	Function: Converts a string to and integer
//			  representation 
//			  i.e. "255" becomes 255
//	Return: int - value of the string passed in 
///////////////////////////////////////////////
int CRuleDlg::StringToInt(CString& szRuleString)
{
	if(szRuleString.IsEmpty())
		return -1;
	int i = _ttoi(szRuleString);
	return i;
}
///////////////////////////////////////////////
//	Method: DrawRuleDialog
//	Function: Instantiates the Cellular Automata
//			  as a modeless dialog box
//	Return: bool - true if successful 
///////////////////////////////////////////////
bool CRuleDlg::DrawRuleDialog(void)
{
	dlgDiagram = new Diagram();
	dlgDiagram->Create(IDD_DIAGRAM, this);
	
	return true;
}
///////////////////////////////////////////////
//	Method: CreateVector
//	Attributes: CString - original top row
//						  string from dialog
//	Function: Inserts the top row string into
//			  vector as char and then resizes
//			  to the amount of columns entered
//	Return: bool - true if successful 
///////////////////////////////////////////////
bool CRuleDlg::CreateVector(CString& szString)
{
	if (nRow <= 0 || nColumn <= 0) 
    {
      return false;
    }
	if( !PushBackVector( szString ) )
		return false;
	vecRow.resize( nColumn);
	vecNextRow.resize( nColumn );

	return true;
}
///////////////////////////////////////////////
//	Method: DetermineRule
//	Attributes: int - position of the cell in the vector
//	Function: Using the rule entered on the dialog
//			  the method compares the loading of the
//			  previous row cells with the present cell
//			  in question and returns true for
//			  population of the vector if the
//			  conditions are correct
//	Return: bool - true if successful 
///////////////////////////////////////////////
bool CRuleDlg::DetermineRule( int nValue )
{
	int nBinary = 0;
	int mask = 1;
	char nTempChar[3] = {0,0,0};
	char nTempNeighbour[3] = {0,0,0};
	
	//The value of each column for the row was passed through from the vector
	//Assign stack memory to the heap memory value for speed
	nTempNeighbour[2] = vecRow.at( nValue - 1);
	nTempNeighbour[1] = vecRow.at( nValue);
	nTempNeighbour[0] = vecRow.at( nValue + 1);

	//Range checked at the endfocus method but safety first
	if( nRule <= 0)
		return false;

	//check the value of each bit
	for( int i = 0; i < 8; i++)
	{
		//determine if a one is present in the rule
		nBinary = nRule & mask;

		if( nBinary )
		{
			//depending on the position the neighbour will have a specific value
			m_Neighbour[2] = ( i >= 4) ? 1 : 0;
			m_Neighbour[1] = ( i & 0x2 ) ? 1 : 0;
			m_Neighbour[0] = (i & 0x1 ) ? 1 : 0;
			
			//Now compare to actual data through memcmp to see if the value matches the theory
			char nCompare = memcmp( nTempNeighbour, m_Neighbour, sizeof( nTempNeighbour ) );

			//memcmp returns 0 if true so return success
			if( 0 == nCompare )
				return true;
		}
		//Set the mask higher to get the next bit
		mask <<= 1;
	}
	//no valid comparison so return false
	return false;
}
///////////////////////////////////////////////
//	Method: OnEnKillfocusEdit2
//	Function: Event handler to handler user input
//			  in the Row edit box
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnEnKillfocusEdit2()
{
	CString szString;
	m_Row.GetWindowTextA(szString);
	nRow = StringToInt(szString);
	if( nRow < 1 )
	{
		nRow = 1;
		m_Row.SetWindowTextA("1");
	}
		
}
///////////////////////////////////////////////
//	Method: OnEnKillfocusEdit3
//	Function: Event handler to handler user input
//			  in the Column edit box
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnEnKillfocusEdit3()
{
	m_RowValue.EnableWindow(TRUE);
	CString szString;
	m_Column.GetWindowTextA(szString);
	nColumn = StringToInt(szString);
	if( nColumn < 1 )
	{
		 nColumn = 1;
		 m_Column.SetWindowTextA("1");
	}

	if(nColumn > 0)
		m_RowValue.SetLimitText(nColumn);
	else
		return;
}
///////////////////////////////////////////////
//	Method: OnEnKillfocusEdit1
//	Function: Event handler to handler user input
//			  in the Rule edit box
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnEnKillfocusEdit1()
{
	CString szString;	
	m_Rule.GetWindowTextA(szString);
	nRule = StringToInt(szString);
	if(nRule < 0)
	{
		nRule = 0;
		m_Rule.SetWindowTextA("0");
	}
	if(nRule > 255)
	{
		nRule = 255;
		m_Rule.SetWindowTextA("255");
	}
}
///////////////////////////////////////////////
//	Method: PushBackVector
//	Attributes: CString - original top row
//						  string from dialog
//	Function: Inserts the top row string into
//			  vector
//	Return: bool - true if successful 
///////////////////////////////////////////////
bool CRuleDlg::PushBackVector(CString& szString)
{
	if( szString.IsEmpty() )
		return false;

	CString szTemp;
	int x = 0;
	
	for(int i = 0; i < szString.GetLength(); ++i )
	{
		szTemp = szString.GetAt( i );
		x = StringToInt( szTemp );
		vecRow.push_back( x );
	}
	return true;
}
///////////////////////////////////////////////
//	Method: OnBnClickedButton2
//	Function: Event handler to handler user input
//			  in the populate cmd button. Defaulted
//			  to columns - 1 of random 1 and 0 values
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnBnClickedButton2()
{
	if(nRow > 0)
		m_RowValue.EnableWindow(TRUE);
	CString str;
	float fRandNum;
	for(int i = 0; i < nColumn-1; i++)
	{
		fRandNum = rand()/(float)RAND_MAX;
		if( 0.5 < fRandNum)
			str += '1';
		else 
			str += '0';
	}
	m_RowValue.SetWindowTextA( str );
}
///////////////////////////////////////////////
//	Method: OnBnClickedButton2
//	Function: Event handler to handler user input
//			  for the change colour cmd button so
//			  the Cellular Automata dialog can have
//			  any colour drawn
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnBnClickedButton3()
{
	CColorDialog dlg; 
	if (dlg.DoModal() == IDOK) 
	{ 
		m_Colour = dlg.GetColor();
	}
	dlgDiagram->SetColour(m_Colour);
	
}
///////////////////////////////////////////////
//	Method: OnBnClickedButton2
//	Function: Event handler to handler user input
//			  in the clear dialog cmd button. Also erases
//			  all data held within the vectors
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnBnClickedButton4()
{
	HWND hwnd = ::FindWindowA(NULL, "Cellular Automata");
	if(hwnd != NULL)
		dlgDiagram->ClearDialog();
	vecRow.clear();
	vecNextRow.clear();
}
///////////////////////////////////////////////
//	Method: OnBnClickedButton5
//	Function: Event handler to handler user input
//			  in the populate cmd button. Defaulted
//			  to columns - 1 of zeros and ending in
//			  a one.
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnBnClickedButton5()
{
	if(nRow > 0)
		m_RowValue.EnableWindow(TRUE);
	CString str;
	for(int i = 0; i < nColumn-1; i++)
	{
		str += '0';
		
	}
	str += '1';
	m_RowValue.SetWindowTextA( str );
}
///////////////////////////////////////////////
//	Method: OnBnClickedButton6
//	Function: Cyclic random pattern of all the
//			  rules
//	Return: void
///////////////////////////////////////////////
void CRuleDlg::OnBnClickedButton6()
{
	try
	{	
		//Disable the button until completed
		m_Pattern.EnableWindow(FALSE);
		m_Generate.EnableWindow(FALSE);
		//Pass the object pointer to get the right interface for the thread
		m_pThread = AfxBeginThread( ThreadFunction, this);

		//If the returned pointer to the thread is not valid ie NULL
		ASSERT_VALID( m_pThread );
		if( !m_pThread )
		{
			// Could not attach thread
			AfxThrowResourceException();
		}
	}
	catch ( CResourceException* pEx )
	{
       	AfxMessageBox( _T( "Couldn't create and attach random genration thread!" ) );
		pEx->Delete();
	}
	
}
///////////////////////////////////////////////////////////
//Method:				ThreadFunction
//Input Parameters:		LPVOID pvParam	: 
//Output Parameters:	UINT			:
//Functionality:		Processes the cyclic genration.  The thread
//                      will start and finsh its existance in this procedure.
///////////////////////////////////////////////////////////
UINT CRuleDlg::ThreadFunction( LPVOID pvParam )
{
	//Create a friend pointer to access the calling object's data
	CRuleDlg *myRuleDlg = ( CRuleDlg* )pvParam;

	char str[10];
	CString szTemp1;
	CString szTemp2;
	myRuleDlg->OnBnClickedButton2();
	for(int i = myRuleDlg->nRule; i < 256; ++i)
	{
		
		DWORD dwStartTickCount = GetTickCount();
		myRuleDlg->nRule++;
		
		myRuleDlg->OnBnClickedButton1();
		DWORD dwEndTickCount = GetTickCount();
		
		DWORD dwTimeElasped = dwEndTickCount-dwStartTickCount;
		if (dwTimeElasped<1000)
		{
			_itoa_s(myRuleDlg->nRule, str, 10);
			szTemp1 = CString(str);
			
			myRuleDlg->m_Rule.SetWindowTextA(szTemp1);
			myRuleDlg->UpdateWindow();
			myRuleDlg->m_Rule.GetWindowTextA(szTemp2);
			if( !szTemp1.CompareNoCase(szTemp2) )
				Sleep(1000-dwTimeElasped);
			
		}
		myRuleDlg->OnBnClickedButton4();
	}
	//Enable the buttons when completed
	myRuleDlg->m_Pattern.EnableWindow(TRUE);
	myRuleDlg->m_Generate.EnableWindow(TRUE);
	return myRuleDlg->nRule;
}
