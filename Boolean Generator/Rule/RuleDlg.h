///////////////////////////////////////////////
//	RuleDlg.h : declaration file
//	Function : Declaration header file of the 
//			   controlling parent dialog
//	Author : Colin Timmons
//	Date : 9 Nov 11
///////////////////////////////////////////////


#pragma once
#include "afxwin.h"
#include "Diagram.h"


// CRuleDlg dialog
class CRuleDlg : public CDialogEx
{
// Construction
public:
	CRuleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RULE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	//Member variable to control the rule edit box
	CEdit m_Rule;

	//Member variable to control the row edit box
	CEdit m_Row;

	//Member variable to control the column edit box
	CEdit m_Column;

	//Member variable to control the first row data field edit box
	CEdit m_RowValue;

	//Member variable to store the full row data as a vector
	std::vector<char> vecRow;

	//Member variable to store the full next row data as a vector
	std::vector<char> vecNextRow;

	//Member variable to store the row data from the row field edit box
	int nRow;

	//Member variable to store the column data from the column field edit box
	int nColumn;

	//Member variable to store the rule data from the rule field edit box
	int nRule;

	//Member variable to store the default system colour of the dialog
	COLORREF m_Colour;

	//Member variable to store the value of the neighborhood ajoining the specified cell
	char m_Neighbour[3];

	//Member variable to control the cyclic pattern button
	CButton m_Pattern;

	//Member variable to control the generate button
	CButton m_Generate;

	//Member variable to activate the modeless dialog for display of the information
	Diagram *dlgDiagram;

	//Member variable for generating cyclic display without freezing the gui
	CWinThread *m_pThread;

	//Processing thread method
	static UINT ThreadFunction(LPVOID pvParam);   

	//Method to handle the event of the generate command button
	afx_msg void OnBnClickedButton1();	

	//Method to handle the event of the populate command button
	afx_msg void OnBnClickedButton2();

	//Method to handle the event of the set colour command button
	afx_msg void OnBnClickedButton3();

	//Method to handle the event of the clear command button
	afx_msg void OnBnClickedButton4();

	//Method to handle the instantiation of the Cellular Automata dialog
	bool DrawRuleDialog(void);

	//Method to convert a string into an integer value
	int StringToInt(CString& szRuleString);

	//Method to create and size the vector depending on the user input
	bool CreateVector( CString& szString );

	//Method to return the success of having neighbours that meet the rule conditions
	bool DetermineRule(int NValue);

	//Method to handle the event of the user leaving the rule edit box
	afx_msg void OnEnKillfocusEdit1();
	
	//Method to handle the event of the user leaving the row edit box
	afx_msg void OnEnKillfocusEdit2();

	//Method to handle the event of the user leaving the column edit box
	afx_msg void OnEnKillfocusEdit3();
	
	//Method to load the vector withe the initial data values as presented in the
	//first row value edit box
	bool PushBackVector(CString& szString);


public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
private:
	
public:
	
private:
	// Member variable to enable / disable logging of data into a text file
	CButton m_Logging;
};
