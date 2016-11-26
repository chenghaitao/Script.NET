// DuiVisionDesignerView.h : interface of the CDuiVisionDesignerView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __DuiVisionDesignerVIEW_H__
#define __DuiVisionDesignerVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "timer.h"
#include "IDuiHostWnd.h"

// ���ڱ���ģʽ
enum
{
	BKTYPE_IMAGE_RESOURCE	= 0,	// ͼƬ��Դ
	BKTYPE_COLOR,					// ָ����ɫ
	BKTYPE_IMAGE_FILE,				// ͼƬ�ļ�
};

/////////////////////////////////////////////////////////////////////////////
// CDuiVisionDesignerView view
class CDuiVisionDesignerDoc;
class CDuiVisionDesignerView : public CView, public CTimer
{
protected: // create from serialization only
	CDuiVisionDesignerView();
	DECLARE_DYNCREATE(CDuiVisionDesignerView)

// Attributes
public:
	CDuiVisionDesignerDoc* GetDocument();

	ULONG			m_ulRefCount;			// ��Ƕ�ӿ���ʹ�õ����ü���,vcicommʹ��
	IDuiPluginPanel* m_pDuiPluginPanelObject; // DUI������Panel����

	UINT			m_uTimerAnimation;			// ������ʱ��
	UINT			m_uTimerAutoClose;			// ���ڴ����Զ��رյĶ�ʱ��ID

	CToolTipCtrl	m_wndToolTip;				// Tooltip
	int				m_nTooltipCtrlID;			// ��ǰTooltip��ʾ�Ŀؼ�ID

	BOOL			m_bChangeSize;				// �ı䴰�ڴ�С
	CSize			m_MinSize;					// �����޶���С��С

	COLORREF		m_clrBK;					// ������ɫ,�ɱ���ͼƬ�������ƽ��ɫ,������ͼƬ������ʱ���Դﵽ����ɫЧ��
	CBitmap			m_BKImage;					// ��ܱ���ͼƬ����
	CSize			m_sizeBKImage;				// ����ͼƬ��С
	//CString			m_strFramePicture;			// ����ͼƬ
	CDC				m_MemBKDC;					// ����dc(�ɱ���ͼƬ�򱳾���ɫ����)
	CBitmap			*m_pOldMemBK;
	CBitmap			m_MemBK;
	BOOL			m_bDrawImage;				// ͼƬ��ɫ����

	CString			m_strBkImg;					// ����ͼƬ
	COLORREF		m_crlBack;					// ������ɫ
	COLORREF		m_crlBackTransParent;		// ����͸����ɫ
	int				m_nBackTranslucent;			// ����͸����

	int				m_nOverRegioX;				// ���ȵĴ�С
	int				m_nOverRegioY;				// ���ȵĴ�С

// Operations
public:
	CString GetDuiVisionPluginPath();

	// ��ʱ����Ϣ
	virtual void OnTimer(UINT uTimerID);
	virtual void OnTimer(UINT uTimerID, CString strTimerName);

	// ��ʼ�����ڱ���Ƥ��(���ص������ڴ�dc)
	void InitWindowBkSkin();
	// ���ش��ڱ���ͼƬ
	void LoadBackgroundImage(CString strFileName);
	// ���ô��ڱ���͸����
	void SetupBackTranslucent();
	// ������ͼƬ
	void DrawBackground(CBitmap &bitBackground);
	// ��������ɫ
	void DrawBackground(COLORREF clr);
	// ��Area�ؼ��İ�͸����
	void DrawAreaControl(CDC &dc, CRect rcArea, COLORREF clr, int nBeginTransparent, int nEndTransparent);
	// ��������Area�ؼ����ڴ�dc
	void DrawBackgroundAndAreas(CDC &dc, const CRect &rcClient, const CRect &rcUpdate);

	// Tooltip����
	void SetTooltip(int nCtrlID, LPCTSTR lpszTooltip, CRect rect, int nTipWidth);
	void ClearTooltip();
	void  SetTooltipCtrlID(int nTooltipCtrlID) { m_nTooltipCtrlID = nTooltipCtrlID; }
	int  GetTooltipCtrlID() { return m_nTooltipCtrlID; }

protected:
	// �����Ĳ���������ڹ��ܽӿ�
    BEGIN_INTERFACE_PART(DuiVisionDesignerView, IDuiHostWnd)
		// ƽ̨����
		STDMETHOD_( CString , GetAppName) ();				// ��ȡӦ�ó�����
		STDMETHOD_( CString , GetPlatPath) ();				// ��ȡƽ̨·��
		STDMETHOD_( CString , GetPlatVersion) ();			// ��ȡƽ̨�汾
		STDMETHOD_( int , GetCurrentLanguage) ();			// ��ȡ��ǰ����
		STDMETHOD_( CString , GetPlatRegistry) ();			// ��ȡƽ̨ע����·��
		STDMETHOD_( CString , GetPlatCopyRight) ();			// ��ȡƽ̨��Ȩ�ַ���
		STDMETHOD_( CString , GetPlatHomeURL) ();			// ��ȡ��ҳURL
		STDMETHOD_( CString , GetPlatDownloadURL) ();		// ��ȡ����URL
		STDMETHOD_( int  , SendMessage) (CVciMessage* pIn, CVciMessage* ppOut);	// ������Ϣ
		STDMETHOD_( int  , ProcessMessage) (CVciMessage* pIn, CVciMessage* ppOut);	// ƽ̨����Ϣ����
		STDMETHOD_( int  , SendCommand) (int nCmd, WPARAM wParam, LPARAM lParam);	// ����ƽ̨����
		STDMETHOD_( BOOL , SendCommand) (int nCmd, WPARAM wParam, LPARAM lParam, LPVOID lpResult);	// ����ƽ̨����

		// DuiVisionϵͳ����
		STDMETHOD_( int  , GetAppID) ();	// ��ȡDuiVisionӦ��ID

		// ���ڲ���
		STDMETHOD_( BOOL , GetWindowBkInfo) (int& nType, int& nIDResource, COLORREF& clr, CString& strImgFile);	// ��ȡ���ڱ�����Ϣ
		STDMETHOD_( BOOL , SetWindowBkInfo) (int nType, int nIDResource, COLORREF clr, LPCTSTR lpszImgFile);	// ���ô��ڱ�����Ϣ
		STDMETHOD_( void  , ClientToScreen) (LPPOINT lpPoint);	// ����ת��Ϊ��Ļ����
		STDMETHOD_( HWND  , GetPaintHWnd) ();	// ��ȡ�������ڵľ��

		// Tooltip����
		STDMETHOD_( void  , SetTooltip) (int nCtrlID, LPCTSTR lpszTooltip, CRect rect, int nTipWidth);	// ����Tooltip
		STDMETHOD_( void , ClearTooltip) ();			// ���Tooltip
		STDMETHOD_( void , SetTooltipCtrlID) (int nTooltipCtrlID);	// ���õ�ǰTooltip�ؼ�ID
		STDMETHOD_( int , GetTooltipCtrlID) ();		// ��ȡ��ǰTooltip�ؼ�ID
	END_INTERFACE_PART(DuiVisionDesignerView)
	EXPORT_INTERFACE_PART(DuiVisionDesignerView)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDuiVisionDesignerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
 //CFormView
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
 //!CRichEditView||CHtmlView
 //CFormView
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDuiVisionDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDuiVisionDesignerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
<<<<<<< HEAD
	virtual BOOL PreTranslateMessage(MSG* pMsg);
=======
	afx_msg void OnViewToolbox();
	afx_msg void OnDuiControlCmd(UINT nID);
	afx_msg void OnUpdateDuiControlCmd(CCmdUI* pCmdUI);
>>>>>>> 0229a0fe52a55c797e37b00865bf980195b8146a
};

#ifndef _DEBUG  // debug version in DuiVisionDesignerView.cpp
inline CDuiVisionDesignerDoc* CDuiVisionDesignerView::GetDocument()
   { return (CDuiVisionDesignerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(__DuiVisionDesignerVIEW_H__)
