// Gradient.h: interface for the CGradient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRADIENT_H__B8518180_B289_11D4_A890_C3D6794EED5F__INCLUDED_)
#define AFX_GRADIENT_H__B8518180_B289_11D4_A890_C3D6794EED5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CPeg : CObject
{
public:
	CPeg() {id = uniqueID, uniqueID++, colour = 0x00000000, position = 0.0f;};
	CPeg(const CPeg &src) {colour = src.colour, position = src.position, id = src.id;};
	CPeg& operator = (const CPeg &src) {colour = src.colour, position = src.position, id = src.id; return *this;};
	void Serialize(CArchive &ar);
	const UINT GetID() const {return id;};

	DECLARE_SERIAL(CPeg)

	COLORREF colour;
	float position;
protected:
	UINT id;
	static UINT uniqueID;
};

#define BACKGROUND -4
#define STARTPEG -3
#define ENDPEG -2
#define NONE -1

typedef COLORREF (__cdecl* InterpolateFn)(COLORREF first, COLORREF second, float position, float start, float end);

class CGradient : public CObject  
{
public:
	CGradient();
	CGradient(CGradient &gradient);
	virtual ~CGradient();

	CGradient& operator =(CGradient &src);
	
	DECLARE_SERIAL(CGradient)

//----- Attributes -----//
	int GetPegCount() const;
	const CPeg GetPeg(int iIndex) const;
	int SetPeg(int iIndex, COLORREF crColour, float fPosition);
	int SetPeg(int iIndex, CPeg peg);
	int AddPeg(COLORREF crColour, float fPosition);
	int AddPeg(CPeg peg);
	void RemovePeg(int iIndex);
	int IndexFromPos(float pos);

	void SetStartPegColour(const COLORREF crColour){m_StartPeg.colour = crColour;};
	COLORREF GetStartPegColour() const {return m_StartPeg.colour;};
	void SetEndPegColour(const COLORREF crColour) {m_EndPeg.colour = crColour;};
	COLORREF GetEndPegColour() const {return m_EndPeg.colour;};
	void SetBackgroundColour(const COLORREF crColour) {m_Background.colour = crColour;};
	COLORREF GetBackgroundColour() const {return m_Background.colour;};
	void SetUseBackground(const BOOL bUseBackground) {m_UseBackground = bUseBackground;};
	BOOL GetUseBackground() const {return m_UseBackground;};

	enum InterpolationMethod
	{
		Linear,
		FlatStart,
		FlatMid,
		FlatEnd,
		Cosine,
		HSLRedBlue,
		HSLBlueRed,
		HSLShortest,
		HSLLongest,
		Reverse
	};

	InterpolationMethod GetInterpolationMethod() const;
	void SetInterpolationMethod(const InterpolationMethod method);
	int GetQuantization() const;
	void SetQuantization(const int entries);

//----- Operations -----//
	void MakePalette(CPalette *lpPalette);
	void Make8BitPalette(RGBTRIPLE *lpPal);
	void MakeEntries(RGBTRIPLE *lpPal, int iEntryCount);
	
	COLORREF ColourFromPosition(float pos);
	
	void Serialize(CArchive &ar);

//----- Internals -----//
protected:
	void SortPegs();
	
	//----- Interpolation routines -----//
	static COLORREF InterpolateLinear(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateFlatStart(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateFlatMid(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateFlatEnd(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateCosine(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateHSLClockwise(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateHSLAntiClockwise(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateHSLLongest(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateHSLShortest(COLORREF first, COLORREF second,
		float position, float start, float end);
	static COLORREF InterpolateReverse(COLORREF first, COLORREF second,
		float position, float start, float end);
private:	
	int IndexFromId(UINT id);
	void InsertSort(int lb, int ub);
	int Partition(int lb, int ub);
	void QuickSort(int lb, int ub);

protected:
	InterpolateFn GetInterpolationProc();
	POSITION GetNextPeg(POSITION current);
	CArray <CPeg, CPeg&> pegs;
	CPeg m_StartPeg, m_EndPeg, m_Background;
	BOOL m_UseBackground;
	int m_Quantization;
	InterpolationMethod m_InterpolationMethod;
};

#endif // !defined(AFX_GRADIENT_H__B8518180_B289_11D4_A890_C3D6794EED5F__INCLUDED_)
