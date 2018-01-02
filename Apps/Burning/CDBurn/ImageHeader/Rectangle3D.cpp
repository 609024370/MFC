// Rectangle3D.cpp : implemetation file
// ������Ƭ��

#include "stdafx.h"
#include "Rectangle3D.h"
#include "TransMatrix3D.h"


// ��ռ�����ֱ��������ƽ��Ľ���
CFPoint3D Intersect3D_Line_Plane()
{
	CFPoint3D ptIntersect;
	return ptIntersect;
}



// ��ռ�ֱ�߶���ռ������Ƭ֮��Ľ���
BOOL Intersect3D_LineSeg_Rectangle(const CFPoint3D& ptStart, const CFPoint3D& ptEnd,
								   const CRectangle& Rectangle,
								   CFPoint3D& ptInstersect)
{
	BOOL bIntersect = FALSE;

	// �ò���ʽ���ռ�ֱ��
	CFVector3D V = ptEnd - ptStart;
	// P(t) = ptStart + t * V -------------------------------(1)

	// �õ㷨ʽ��ʾ�ռ�ƽ��
	CFVector3D N = Rectangle.GetN();
	// N �� (P - Rectangle.m_ptCenter) = 0 ------------------(2)

	// ��(1)����(2),���t
	// N �� (t * V + D) = 0,  in which D is
	CFVector3D D = ptStart - Rectangle.GetCenter();
	// t* (N �� V) = -N �� D
	double fNV_DotMul = DotMul(N, V);
	if(! IsZero(fNV_DotMul))
	{
		double t = -DotMul(N, D) / fNV_DotMul;
		if(0.0 <= t && t <= 1.0)
		{
			bIntersect = TRUE;
			ptInstersect = ptStart + t * V;
		}
	}

	return bIntersect;
}

// ���̣�
//    c[0][0] * x  +  c[0][1] * y  =  c[0][2]
//    c[1][0] * x  +  c[1][1] * y  =  c[1][2]
// ����
//    a0 * x  +  b0 * y  =  c0
//    a1 * x  +  b1 * y  =  c1
//
// �ⷽ�̣�
//    a1 * a0 * x  +  a1 * b0 * y  =  a1 * c0       -----------(1)
//    a0 * a1 * x  +  a0 * b1 * y  =  a0 * c1       -----------(2)
// (1) - (2)����
//    (a1 * b0  -  a0 * b1) * y  =  a1 * c0  -  a0 * c1
//
// ���ڽ�������ǣ��б�����ʽ 
//    delta = a1 * b0  -  a0 * b1
// ��Ϊ�㡣
//    y = (a1 * c0  -  a0 * c1) / delta
//
// ͬ����
//    b1 * a0 * x  +  b1 * b0 * y  =  b1 * c0       -----------(1)
//    b0 * a1 * x  +  b0 * b1 * y  =  b0 * c1       -----------(2)
// (2) - (1)����
//    delta = a0 * b1  -  a1 * b0
//    x = (b0 * c1  -  b1 * c0) / delta
class CEquation2x2
{
public:
	CEquation2x2()
	{
		for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			c[i][j] = 0.0;
	}

public:
	void Set(const double a0_, const double b0_, const double c0_, 
			const double a1_, const double b1_, const double c1_)
	{
		a0 = a0_, b0 = b0_, c0 = c0_, a1 = a1_, b1 = b1_, c1 = c1_;
	}

	void Set(const double c_[2][3])
	{
		for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			c[i][j] = c_[i][j];
	}


public:
	BOOL GetRoot(double& x, double& y)
	{
		double delta = a1 * b0  -  a0 * b1;
		if(IsZero(delta))
			return FALSE;

		x = (b0 * c1  -  b1 * c0) / delta;
		y = (a1 * c0  -  a0 * c1) / delta;
		return TRUE;
	}

public:
	union
	{
		double c[2][3];
		struct
		{
			double a0, b0, c0, a1, b1, c1;
		};
	};

};

BOOL GetRoot(const double a0, const double b0, const double c0, 
			 const double a1, const double b1, const double c1, 
			 double& x, double& y)
{
	double delta = a1 * b0  -  a0 * b1;
	if(IsZero(delta))
		return FALSE;

	x = (b0 * c1  -  b1 * c0) / delta;
	y = (a1 * c0  -  a0 * c1) / delta;
	return TRUE;
}

#define IsBetween(_value, _minV, _maxV)		( (_minV <= _value) && (_value <= _maxV) )
#define IsBetween01(_value)					IsBetween(_value, 0.0, 1.0)

// �������߶�: <P0-P1> �� <Q0-Q1> һ������
BOOL LineSeg_LineSeg_Intersect(const CFPoint3D& P0, const CFPoint3D& P1,
							   const CFPoint3D& Q0, const CFPoint3D& Q1,
							   CFPoint3D& ptIntersect)
{
	CFPoint3D V0 = P1 - P0;
	CFPoint3D V1 = Q1 - Q0;

	// ���ж�������ֱ�߶��Ƿ�ƽ�У����ƽ�У��϶�û�н���
	if(V0.ForkMulWith(V1).IsZeroVector()) // ----------------------------- (0)
	{
		return FALSE;
	}

	// ������ʽ��ʾ������ֱ��(��)
	// P(s) = P0 + s * V0,  0 <= s <= 1  -------------------------- (1)
	// Q(t) = Q0 + t * V1,  0 <= t <= 1  -------------------------- (2)
	// �� P(s) = Q(t), ��
	// P0 + s * V0  =  Q0 + t * V1����
	// s * V0  - t * V1  =  Q0-P0����
	// s * V0  - t * V1  =  D0������ -------------------------------(3)
	CFPoint3D D0 = Q0 - P0;
	// ����һ����Ԫһ�����෽���飨��3�����̽�2��δ֪��s,t��
	//     V0.x * s - V1.x * t = D0.x
	//     V0.y * s - V1.y * t = D0.y
	//     V0.z * s - V1.z * t = D0.z  -----------------------------(4)
	//
	// ����ֻ��ȡ�����������ɣ���(x,y)������ <P0-P1> �� <Q0-Q1> ��x-y���ͶӰ��ƽ��/�غϵģ�
	// ��ʱ������ȡx-z����y-z���ɡ�


	// ѡ����ʵķ�������нⷽ�̣��õ�����s��/��t���Ӷ��������
	CEquation2x2  Equation;
	if(! IsEqual(V0.m_fx * V1.m_fy, V0.m_fy * V1.m_fx)) // �ж������߶���x-yͶӰ�Ƿ�ƽ��/�غ�
	{
		// ��ƽ��/�غϣ���(x,y)���������
		Equation.Set(V0.m_fx, -V1.m_fx, D0.m_fx,   V0.m_fy, -V1.m_fy, D0.m_fy);
	}
	else if(! IsEqual(V0.m_fx * V1.m_fz, V0.m_fz * V1.m_fx)) // ��ȡ(x,z)����������x-zƽ���ͶӰ�Ƿ�ƽ��/�غ�
	{
		Equation.Set(V0.m_fx, -V1.m_fx, D0.m_fx,   V0.m_fz, -V1.m_fz, D0.m_fz);
	}
	else if(! IsEqual(V0.m_fy * V1.m_fz, V0.m_fz * V1.m_fy)) // ��ʱ��������y-zƽ���ͶӰ�ض��ཻ��ȡ(y,z)
	{
		Equation.Set(V0.m_fy, -V1.m_fy, D0.m_fy,   V0.m_fz, -V1.m_fz, D0.m_fz);
	}
	else
	{
		// ��������£�����ֱ�߶αض�ƽ�У����Ѿ��� ---(0) �ų�
		ASSERT(0);
		return FALSE;
	}

	double s = 0.0, t = 0.0;
	Equation.GetRoot(s, t);

	if(IsBetween01(s) && IsBetween01(t))
	{
		CFPoint3D P = P0 + s * V0;
		CFPoint3D Q = Q0 + t * V1;

		#ifdef _RODGER_DBG
		ASSERT(P == Q);
		#endif

		ptIntersect = P;

		return TRUE;
	}

	return FALSE;
}

// ���߶� <P0-P1> �� <������Ƭrc1> �Ľ��߶Σ����� <P0-P1> �� rc1 ���档
// ���������߶Σ�����true�����Ҹý��߶η��� <ptStartNew, ptEndNew> �з��أ�
// ���򷵻�false
BOOL LineSeg_Rectangle_Intersect(const CFPoint3D& ptStart, const CFPoint3D& ptEnd,
								 const CRectangle& rc,
								 CFPoint3D& ptStartNew, CFPoint3D& ptEndNew)
{
	BOOL bStartIn = FALSE, bEndIn = FALSE;
	if(rc.PtInRectangle(ptStart))
	{
		bStartIn = TRUE;
		ptStartNew	= ptStart;
	}

	if(rc.PtInRectangle(ptEnd))
	{
		bEndIn = TRUE;
		ptEndNew	= ptEnd;
	}

	if(bStartIn && bEndIn)
		return TRUE;

	CFPoint3D p0, p1;

	int nCount = 0;
	CFPoint3D ptIntersect[4]; // 2 at most
	for(int nEdgeIndex = 0; (nEdgeIndex < 4) && (nCount < 3); nEdgeIndex++)
	{
		rc.GetEdgeByIndex(nEdgeIndex, p0, p1);
		if(LineSeg_LineSeg_Intersect(ptStart, ptEnd, p0, p1, ptIntersect[nCount]))
			nCount++;
	}

	// 1 or 2
	if(1 == nCount)
	{
		if(bStartIn)
			ptEndNew = ptIntersect[0];
		else
			ptStartNew = ptIntersect[0];
	}
	else if(2 == nCount)
	{
		// which is the start, which is the end?
		ptStartNew	= ptIntersect[0];
		ptEndNew	= ptIntersect[1];
	}
	else
	{
		// ASSERT(0);
		//
		return FALSE;
	}

	return TRUE;
}

BOOL Rectangle_Rectangle_Intersect(const CRectangle& rc0, const CRectangle& rc1,
								   CFPoint3D& ptStart, CFPoint3D& ptEnd)
{
	BOOL bIntersect = FALSE; // ������������Ƭ�Ƿ��н�

	// debug
//	rc0.Dump(0);
//	rc1.Dump(1);

	// �������������Ƭƽ�У���ɶ��������غ�����Ժ��ٿ��ǣ�
	if( ForkMul(rc0.GetN(), rc1.GetN()).IsZeroVector() )
	{
		return bIntersect;
	}


	CFPoint3D ptInstersects[4]; // 2 at most
	int nCount = 0;
	CFPoint3D ptInstersect;
	CLineSeg3D LineSeg;

//	CFPoint3D ptStart, ptEnd;

	BOOL bFirstEdge = TRUE;
	for(int nEdgeIndex = 0; nEdgeIndex < 4; nEdgeIndex++)
	{
		rc0.GetEdgeByIndex(nEdgeIndex, ptStart, ptEnd);
		if( Intersect3D_LineSeg_Rectangle(ptStart, ptEnd, rc1, ptInstersect) )
		{
			if(bFirstEdge)
			{
				ptInstersects[nCount++] = ptInstersect;
			}
			else
			{
				if(0 == nCount)
					ptInstersects[nCount++] = ptInstersect;
				else if(ptInstersects[nCount-1] != ptInstersect)
					ptInstersects[nCount++] = ptInstersect;
			}
		}

		bFirstEdge = FALSE;
	}

	// <������Ƭ0> �� <������Ƭ1����ƽ��> �Ľ���
	if(0 == nCount) // û�н�
	{
		// nop
	}
	else if(1 == nCount) // �ǵ�Ӵ�
	{
		// nop
	}
	else if(2 == nCount) // һ������
	{
		// check further
		bIntersect = LineSeg_Rectangle_Intersect(ptInstersects[0], ptInstersects[1], rc1, ptStart, ptEnd);
		if(bIntersect)
		{
			if(! rc0.PtInRectangle(ptStart))
				rc0.PtInRectangle(ptStart);
			if(! rc0.PtInRectangle(ptEnd))
				rc0.PtInRectangle(ptEnd);

			if(! rc1.PtInRectangle(ptStart))
				rc1.PtInRectangle(ptStart);
			if(! rc1.PtInRectangle(ptEnd))
				rc1.PtInRectangle(ptEnd);
		}
	}
	else
	{
		ASSERT(0); // impossible
	}

	ASSERT(nCount < 3);

	return bIntersect;
}
