
// CADViewerView.cpp : implementation of the CCADViewerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CADViewer.h"
#endif

#include "CADViewerDoc.h"
#include "CADViewerView.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#endif


// CCADViewerView

IMPLEMENT_DYNCREATE(CCADViewerView, CView)

BEGIN_MESSAGE_MAP(CCADViewerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCADViewerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CCADViewerView construction/destruction

CCADViewerView::CCADViewerView()
{
	// TODO: add construction code here

}

CCADViewerView::~CCADViewerView()
{
}

BOOL CCADViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCADViewerView drawing

void CCADViewerView::OnDraw(CDC* /*pDC*/)
{
	CCADViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	myView->MustBeResized();
	myView->Update();
	pDoc->DrawSphere(10.0);
	myView->FitAll();   // To Focus the view to the drawn Object;

}


// CCADViewerView printing


void CCADViewerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCADViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCADViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCADViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCADViewerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCADViewerView::OnInitialUpdate(){

 myView=GetDocument()->GetViewer()->CreateView();
 myView->SetShadingModel(V3d_GOURAUD);
 Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((CCADViewerApp*)AfxGetApp())->GetGraphicDriver();
 Aspect_Handle aWindowHandle = (Aspect_Handle)GetSafeHwnd();
 Handle(WNT_Window) aWntWindow=new WNT_Window(GetSafeHwnd());
 myView->SetWindow(aWntWindow);
 
 if(!aWntWindow->IsMapped()){
  aWntWindow->Map();
 }

 Standard_Integer w=100;
 Standard_Integer h=100;
 aWntWindow->Size(w,h);
 ::PostMessage(GetSafeHwnd(),WM_SIZE,SIZE_RESTORED,w+h*65536);
 myView->FitAll();
 myView->ZBufferTriedronSetup(Quantity_NOC_RED,Quantity_NOC_GREEN,Quantity_NOC_BLUE1,0.8,0.05,12);
    myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER,Quantity_NOC_WHITE,0.2,V3d_ZBUFFER);


	


}

void CCADViewerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCADViewerView diagnostics

#ifdef _DEBUG
void CCADViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CCADViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCADViewerDoc* CCADViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCADViewerDoc)));
	return (CCADViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CCADViewerView message handlers





void CCADViewerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
	if(nFlags && MK_LBUTTON){
		
			
			myView->Rotation(point.x,point.y);	
			myView->StartRotation(point.x,point.y);
	}

}
