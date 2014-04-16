
// CADViewerView.h : interface of the CCADViewerView class
//

#pragma once


class CCADViewerView : public CView
{
protected: // create from serialization only
	CCADViewerView();
	DECLARE_DYNCREATE(CCADViewerView)

// Attributes
public:
	CCADViewerDoc* GetDocument() const;
	Handle(V3d_View) myView;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate();

// Implementation
public:
	virtual ~CCADViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in CADViewerView.cpp
inline CCADViewerDoc* CCADViewerView::GetDocument() const
   { return reinterpret_cast<CCADViewerDoc*>(m_pDocument); }
#endif

