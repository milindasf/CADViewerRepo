/*

Author: Milinda Fernando.
3/3/2014 
23:27

*/
// CADViewer.h : main header file for the CADViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCADViewerApp:
// See CADViewer.cpp for the implementation of this class
//

class CCADViewerApp : public CWinAppEx
{


private: 
	Handle(Graphic3d_GraphicDriver) m_GraphicDriver;					// To Keep the Initialized graphic driver...

public:
	CCADViewerApp();
	Handle(Graphic3d_GraphicDriver) GetGraphicDriver(){return m_GraphicDriver;}

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCADViewerApp theApp;
