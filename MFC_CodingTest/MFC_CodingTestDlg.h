
// MFC_CodingTestDlg.h: 헤더 파일
//

#pragma once

#include <vector>
// CMFCCodingTestDlg 대화 상자
class CMFCCodingTestDlg : public CDialogEx
{
private:
	CImage m_image;
	std::vector<CPoint> m_vPoint;
	BOOL m_bMovPoint;
	int m_nSeletedPoint;
	void Initcanvas();

// 생성입니다.
public:
	CMFCCodingTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CODINGTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_nRadius;
	int m_nThickness;
	void UpdateDisplay();
	void DrawPoint(unsigned char* fm, int x, int y, int nRadius, int nGray);
	void DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	BOOL ValidImgPos(int x, int y);
	BOOL vaildPointPos(int currentX, int currentY, int x, int y);
	LRESULT OnUpdateData(WPARAM wParam, LPARAM lParam);
	void RandomProcess();
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnRandom();
};
