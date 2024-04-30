#pragma once
#include "..\IppImage.h"

void IppInverse(IppByteImage& img);//�����Լ�
void IppBrightness(IppByteImage& img, int n);//��� ��ȯ �Լ�
void IppContrast(IppByteImage& img, int n); //��Ϻ� ���� �Լ�


void IppGammaCorrection(IppByteImage& img, float gamma); //���� ���� 
void IppHistogram(IppByteImage& img, float histo[256]);
void IppHistogramStretching(IppByteImage& img);
void IppHistogramEqualizaiton(IppByteImage& img);

bool IppAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppSub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppAve(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppDiff(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);
bool IppOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

