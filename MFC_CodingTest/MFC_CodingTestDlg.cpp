
// MFC_CodingTestDlg.cpp: 구현 파일
//


#include "pch.h"
#include "framework.h"
#include "MFC_CodingTest.h"
#include "MFC_CodingTestDlg.h"
#include "afxdialogex.h"
#include "corecrt_math_defines.h"


#ifdef _DEBUG

#define UM_UPDATE WM_USER

#define new DEBUG_NEW

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCodingTestDlg 대화 상자



void CMFCCodingTestDlg::Initcanvas()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;//Gray Level;
	
	m_bMovPoint = false;
	m_image.Create(nWidth, -nHeight, nBpp);
	
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();//첫번째 포인터 가져오기

	memset(fm, 0xff, nWidth * nHeight);
}

CMFCCodingTestDlg::CMFCCodingTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CODINGTEST_DIALOG, pParent)
	, m_nRadius(10)
	, m_nThickness(2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCodingTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_nRadius);
	DDX_Text(pDX, IDC_EDIT_THICKNESS, m_nThickness);
}

BEGIN_MESSAGE_MAP(CMFCCodingTestDlg, CDialogEx)
	ON_MESSAGE(UM_UPDATE, OnUpdateData)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_INIT, &CMFCCodingTestDlg::OnBnClickedBtnInit)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CMFCCodingTestDlg::OnBnClickedBtnRandom)
END_MESSAGE_MAP()


// CMFCCodingTestDlg 메시지 처리기

BOOL CMFCCodingTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	Initcanvas();
	UpdateDisplay();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCCodingTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCCodingTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		if (m_image)
		{
			CPaintDC dc(this);

			m_image.Draw(dc, 0, 0);
		}

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCCodingTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCodingTestDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
	
}

void CMFCCodingTestDlg::DrawPoint(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = m_image.GetPitch();
	CString strPos;
	CPoint point;
	CPoint dot;
	HDC dc = m_image.GetDC();

	for (double rad = 0; rad < M_PI * 2; rad = rad + (M_PI / 360))
	{
		for (int i = 0; i < nRadius; i++)
		{
			point.x = (int)round(nCenterX + i * cos(rad));
			point.y = (int)round(nCenterY + i * sin(rad));
			if (ValidImgPos(point.x, point.y))
			fm[point.y * nPitch + point.x] = nGray;
			
		}
	}
	strPos.Format(_T("x : %d, y : %d"), nCenterX, nCenterY);
	TextOutW(dc, nCenterX, nCenterY + 15, strPos, strPos.GetLength());
	m_image.ReleaseDC();
	
}

void CMFCCodingTestDlg::DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	PostMessage(UM_UPDATE);
	int nCenterX = x;
	int nCenterY = y;
	int nResolution;
	int nPitch = m_image.GetPitch();
	CPoint point;
	CPoint dot;
	int nThikness = m_nThickness;
	if (nRadius > m_image.GetHeight())
	{
		nResolution = nRadius / (m_image.GetHeight()) + 3;
	}
	else
	{
		nResolution = 1;
	}

	for (double Circle = 0; Circle < M_PI * 2; Circle = Circle + (M_PI / (360 * nResolution)))
	{
		point.x = (int)round(nCenterX + nRadius * cos(Circle));
		point.y = (int)round(nCenterY + nRadius * sin(Circle));
		if (ValidImgPos(point.x, point.y))
		{
			for (int i = 0; i < nThikness; i++)
			{
				CPoint dot;
				for (double radPoint = 0; radPoint < M_PI * 2; radPoint = radPoint + (M_PI / 360))
				{
					dot.x = (int)round(point.x + i * cos(radPoint));
					dot.y = (int)round(point.y + i * sin(radPoint));
					if (dot.x > 0 && dot.y > 0)
						if (ValidImgPos(dot.x, dot.y))
							fm[dot.y * nPitch + dot.x] = nGray;
				}
			}
		}
	}

}

BOOL CMFCCodingTestDlg::ValidImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);


	return rect.PtInRect(CPoint(x, y));
}

BOOL CMFCCodingTestDlg::vaildPointPos(int currentX, int currentY, int x, int y)
{
	UpdateData(true);

	BOOL nRet = false;
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = m_image.GetPitch();
	int nRadius = m_nRadius;
	CPoint point;
	CPoint dot;

	for (double rad = 0; rad < M_PI * 2; rad = rad + (M_PI / 360))
	{
		for (int i = 0; i < nRadius; i++)
		{
			point.x = (int)round(nCenterX + i * cos(rad));
			point.y = (int)round(nCenterY + i * sin(rad));
			if(currentX == point.x && currentY == point.y){
				nRet = true;
				return nRet;
			}
		}
	}

	return nRet;
}

LRESULT CMFCCodingTestDlg::OnUpdateData(WPARAM wParam, LPARAM lParam)
{
	UpdateData(true);
	return 0;
}

void CMFCCodingTestDlg::RandomProcess()
{
	PostMessage(UM_UPDATE);

	unsigned char* fm = (unsigned char*)m_image.GetBits();//첫번째 포인터 가져오기
	int nColor = 0;
	int nRadius = (int)m_nRadius;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	for (int i = 0; i < 3; i++) {
		m_vPoint[i].x = rand() % m_image.GetWidth();
		m_vPoint[i].y = rand() % m_image.GetHeight();
	}
	
	memset(fm, 0xff, nWidth * nHeight);
	
	for (int i = 0; i < 3; i++)
	{
		DrawPoint(fm, m_vPoint[i].x, m_vPoint[i].y, nRadius, nColor);
	}
	int d = 2 * (m_vPoint[0].x * (m_vPoint[1].y - m_vPoint[2].y) + m_vPoint[1].x * (m_vPoint[2].y - m_vPoint[0].y) + m_vPoint[2].x * (m_vPoint[0].y - m_vPoint[1].y));
	int x = ((m_vPoint[0].x * m_vPoint[0].x + m_vPoint[0].y * m_vPoint[0].y) * (m_vPoint[1].y - m_vPoint[2].y)
		+ (m_vPoint[1].x * m_vPoint[1].x + m_vPoint[1].y * m_vPoint[1].y) * (m_vPoint[2].y - m_vPoint[0].y)
		+ (m_vPoint[2].x * m_vPoint[2].x + m_vPoint[2].y * m_vPoint[2].y) * (m_vPoint[0].y - m_vPoint[1].y)) / d;
	int y = ((m_vPoint[0].x * m_vPoint[0].x + m_vPoint[0].y * m_vPoint[0].y) * (m_vPoint[2].x - m_vPoint[1].x)
		+ (m_vPoint[1].x * m_vPoint[1].x + m_vPoint[1].y * m_vPoint[1].y) * (m_vPoint[0].x - m_vPoint[2].x)
		+ (m_vPoint[2].x * m_vPoint[2].x + m_vPoint[2].y * m_vPoint[2].y) * (m_vPoint[1].x - m_vPoint[0].x)) / d;

	int r = (int)sqrt(pow(m_vPoint[0].x - x, 2) + pow(m_vPoint[0].y - y, 2));
	DrawCircle(fm, x, y, r, nColor);
	UpdateDisplay();
}


void CMFCCodingTestDlg::OnBnClickedBtnInit()
{
	int nWidth = 640;
	int nHeight = 480;
	
	unsigned char* fm = (unsigned char*)m_image.GetBits();//첫번째 포인터 가져오기

	memset(fm, 0xff, nWidth * nHeight);
	m_vPoint.clear();
	UpdateDisplay();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

#include <list>

void CMFCCodingTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	static std::list<CPoint> objList;
	
	UpdateData(true);
	int nColor = 0;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = m_nRadius;

	unsigned char* fm = (unsigned char*)m_image.GetBits();//첫번째 포인터 가져오기

	if (m_vPoint.size() < 3)
	{
		m_vPoint.push_back(point);
		DrawPoint(fm, point.x, point.y, nRadius, nColor);

		if (m_vPoint.size() == 3)
		{
			int d = 2 * (m_vPoint[0].x * (m_vPoint[1].y - m_vPoint[2].y) + m_vPoint[1].x * (m_vPoint[2].y - m_vPoint[0].y) + m_vPoint[2].x * (m_vPoint[0].y - m_vPoint[1].y));
			int x = ((m_vPoint[0].x * m_vPoint[0].x + m_vPoint[0].y * m_vPoint[0].y) * (m_vPoint[1].y - m_vPoint[2].y)
				+ (m_vPoint[1].x * m_vPoint[1].x + m_vPoint[1].y * m_vPoint[1].y) * (m_vPoint[2].y - m_vPoint[0].y)
				+ (m_vPoint[2].x * m_vPoint[2].x + m_vPoint[2].y * m_vPoint[2].y) * (m_vPoint[0].y - m_vPoint[1].y)) / d;
			int y = ((m_vPoint[0].x * m_vPoint[0].x + m_vPoint[0].y * m_vPoint[0].y) * (m_vPoint[2].x - m_vPoint[1].x)
				+ (m_vPoint[1].x * m_vPoint[1].x + m_vPoint[1].y * m_vPoint[1].y) * (m_vPoint[0].x - m_vPoint[2].x)
				+ (m_vPoint[2].x * m_vPoint[2].x + m_vPoint[2].y * m_vPoint[2].y) * (m_vPoint[1].x - m_vPoint[0].x)) / d;

			
			int r = (int)sqrt(pow(m_vPoint[0].x - x, 2) + pow(m_vPoint[0].y - y, 2));
			DrawCircle(fm, x, y, r, nColor);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_bMovPoint = vaildPointPos(point.x, point.y, m_vPoint[i].x, m_vPoint[i].y);

			if (m_bMovPoint)
			{
				m_vPoint[i].x = point.x;
				m_vPoint[i].y = point.y;
				m_nSeletedPoint = i;
				break;
			}
		}
	}

	UpdateDisplay();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCCodingTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	BOOL bRet = false;
	unsigned char* fm = (unsigned char*)m_image.GetBits();//첫번째 포인터 가져오기
	int nColor = 0;
	int nRadius = m_nRadius;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags == MK_LBUTTON && m_vPoint.size() >= 3)
	{
		if (m_bMovPoint)
		{
			if (ValidImgPos(point.x, point.y))
			{
				memset(fm, 0xff, nWidth * nHeight);
				m_vPoint[m_nSeletedPoint].x = point.x;
				m_vPoint[m_nSeletedPoint].y = point.y;
				for (int i = 0; i < 3; i++)
				{
					DrawPoint(fm, m_vPoint[i].x, m_vPoint[i].y, nRadius, nColor);
				}
				int d = 2 * (m_vPoint[0].x * (m_vPoint[1].y - m_vPoint[2].y) + m_vPoint[1].x * (m_vPoint[2].y - m_vPoint[0].y) + m_vPoint[2].x * (m_vPoint[0].y - m_vPoint[1].y));
				int x = ((m_vPoint[0].x * m_vPoint[0].x + m_vPoint[0].y * m_vPoint[0].y) * (m_vPoint[1].y - m_vPoint[2].y)
						+ (m_vPoint[1].x * m_vPoint[1].x + m_vPoint[1].y * m_vPoint[1].y) * (m_vPoint[2].y - m_vPoint[0].y)
						+ (m_vPoint[2].x * m_vPoint[2].x + m_vPoint[2].y * m_vPoint[2].y) * (m_vPoint[0].y - m_vPoint[1].y)) / d;
				int y = ((m_vPoint[0].x * m_vPoint[0].x + m_vPoint[0].y * m_vPoint[0].y) * (m_vPoint[2].x - m_vPoint[1].x)
					+ (m_vPoint[1].x * m_vPoint[1].x + m_vPoint[1].y * m_vPoint[1].y) * (m_vPoint[0].x - m_vPoint[2].x)
					+ (m_vPoint[2].x * m_vPoint[2].x + m_vPoint[2].y * m_vPoint[2].y) * (m_vPoint[1].x - m_vPoint[0].x)) / d;

				int r = (int)sqrt(pow(m_vPoint[0].x - x, 2) + pow(m_vPoint[0].y - y, 2));
				DrawCircle(fm, x, y, r, nColor);
				UpdateDisplay();
			}

		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

#include <thread>
using namespace std;

void threadProcess(CWnd* pParent) {
	
	CMFCCodingTestDlg* pWnd = (CMFCCodingTestDlg*)pParent;
	for (int i = 0; i < 10; i++)
	{
		pWnd->RandomProcess();
		pWnd->GetDlgItem(IDC_BTN_INIT)->EnableWindow(false);
		Sleep(500);
	}
	pWnd->GetDlgItem(IDC_BTN_INIT)->EnableWindow(true);
}

void CMFCCodingTestDlg::OnBnClickedBtnRandom()
{
	if (m_vPoint.size() > 2)
	{
		thread _thread0(threadProcess, this);
		_thread0.detach();
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
