
// CADViewerDoc.cpp : implementation of the CCADViewerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CADViewer.h"
#endif

#include "CADViewerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
//#define new DEBUG_NEW
#endif

// CCADViewerDoc

IMPLEMENT_DYNCREATE(CCADViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CCADViewerDoc, CDocument)
END_MESSAGE_MAP()


// CCADViewerDoc construction/destruction

CCADViewerDoc::CCADViewerDoc()
{
	// TODO: add one-time construction code here

	Handle(Graphic3d_GraphicDriver) theGraphicDriver=((CCADViewerApp*)AfxGetApp())->GetGraphicDriver();
	theGraphicDriver->Begin(new Aspect_DisplayConnection());
	TCollection_ExtendedString aNameOfViewer("Visu3d");
 
	//Initializing V3d_Viewer
	myViewer = new V3d_Viewer (theGraphicDriver, aNameOfViewer.ToExtString());
	myViewer->Init();
 
	
	myViewer->SetLightOn();
	myViewer->SetDefaultBackgroundColor(Quantity_NOC_BLACK);
 
	// create a new window or a wrapper over the existing window,
	myAISContext=new AIS_InteractiveContext(myViewer);
	myAISContext->SetDisplayMode(AIS_Shaded);
	myAISContext->SetAutomaticHilight(Standard_False);




}

CCADViewerDoc::~CCADViewerDoc()
{
}


void CCADViewerDoc::DrawSphere(double Radius){

	BRepPrimAPI_MakeSphere mkSphere(Radius);
	mkSphere.Build();
	TopoDS_Shape Sphere=mkSphere.Shape();

	myAISContext->Display(new AIS_Shape(Sphere));   // Draw the Sphere on the Screen
	


}

BOOL CCADViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCADViewerDoc serialization

void CCADViewerDoc::Serialize(CArchive& ar)
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
void CCADViewerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CCADViewerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCADViewerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCADViewerDoc diagnostics

#ifdef _DEBUG
void CCADViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCADViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCADViewerDoc commands
