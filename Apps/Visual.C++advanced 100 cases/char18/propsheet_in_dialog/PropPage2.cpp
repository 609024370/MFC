// PropPage2.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Example.h"
#include "PropPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PropPage2 


PropPage2::PropPage2(CWnd* pParent /*=NULL*/)
	: CDialog(PropPage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(PropPage2)
		// HINWEIS: Der Klassen-Assistent f�gt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void PropPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropPage2)
		// HINWEIS: Der Klassen-Assistent f�gt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

// ESC-Button not allowed here
void PropPage2::OnCancel (void) {

	return ;
}
// ENTER-Button not allowed here
void PropPage2::OnOK (void) {

	return ;
}

BEGIN_MESSAGE_MAP(PropPage2, CDialog)
	//{{AFX_MSG_MAP(PropPage2)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten PropPage2 
