/**
*	made by alzq,dpb
*	08-08-28
*	edit alzq 08-29
*
*/

#include "StdAfx.h"
#include "PublicFunc.h"
#include <sstream>
#include <map>

T_mapStrStr PublicFunc::ExifTitleMap;
HANDLE PublicFunc::T_hMutex;

PublicFunc::PublicFunc(void)
{
}

PublicFunc::~PublicFunc(void)
{
}
//=====================================================================
// �� �� ����InitPublicFuncs
// ������������ʼ�������������в��ֳ�Ա
// ���������void
// ���������void
// �������ڣ�08.10.07
// �޸����ڣ�08.10.07
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void PublicFunc::InitPublicFuncs()
{
	T_hMutex=CreateMutex(NULL,FALSE,NULL);
}

//=====================================================================
// �� �� ����LockMutex
// �����������ȴ�������󲢸�����������
// ���������DWORD dwMilliseconds:�ȴ���ʱ�䣬��λ-����
// ���������void
// �������ڣ�08.10.07
// �޸����ڣ�08.10.07
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void PublicFunc::LockMutex(DWORD dwMilliseconds)
{
	WaitForSingleObject(T_hMutex,dwMilliseconds);
}

//=====================================================================
// �� �� ����UnLockMutex
// ����������������������
// ���������void
// ���������void
// �������ڣ�08.10.07
// �޸����ڣ�08.10.07
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void PublicFunc::UnLockMutex()
{
	ReleaseMutex(T_hMutex);
}

//=====================================================================
// �� �� ����DoChangeImageSize
// ������������image�����������
// ���������Image * image,				//ͼ�����ָ��
//			 UINT nImageWidth,			//ͼ��Ҫ�趨�����ؿ����
//			 UINT nImageHeight 			//ͼ��Ҫ�趨�����ظߣ����
// ���������BOOL:�����Ƿ����óɹ�
// �������ڣ�
// �޸����ڣ�08.09.11
// �� �ߣ�edit:alzq
// ����˵���������б��е�pImage�Ѿ�ָ��һ����Ч�ĵ�ַ�ռ�,ͼ��������߰�ԭ������������
//=====================================================================
BOOL PublicFunc::DoChangeImageSize(Magick::Image * image,		//ͼ�����ָ��
					   UINT nImageWidth,				//ͼ��Ҫ�趨�����ؿ����
					   UINT nImageHeight )				//ͼ��Ҫ�趨�����ظߣ����
{
	try
	{
		/*--alzq edit 08-29--*/
		LONG pWidth=image->columns();	//ͼ����
		LONG pHeight=image->rows();	//ͼ��߶�
		LONG realWidth=pWidth;									//��ʾͼ����
		LONG realHeight=pHeight;								//��ʾͼ��߶�
		double scaleW=(double)(pWidth)/nImageWidth;
		double scaleH=(double)(pHeight)/nImageHeight;
		double scale=scaleW>scaleH?scaleW:scaleH;
		if(scale>1)
		{
			realWidth=(LONG)(pWidth/scale);
			realHeight=(LONG)(pHeight/scale);
		}

		//����Magick�д�����������ݶ���Geometry���͵Ķ���
		Magick::Geometry geometry;
		geometry.width(realWidth);		//�趨���
		geometry.height(realHeight);	//�趨�߶�
		geometry.aspect( true );		//�������޸�ͼ���߱����Ŀ���
		/*--edit end --*/

		//����ͼ��Ŀ�߱���
		image->resize(geometry);
		geometry.~Geometry();
	}
	catch (Magick::Error & e)
	{
		AfxMessageBox(_T(e.what()));
		return FALSE;
	}

	return TRUE;
}


/*
����ֵ��TRUE��ʾͼ�����ݿ�����DC�ɹ�,FALSE��ʾͼ�����ݿ�����DC���ɹ�
������Image &inImage				//ͼ�����ݶ���
		CDC &SrcDC 					//ͼ�񿽱���ȥ��DC	�ڴ���SrcDCʱ��Ҫ��SrcDC�������ĳ�ʼ��
		CDC *pDC					//ͼ����Ҫ��ʾ��DC
*/
BOOL  PublicFunc::DoDCSelectObject( Magick::Image * inImage,			//ͼ�����ݶ���
						CDC * SrcDC ,							//ͼ�񿽱���ȥ��DC
						CDC * pDC)								//ͼ����Ҫ��ʾ��DC
{
	HBITMAP hBitmap;
	RGBQUAD *prgbaDIB = 0;
	BITMAPINFOHEADER bmi;
	//CDC * pDC=new CDC();

	// make sure we're getting a valid image!
	if (!inImage->isValid())
	{
		return FALSE;
	}

	// make sure we have a valid destination DC
	if (&pDC != NULL)
	{
		//
		// Set up the Windows bitmap header
		//
		//BITMAPINFOHEADER bmi;
		bmi.biSize = sizeof(BITMAPINFOHEADER);	// Size of structure
		bmi.biWidth = inImage->columns();	// Bitmaps width in pixels
		bmi.biHeight = (-1)*inImage->rows();	// Bitmaps height n pixels
		bmi.biPlanes = 1;				// Number of planes in the image
		bmi.biBitCount = 32;			// The number of bits per pixel
		bmi.biCompression = BI_RGB;		// The type of compression used
		bmi.biSizeImage = 0;			// The size of the image in bytes
		bmi.biXPelsPerMeter = 0;			// Horizontal resolution
		bmi.biYPelsPerMeter = 0;			// Veritical resolution
		bmi.biClrUsed = 0;			// Number of colors actually used
		bmi.biClrImportant = 0;			// Colors most important
		//			mBMI = bmi;	// keep it for clipboard use...

		hBitmap = CreateDIBSection
			(
			pDC->m_hDC,            // handle to device context
			(BITMAPINFO *)&bmi,    // pointer to structure containing bitmap size, format, and color data
			DIB_RGB_COLORS,        // color data type indicator: RGB values or palette indices
			(void**)&prgbaDIB,     // pointer to variable to receive a pointer to the bitmap's bit values
			NULL,                  // optional handle to a file mapping object
			0                      // offset to the bitmap bit values within the file mapping object
			);

		if ( !hBitmap )
		{
			return FALSE;
		}

		//
		// If image is non-opaque, create overlay the image on top of
		// a pattern background so non-opaque regions become evident.
		//

		Magick::Image * image=inImage;
		if (image->matte())
		{
			Magick::Image matteImage;
			matteImage.size(Magick::Geometry(image->columns(), image->rows()));
			matteImage.read("pattern:checkerboard");
			matteImage.composite(*image,0,0,AtopCompositeOp);
			image->~Image();
			image=&matteImage;
			//image->replaceImage(&matteImage);
		}

		//
		// Extract the pixels from Magick++ image object and convert to a DIB section
		//

		const unsigned int columns = image->columns();
		const unsigned int rows = image->rows();

		RGBQUAD *pDestPixel = prgbaDIB;

		for( unsigned int row = 0 ; row < rows ; row++ )
		{
			const PixelPacket *pPixels = image->getConstPixels(0,row,columns,1);
#if QuantumDepth == 8
			// Form of PixelPacket is identical to RGBQUAD when QuantumDepth==8
			memcpy((void*)pDestPixel,(const void*)pPixels,sizeof(PixelPacket)*columns);
			pDestPixel += columns;

#else	    // 16 or 32 bit Quantum
			// Transfer pixels, scaling to Quantum
			for( unsigned long nPixelCount = columns; nPixelCount ; nPixelCount-- )
			{
				pDestPixel->rgbRed = (BYTE)pPixels->red;//ScaleQuantumToChar(pPixels->red);
				pDestPixel->rgbGreen = (BYTE)pPixels->green;//ScaleQuantumToChar(pPixels->green);
				pDestPixel->rgbBlue = (BYTE)pPixels->blue;//ScaleQuantumToChar(pPixels->blue);
				pDestPixel->rgbReserved = 0;
				++pDestPixel;
				++pPixels;
			}
#endif
		}

		// Now copy the bitmap to device
		SrcDC->SelectObject( hBitmap );
		DeleteObject( hBitmap );
		DeleteObject(pDestPixel);

		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("DoDCSelectObject Error..."));
		return FALSE;
	}
}

//=====================================================================
// �� �� ����ReadImage
// �������������ļ���ȡΪָ����С������ͼ
// ���������FileInfoList * fileInfo
//			 int width,int height
// ���������Gdiplus::Image *
// �������ڣ�08.08.29
// �޸����ڣ�08.08.29
// �� �ߣ�alzq
// ����˵����
//=====================================================================
Gdiplus::Image * PublicFunc::ReadImage(FileInfoList * fileInfo,int width,int height)
{
	USES_CONVERSION;
	Gdiplus::Image * image=Gdiplus::Image::FromFile(A2W(fileInfo->GetFileFullPath().c_str()));
	Bitmap * bmp=new Bitmap(width,height,image->GetPixelFormat());
	Gdiplus::Image * tmpImg=bmp;
	
	Gdiplus::Graphics * graph=Gdiplus::Graphics::FromImage(tmpImg);
	graph->SetInterpolationMode(InterpolationModeHighQualityBicubic);
	graph->DrawImage(image,0,0,width,height);
	delete image;
	delete graph;

	return tmpImg;
}


//=====================================================================
// �� �� ����Long2Str
// ������������long������ת��Ϊstring
// ���������LONG l:��Ҫת��������
//			 int minSize:��С����
// ���������string
// �������ڣ�08.08.29
// �޸����ڣ�08.08.29
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string PublicFunc::Long2Str(LONG l,int minSize)
{
	stringstream stream; 
	string str;
	stream<<l;
	stream>>str;
	if(str.length()<minSize)
	{
		string str_head="";
		for(int n=0;n<minSize-str.length();n++)
		{
			str_head.append("0");
		}
		str_head.append(str);
		return str_head;
	}
	else
	{
		return str;
	}
}
	

//=====================================================================
// �� �� ����Time2Str
// ������������ʱ������ת��Ϊ�̶����ַ�����ʽ
// ���������LPSYSTEMTIME time
// ���������string
// �������ڣ�08.08.29
// �޸����ڣ�08.08.29
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string PublicFunc::Time2Str(LPSYSTEMTIME time)
{
	string timeStr="";
	timeStr.append(Long2Str(time->wYear,4));
	timeStr.append("-");
	timeStr.append(Long2Str(time->wMonth,2));
	timeStr.append("-");
	timeStr.append(Long2Str(time->wDay,2));
	timeStr.append(" ");
	timeStr.append(Long2Str(time->wHour,2));
	timeStr.append(":");
	timeStr.append(Long2Str(time->wMinute,2));
	timeStr.append(":");
	timeStr.append(Long2Str(time->wSecond,2));
	return timeStr;
}
		

//=====================================================================
// �� �� ����GetFileType
// ���������������ļ���չ���ó��ļ�����
// ���������string exName:�ļ���չ��
// ���������string
// �������ڣ�08.09.02
// �޸����ڣ�08.09.02
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string PublicFunc::GetFileType(string exName)
{
	if(exName.compare("exe")==0){return "Ӧ�ó���";}
	if(exName.compare("")==0){return "δ֪�ļ�";}
	return exName+"�ļ�";

}
		

//=====================================================================
// �� �� ����InitExifMap
// ������������ʼ��EXIF��Ϣ��ش洢����
// ���������void
// ���������void
// �������ڣ�08.09.04
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void PublicFunc::InitExifMes(void)
{
	/**
	*---------Exif��Ϣ����-----------

	("exif:ApertureValue","95/32")----------------------------��Ȧֵ
	("exif:ColorSpace","1")------------------------------------ɫ�ʿռ�(1:"sRGB";2:"δ֪")
	("exif:ComponentsConfiguration","...")--------------------��������("01020300":YCbCr;"04050600":RGB);
	("exif:CompressedBitsPerPixel","3/1")--------------------ͼ��ѹ����
	("exif:Compression","6")
	("exif:CustomRendered","0")
	("exif:DateTime","2008:08:06 09:24:10")--------------------ʱ���
	("exif:DateTimeDigitized","2008:08:06 09:24:10")--------���ֻ�ʱ��
	("exif:DateTimeOriginal","2008:08:06 09:24:10")------------����ʱ��
	("exif:DigitalZoomRatio","4000/4000")--------
	("exif:ExifImageLength","1944")----------------------------Exifͼ����
	("exif:ExifImageWidth","2592")----------------------------Exifͼ��߶�
	("exif:ExifOffset","196")------------
	("exif:ExifVersion","0220")--------------------------------Exif�汾(/100)
	("exif:ExposureBiasValue","0/3")------------------------�عⲹ��ֵ
	("exif:ExposureMode","0")--------------------------------�ع�ģʽ(1:"�ֶ�";"�Զ�")
	("exif:ExposureTime","1/20")----------------------------�����ٶ�ֵ(/s)
	("exif:FNumber","28/10")--------------------------------F-ֵ
	("exif:FileSource",".")------------------------------------�ļ���Դ(0x03:"digital still camera":"unknown")
	("exif:Flash","16")
	("exif:FlashPixVersion","0100")----------------------------FlashPix�汾(/100)
	("exif:FocalLength","7400/1000")------------------------����mm
	("exif:FocalPlaneResolutionUnit","2")--------------------��ƽ��ֱ浥λ(0:"";1:"";2:"Ӣ��";3:"����")
	("exif:FocalPlaneXResolution","2592000/291")------------��ƽ��X�ֱ���
	("exif:FocalPlaneYResolution","1944000/219")------------��ƽ��Y�ֱ���
	("exif:ISOSpeedRatings","200")----------------------------ISO����(ISO )
	("exif:InteroperabilityIndex","R98")
	("exif:InteroperabilityOffset","3362")
	("exif:InteroperabilityVersion","0100")
	("exif:JPEGInterchangeFormat","5108")
	("exif:JPEGInterchangeFormatLength","5329")
	("exif:Make","Canon")------------------------------------������
	("exif:MakerNote",".")
	("exif:MaxApertureValue","95/32")------------------------����Ȧֵ
	("exif:MeteringMode","5")--------------------------------���ģʽ(0:"δ֪";1:"ƽ��";2:"�����ص�ƽ�����";3:"���";4:"����";5:"����";6:"�ֲ�";255:"����";)
	("exif:Model","Canon PowerShot G9")------------------------�ͺ�
	("exif:Orientation","1")--------------------------------����(0:"";1:"����";2:"����";3:"����";4:"����";5:"left side top";6:"right side top";7:"right side bottom";8:"left side bottom";)--------
	("exif:RelatedImageLength","2592")------------------------����X�ߴ�
	("exif:RelatedImageWidth","1944")------------------------����Y�ߴ�
	("exif:ResolutionUnit","2")--------------------------------�ֱ浥λ(0:"";1:"";2:"Ӣ��";3:"����")
	("exif:SceneCaptureType","0")----------------------------��������(0x01:"A directly photographed image";"unknown")
	("exif:SensingMethod","2")
	("exif:ShutterSpeedValue","138/32")------------------------�����ٶ�
	("exif:WhiteBalance","0")--------------------------------��ƽ��(1:"�ֶ�";"�Զ�")
	("exif:XResolution","180/1")----------------------------X�ֱ���
	("exif:YCbCrPositioning","1")----------------------------YCbCrλ��(0:"";1:"����";2:"the datum point";)
	("exif:YResolution","180/1")----------------------------Y�ֱ���

	*------------------------------
	*/
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ApertureValue",CreateExifInfoItem("��Ȧֵ",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ColorSpace",CreateExifInfoItem("ɫ�ʿռ�",EXIF_COLORSPACE,"")));								//(1:"sRGB";2:"δ֪")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ComponentsConfiguration",CreateExifInfoItem("��������",EXIF_COMPONENTSCONFIGURATION,"")));	//("01020300":YCbCr;"04050600":RGB);
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:CompressedBitsPerPixel",CreateExifInfoItem("ͼ��ѹ����",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Compression",CreateExifInfoItem("Compression",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:CustomRendered",CreateExifInfoItem("CustomRendered",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DateTime",CreateExifInfoItem("ʱ���",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DateTimeDigitized",CreateExifInfoItem("���ֻ�ʱ��",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DateTimeOriginal",CreateExifInfoItem("����ʱ��",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:DigitalZoomRatio",CreateExifInfoItem("DigitalZoomRatio",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifImageLength",CreateExifInfoItem("Exifͼ����",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifImageWidth",CreateExifInfoItem("Exifͼ��߶�",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifOffset",CreateExifInfoItem("ExifOffset",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExifVersion",CreateExifInfoItem("Exif�汾",EXIF_EXIFVERSION,"")));					//(/100)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExposureBiasValue",CreateExifInfoItem("�عⲹ��ֵ",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExposureMode",CreateExifInfoItem("�ع�ģʽ",EXIF_EXPOSUREMODE,"")));					//(1:"�ֶ�";"�Զ�")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ExposureTime",CreateExifInfoItem("�����ٶ�ֵ",EXIF_MATCH,"")));						//(/s)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FNumber",CreateExifInfoItem("��Ȧ",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FileSource",CreateExifInfoItem("FileSource",EXIF_FILESOURCE,"")));					//�ļ���Դ(0x03:"digital still camera":"unknown")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Flash",CreateExifInfoItem("Flash",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FlashPixVersion",CreateExifInfoItem("FlashPix�汾",EXIF_FLASHPIXVERSION,"")));		//(/100)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalLength",CreateExifInfoItem("����",EXIF_MATCH,"")));								//mm
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalPlaneResolutionUnit",CreateExifInfoItem("��ƽ��ֱ浥λ",EXIF_FOCALPLANERESOLUTIONUNIT,"")));	//(0:"";1:"";2:"Ӣ��";3:"����")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalPlaneXResolution",CreateExifInfoItem("��ƽ��X�ֱ���",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:FocalPlaneYResolution",CreateExifInfoItem("��ƽ��Y�ֱ���",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ISOSpeedRatings",CreateExifInfoItem("ISO����",EXIF_ISOSPEEDRATINGS,"")));				//(ISO )
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:InteroperabilityIndex",CreateExifInfoItem("InteroperabilityIndex",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:InteroperabilityOffset",CreateExifInfoItem("InteroperabilityOffset",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:InteroperabilityVersion",CreateExifInfoItem("InteroperabilityVersion",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:JPEGInterchangeFormat",CreateExifInfoItem("JPEGInterchangeFormat",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:JPEGInterchangeFormatLength",CreateExifInfoItem("JPEGInterchangeFormatLength",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Make",CreateExifInfoItem("������",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:MakerNote",CreateExifInfoItem("MakerNote",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:MaxApertureValue",CreateExifInfoItem("����Ȧֵ",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:MeteringMode",CreateExifInfoItem("���ģʽ",EXIF_METERINGMODE,"")));					//(0:"δ֪";1:"ƽ��";2:"�����ص�ƽ�����";3:"���";4:"����";5:"����";6:"�ֲ�";255:"����";)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Model",CreateExifInfoItem("�ͺ�",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:Orientation",CreateExifInfoItem("����",EXIF_ORIENTATION,"")));						//(0:"";1:"����";2:"����";3:"����";4:"����";5:"left side top";6:"right side top";7:"right side bottom";8:"left side bottom";)--------
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:RelatedImageLength",CreateExifInfoItem("����X�ߴ�",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:RelatedImageWidth",CreateExifInfoItem("����Y�ߴ�",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ResolutionUnit",CreateExifInfoItem("�ֱ浥λ",EXIF_RESOLUTIONUNIT,"")));				//(0:"";1:"";2:"Ӣ��";3:"����")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:SceneCaptureType",CreateExifInfoItem("��������",EXIF_SCENECAPTURETYPE,"")));			//(0x01:"A directly photographed image";"unknown")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:SensingMethod",CreateExifInfoItem("SensingMethod",EXIF_NONE,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:ShutterSpeedValue",CreateExifInfoItem("�����ٶ�",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:WhiteBalance",CreateExifInfoItem("��ƽ��",EXIF_WHITEBALANCE,"")));					//(1:"�ֶ�";"�Զ�")
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:XResolution",CreateExifInfoItem("X�ֱ���",EXIF_MATCH,"")));
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:YCbCrPositioning",CreateExifInfoItem("YCbCrλ��",EXIF_YCBCRPOSITIONING,"")));			//(0:"";1:"����";2:"the datum point";)
	ExifTitleMap.insert(T_mapStrStr::value_type
		("exif:YResolution",CreateExifInfoItem("Y�ֱ���",EXIF_MATCH,"")));
}
		

//=====================================================================
// �� �� ����CreateExifInfoItem
// ��������������һ��ExifInfoValueItem����
// ���������String itemName,int dealMethod,String value;
// ���������ExifInfoValueItem
// �������ڣ�08.09.04
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
ExifInfoValueItem PublicFunc::CreateExifInfoItem(string itemName,int dealMethod,string value)
{
	ExifInfoValueItem item;
	item.ItemName=itemName;
	item.DealMethod=dealMethod;
	item.Value=value;
	return item;
}
		

//=====================================================================
// �� �� ����DealExifValue
// ��������������EXIF��ITEM���ƴ���EXIFֵ
// ���������string itemName:ITEM����
//			 string value:ITEMֵ
// ���������ExifInfoValueItem
// �������ڣ�08.09.04
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
ExifInfoValueItem PublicFunc::DealExifValue(string itemName,string value)
{
	//��ȡ���ƶ�Ӧ��Ԥ�洢�Ķ���
	ExifInfoValueItem methodItem=ExifTitleMap[itemName];
	ExifInfoValueItem item;
	item.ItemName=methodItem.ItemName;

	if(value.compare("")==0)
	{
		item.Value="";
		return item;
	}

	//����Ԥ�洢�����еĴ��������в�ͬ����
	switch(methodItem.DealMethod)
	{
		case EXIF_NONE:							//������ֱ�ӷ���ֵ
			item.Value=value;
			break;
		case EXIF_MATCH:						//���м��㴦��
			item.Value=DealExifMatch(value);
			break;
		case EXIF_COLORSPACE:					//ɫ�ʿռ䴦��(1:"sRGB";2:"δ֪")
			item.Value=value.compare("1")==0?"sRGB":"δ֪";
			break;
		case EXIF_COMPONENTSCONFIGURATION:		//�������ô���("01020300":YCbCr;"04050600":RGB);
			item.Value=value.compare("01020300")==0?"YCbCr":
				value.compare("04050600")==0?"RGB":"δ֪";
			break;
		case EXIF_EXIFVERSION:					//Exif�汾����(/100)
			item.Value=Number2Str((double)(StrToInt(value.c_str()))/(double)(100),2);
			break;
		case EXIF_EXPOSUREMODE:					//�ع�ģʽ����(1:"�ֶ�";"�Զ�")
			item.Value=value.compare("1")==0?"�ֶ�":"�Զ�";
			break;
		case EXIF_FILESOURCE:					//�ļ���Դ����(0x03:"digital still camera":"unknown")
			item.Value=value.compare("0x03")==0?"digital still camera":"unknown";
			break;
		case EXIF_FLASHPIXVERSION:				//FlashPix�汾����(/100)
			item.Value=Number2Str((double)(StrToInt(value.c_str()))/(double)(100),2);
			break;
		case EXIF_FOCALPLANERESOLUTIONUNIT:		//��ƽ��ֱ浥λ����(0:"";1:"";2:"Ӣ��";3:"����")
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"":
				value.compare("2")==0?"Ӣ��":
				value.compare("3")==0?"����":"δ֪";
			break;
		case EXIF_ISOSPEEDRATINGS:				//ISO���ʴ���(ISO +)
			item.Value="ISO "+value;
			break;
		case EXIF_METERINGMODE:					//���ģʽ����(0:"δ֪";1:"ƽ��";2:"�����ص�ƽ�����";3:"���";4:"����";5:"����";6:"�ֲ�";255:"����";)
			item.Value=value.compare("0")==0?"δ֪":
				value.compare("1")==0?"ƽ��":
				value.compare("2")==0?"�����ص�ƽ�����":
				value.compare("3")==0?"���":
				value.compare("4")==0?"����":
				value.compare("5")==0?"����":
				value.compare("6")==0?"�ֲ�":
				value.compare("255")==0?"����":"δ֪";
			break;
		case EXIF_ORIENTATION:					//������(0:"";1:"����";2:"����";3:"����";4:"����";5:"left side top";6:"right side top";7:"right side bottom";8:"left side bottom";)
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"����":
				value.compare("2")==0?"����":
				value.compare("3")==0?"����":
				value.compare("4")==0?"����":
				value.compare("5")==0?"left side top":
				value.compare("6")==0?"right side top":
				value.compare("7")==0?"right side bottom":
				value.compare("8")==0?"left side bottom":"δ֪";
			break;
		case EXIF_RESOLUTIONUNIT:				//�ֱ浥λ����(0:"";1:"";2:"Ӣ��";3:"����")
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"":
				value.compare("2")==0?"Ӣ��":
				value.compare("4")==0?"����":"δ֪";
			break;
		case EXIF_SCENECAPTURETYPE:				//�������ʹ���(1:"A directly photographed image";"unknown")
			item.Value=value.compare("1")==0?"A directly photographed image":"δ֪";
			break;
		case EXIF_WHITEBALANCE:					//��ƽ�⴦��(1:"�ֶ�";"�Զ�")
			item.Value=value.compare("1")==0?"�ֶ�":"�Զ�";
			break;
		case EXIF_YCBCRPOSITIONING:				//YCbCrλ�ô���(0:"";1:"����";2:"the datum point";)
			item.Value=value.compare("0")==0?"":
				value.compare("1")==0?"����":
				value.compare("2")==0?"the datum point":"δ֪";
			break;
		default:
			item.Value=value;
			break;
	}

	return item;
}
		

//=====================================================================
// �� �� ����DealExifMatch
// ������������EXIF��Ϣ����Ҫ������ַ������м���
// ���������string str
// ���������string
// �������ڣ�08.09.04
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string PublicFunc::DealExifMatch(string str)
{
	int s=(int)str.find_first_of("/");
	double d1=(double)(StrToInt(string(str,0,s).c_str()));
	double d2=(double)(StrToInt(string(str,s+1).c_str()));
	return Number2Str(d1/d2,2);
}
		

//=====================================================================
// �� �� ����Number2Str
// ����������������ת��ΪString�������涨С��λ
// ���������double num,int maxS
// ���������string
// �������ڣ�08.09.04
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
string PublicFunc::Number2Str(double num,int maxS)
{
	stringstream stream; 
	string str;
	stream<<num;
	stream>>str;
	int pointS=(int)str.find_first_of(".");
	if(maxS==0)
	{
		return string(str,0,pointS);
	}
	else
	{
		if(pointS==-1)
		{
			//��������С����ʱ
			return str;
		}
		else
		{
			return string(str,0,pointS+maxS+1);
		}
	}
}
	

//=====================================================================
// �� �� ����DeleteThread
// ���������������߳�
// ���������HANDLE handle:��Ҫ�������߳̾��
// ���������void
// �������ڣ�08.09.15
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void PublicFunc::DeleteThread (HANDLE handle)
{
	DWORD exitCode;			//�߳�״̬��
	if(handle!=NULL)
	{
		GetExitCodeThread(handle,&exitCode);	//��ȡ�߳�״̬��
		if(exitCode==STILL_ACTIVE)
		{
			//������״̬Ϊ����״̬ʱ���ر��߳�
			//TerminateThread(m_hLoadImageDC,0);
			TerminateThread(handle,0);
			CloseHandle(handle);
		}
	}
}
	

//=====================================================================
// �� �� ����LowStr
// �������������ַ���ȫ��ת��ΪСд
// ���������string &str
// ���������void
// �������ڣ�08.09.24
// �޸����ڣ�
// �� �ߣ�alzq
// ����˵����
//=====================================================================
void PublicFunc::LowStr( string &str )
{
	int i;
	int nlen;

	char *ps = (char *)str.c_str();

	int d='A' - 'a';

	nlen = (int)str.length();
	for( i=0;i<nlen;i++ )
	{
		if( ps[i]<='Z' && ps[i]>='A' )
			ps[i] =  ps[i] - d;
	}
}
	

//=====================================================================
// �� �� ����CreateShortcut
// �������������ַ���ȫ��ת��ΪСд
// ���������LPCSTR szPath:��ݷ�ʽ����·��-������.lnk��β
//			 LPCSTR szLink:ָ����ļ�·��
// ���������BOOL
// �������ڣ�08.10.07
// �޸����ڣ�
// �� �ߣ�alzq   
// ����˵����jiangxh changed 2008.10.9
//=====================================================================
BOOL PublicFunc::CreateLink(LPCSTR szPath,LPCSTR szLink)
{	
	CoInitialize(NULL);
	HRESULT hres;
	IShellLink * psl;
	IPersistFile * ppf;
	WORD wsz[MAX_PATH];
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,IID_IShellLink, (void**)&psl);

	if(FAILED(hres))
		return FALSE;

	psl-> SetPath((LPCTSTR)szPath);
	hres = psl-> QueryInterface(IID_IPersistFile, (void**)&ppf);

	if(FAILED(hres))
		return FALSE;

	MultiByteToWideChar(CP_ACP, 0, szLink, -1, (LPWSTR)wsz, MAX_PATH);
	hres = ppf-> Save((LPCOLESTR)wsz, STGM_READWRITE);

	ppf-> Release();
	psl-> Release();
	//jxh ɾ�� 2008.10.9
	//delete psl;
	//delete ppf;
	CoUninitialize();

	return TRUE; 
}


	

//=====================================================================
// �� �� ����CutOrCopyFiles
// ����������lpBuffer���ļ������б�uBufLen:�ַ������ȣ�bCopy����Ϊ���ƣ���Ϊ����
// ���������
// ���������void
// �������ڣ�2008.10.8
// �޸�����:
// �� �ߣ�   jiangxh
// ����˵���� 
//=====================================================================
void PublicFunc::CutOrCopyFiles(char *lpBuffer,UINT uBufLen,BOOL bCopy)
{
	UINT uDropEffect;
	DROPFILES dropFiles;
	UINT uGblLen,uDropFilesLen;
	HGLOBAL hGblFiles,hGblEffect;
	char *szData,*szFileList;

	DWORD *dwDropEffect;

	uDropEffect=RegisterClipboardFormat("Preferred DropEffect");
	hGblEffect=GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE,sizeof(DWORD));
	dwDropEffect=(DWORD*)GlobalLock(hGblEffect);
	if(bCopy)
		*dwDropEffect=DROPEFFECT_COPY;
	else 
		*dwDropEffect=DROPEFFECT_MOVE;
	GlobalUnlock(hGblEffect);

	uDropFilesLen=sizeof(DROPFILES);
	dropFiles.pFiles =uDropFilesLen;
	dropFiles.pt.x=0;
	dropFiles.pt.y=0;
	dropFiles.fNC =FALSE;
	dropFiles.fWide =TRUE;

	uGblLen=uDropFilesLen+uBufLen*2+8;
	hGblFiles= GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, uGblLen);
	szData=(char*)GlobalLock(hGblFiles);
	memcpy(szData,(LPVOID)(&dropFiles),uDropFilesLen);
	szFileList=szData+uDropFilesLen;

	MultiByteToWideChar(CP_ACP,MB_COMPOSITE,
		lpBuffer,uBufLen,(WCHAR *)szFileList,uBufLen);

	GlobalUnlock(hGblFiles);

	if( OpenClipboard(NULL) )
	{
		EmptyClipboard();
		SetClipboardData( CF_HDROP, hGblFiles );
		SetClipboardData(uDropEffect,hGblEffect);
		CloseClipboard();
	}
} 

//=====================================================================
// �� �� ����ReadShortcut
// ����������
// ���������
// ���������void
// �������ڣ�2008.10.10
// �޸�����:
// �� �ߣ�   jiangxh
// ����˵���� 
//=====================================================================
bool   PublicFunc::ReadShortcut(LPWSTR   lpwLnkFile,   LPSTR   lpDescFile)
{
	bool   bReturn   =   true;   
	IShellLink   *pShellLink;   

	if(bReturn)   
	{   
		bReturn   =   (CoInitialize(NULL)   !=   S_OK);   
		if(bReturn)   
		{   
			bReturn   =   CoCreateInstance   (CLSID_ShellLink,   NULL,   CLSCTX_INPROC_SERVER,   
				IID_IShellLink,   (void   **)&pShellLink)   >=   0;   
			if(bReturn)   
			{   
				IPersistFile   *ppf;   
				bReturn   =   pShellLink->QueryInterface(IID_IPersistFile,   (void   **)&ppf)   >=   0;   
				if(bReturn)   
				{   
					bReturn   =   ppf->Load(lpwLnkFile,   TRUE)   >=   0;   
					if(bReturn)   
					{   
						pShellLink->GetPath(lpDescFile,   MAX_PATH,   NULL,   0);   
					}   
					ppf->Release   ();   
				}   
				pShellLink->Release   ();   
			}   
			CoUninitialize();   
		}   
	}   
	return   bReturn;   
}
	

//=====================================================================
// �� �� ����ReadImageList
// ������������ָ��·����ȡCImageList
// ���������CString imgPath,CImageList * list,int width,int height,int count
// ���������void
// �������ڣ�2008.10.13
// �޸�����:
// �� �ߣ�   alzq
// ����˵���� 
//=====================================================================
void   PublicFunc::ReadImageList(CString imgPath,CImageList * list)
{
	HBITMAP hBitmap;
	CBitmap pBitmap;

	hBitmap = (HBITMAP)LoadImage(NULL,imgPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	pBitmap.Attach(hBitmap); 

	list->Add(&pBitmap,RGB(255,255,255));
}

