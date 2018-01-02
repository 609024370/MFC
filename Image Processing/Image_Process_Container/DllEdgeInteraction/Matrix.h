//////////////////////////////////////////////////////////////////////
//        ����     :   CMatrix ������                               //
//        ����     :   The Shadow Of The Bleak Moon                 //
//        �������� :   yy006yy@emails.bjut.edu.cn                   //
//        �������� :   2006 - 6 - 13                                //
//        ˵��     :   ʵ�ֶ�ά������                               //
//////////////////////////////////////////////////////////////////////  
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cassert>

using std::vector;

//##ModelId=499E6681025E
template<typename T>
class CMatrix
{
public:
	//##ModelId=499E6681026F
	explicit CMatrix(unsigned int nRows, unsigned int nCols, const T &data = T());
	//##ModelId=499E66810273
	~CMatrix();

	// ��������
	//##ModelId=499E66810274
	vector<T>       &operator[](int nIndex);
	//##ModelId=499E6681027E
	const vector<T> &operator[](int nIndex) const;

	//##ModelId=499E66810281
	unsigned int     Row()                  const;  // �к�
	//##ModelId=499E66810283
	unsigned int     Col()                  const;  // �к�

	//##ModelId=499E66810285
	void             Resize(unsigned int nRows, unsigned int nCols, const T &data = T());
private:
	// ���ݳ�Ա
	//##ModelId=499E6681028F
	unsigned int       m_nRows;  // ��������
	//##ModelId=499E66810290
	unsigned int       m_nCols;  // ��������
	//##ModelId=499E6681029E
	vector<vector<T> > m_Data;   // ��������
};

//##ModelId=499E6681026F
template<typename T>
CMatrix<T>::CMatrix(unsigned int nRows, unsigned int nCols, const T &data)
:m_nRows(nRows), m_nCols(nCols), m_Data(nRows, vector<T>(nCols, data))
{
	// ��ӳ�ʼ������
}

//##ModelId=499E66810273
template<typename T>
CMatrix<T>::~CMatrix()
{
	// �����Դ�ͷŴ���
}

//##ModelId=499E66810274
template<typename T>
vector<T> &CMatrix<T>::operator [](int nIndex)
{
	assert((nIndex >= 0) && (nIndex < m_nRows));

	return m_Data[nIndex];
}

//##ModelId=499E6681027E
template<typename T>
const vector<T> &CMatrix<T>::operator [](int nIndex) const
{
	assert((nIndex >= 0) && (nIndex < m_nRows));

	return m_Data[nIndex];
}

//##ModelId=499E66810281
template<typename T>
unsigned int CMatrix<T>::Row() const
{
	return m_nRows;
}

//##ModelId=499E66810283
template<typename T>
unsigned int CMatrix<T>::Col() const
{
	return m_nCols;
}

//##ModelId=499E66810285
template<typename T>
void CMatrix<T>::Resize(unsigned int nRows, unsigned int nCols, const T &data)
{
	for(int roll = 0; roll < m_nRows; ++ roll)
	{
		m_Data[roll].resize(nCols, data);
	}

	m_Data.resize(nRows, vector<T>(nCols, data));
	m_nRows = nRows;
	m_nCols = nCols;
}
#endif
