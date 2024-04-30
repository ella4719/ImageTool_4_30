
// ImageToolDoc.cpp: CImageToolDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "ImageToolDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "IppImage.h"
#include "IppConvert.h"
#include "IppImage/IppEnhance.h"
#include "CGammaCorrectionDlg.h"
#include "CHistogramDlg.h"
#include "CArithmeticLogicalDlg.h"
#include "IppFilter.h"

// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolDoc::OnImageInverse)
	ON_COMMAND(ID_BRIGHTNESS_CONTRAST, &CImageToolDoc::OnBrightnessContrast)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageToolDoc::OnGammaCorrection)
	ON_COMMAND(ID_VIEW_HISTOGRAM, &CImageToolDoc::OnViewHistogram)
	ON_COMMAND(ID_HISTO_STRETCHING, &CImageToolDoc::OnHistoStretching)
	ON_COMMAND(ID_HISTO_EQUALIZATION, &CImageToolDoc::OnHistoEqualization)
	ON_COMMAND(ID_ARITHMETIC_LOGICAL, &CImageToolDoc::OnArithmeticLogical)
	ON_COMMAND(ID_FILTER_MEAN, &CImageToolDoc::OnFilterMean)
	ON_COMMAND(ID_FILTER_WEIGHTED_MEAN, &CImageToolDoc::OnFilterWeightedMean)
	ON_COMMAND(ID_FILTER_MEAN2, &CImageToolDoc::OnFilterMean2)
	ON_COMMAND(ID_FILTER_WEIGHTED_MEAN2, &CImageToolDoc::OnFilterWeightedMean2)
END_MESSAGE_MAP()


// CImageToolDoc 생성/소멸

CImageToolDoc::CImageToolDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageToolDoc::~CImageToolDoc()
{
}

BOOL CImageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	BOOL ret = TRUE;

	m_Dib = *(theApp.m_pNewDib);
	theApp.m_pNewDib = NULL;

	return TRUE;
}




// CImageToolDoc serialization

void CImageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CImageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolDoc 진단

#ifdef _DEBUG
void CImageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolDoc 명령


BOOL CImageToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return m_Dib.Load(CT2A(lpszPathName));
}


BOOL CImageToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return m_Dib.Save(CT2A(lpszPathName));
}


void CImageToolDoc::OnImageInverse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage img;
	IppDibToImage(m_Dib, img);

	IppInverse(img);

	IppDib dib;
	IppImageToDib(img, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnBrightnessContrast()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage img;
	IppDibToImage(m_Dib, img);

	IppBrightness(img, 60);
	IppContrast(img, 40);

	IppDib dib;
	IppImageToDib(img, dib);

	AfxNewBitmap(dib);

}


void CImageToolDoc::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGammaCorrectionDlg dlg;
	if (dlg.DoModal() == IDOK) {

		IppByteImage img;
		IppDibToImage(m_Dib, img);

		IppGammaCorrection(img, dlg.m_fGamma);

		IppDib dib;
		IppImageToDib(img, dib);

		AfxNewBitmap(dib);

	}

}


void CImageToolDoc::OnViewHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CHistogramDlg dlg;
	dlg.SetImage(&m_Dib);
	dlg.DoModal();
}


void CImageToolDoc::OnHistoStretching()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage img;
	IppDibToImage(m_Dib, img);

	IppHistogramStretching(img);

	IppDib dib;
	IppImageToDib(img, dib);

	AfxNewBitmap(dib);

}


void CImageToolDoc::OnHistoEqualization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage img;
	IppDibToImage(m_Dib, img);

	IppHistogramEqualizaiton(img);

	IppDib dib;
	IppImageToDib(img, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnArithmeticLogical()
{

	CArithmeticLogicalDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
		CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;


		IppByteImage img1;
		IppDibToImage(pDoc1->m_Dib, img1);

		IppByteImage img2;
		IppDibToImage(pDoc2->m_Dib, img2);

		IppByteImage img3;

		bool ret = false;

		switch (dlg.m_nFunction)
		{
		case 0: ret = IppAdd(img1, img2, img3);  break;
		case 1: ret = IppSub(img1, img2, img3);  break;
		case 2: ret = IppAve(img1, img2, img3);  break;
		case 3: ret = IppDiff(img1, img2, img3); break;
		case 4: ret = IppAND(img1, img2, img3);  break;
		case 5: ret = IppOR(img1, img2, img3);   break;
		}
		if (ret)
		{
			IppDib dib;
			IppImageToDib(img3, dib);

			AfxNewBitmap(dib);
		}
		else
			AfxMessageBox(_T("영상의 크기가 다릅니다!"));
	}


}


void CImageToolDoc::OnFilterMean()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage imgSrc;
	IppByteImage imgDst;
	IppDibToImage(m_Dib, imgSrc);

	IppFilterMean(imgSrc, imgDst);

	IppDib dib;
	IppImageToDib(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFilterWeightedMean()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage imgSrc;
	IppByteImage imgDst;
	IppDibToImage(m_Dib, imgSrc);

	IppFilterWeightedMean(imgSrc, imgDst);

	IppDib dib;
	IppImageToDib(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFilterMean2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage imgSrc;
	IppByteImage imgDst;
	IppDibToImage(m_Dib, imgSrc);

	IppFilterMean2(imgSrc, imgDst);

	IppDib dib;
	IppImageToDib(imgDst, dib);

	AfxNewBitmap(dib);
}


void CImageToolDoc::OnFilterWeightedMean2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	IppByteImage imgSrc;
	IppByteImage imgDst;
	IppDibToImage(m_Dib, imgSrc);

	IppFilterWeightedMean2(imgSrc, imgDst);

	IppDib dib;
	IppImageToDib(imgDst, dib);

	AfxNewBitmap(dib);
}
