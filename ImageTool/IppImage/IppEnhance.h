#pragma once
#include "..\IppImage.h"

void IppInverse(IppByteImage& img);//반전함수
void IppBrightness(IppByteImage& img, int n);//밝기 변환 함수
void IppContrast(IppByteImage& img, int n); //명암비 조절 함수


void IppGammaCorrection(IppByteImage& img, float gamma); //감마 보정 
void IppHistogram(IppByteImage& img, float histo[256]);
void IppHistogramStretching(IppByteImage& img);
void IppHistogramEqualizaiton(IppByteImage& img);

bool IppAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppSub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppAve(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppDiff(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

