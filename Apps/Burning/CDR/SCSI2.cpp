// SCSI2.cpp: implementation of the SCSI2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CDR.h"
#include "SCSI2.h"
#include "scsireg.h"
#include "osta_udf.h"
#include "ecma_167.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#pragma pack(1)

extern timestamp *
udf_time_to_stamp(timestamp *dest, time_t tv_sec, long tv_usec);
extern Uint16
udf_crc(Uchar *data, Uint32 size);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SCSI2::SCSI2()
{
	hEventSRB=NULL;
	m_HA=1;
	m_ID=0;
	m_LUN=0;
	m_silence=false;
}
//----------------------------------------------------------------------------

SCSI2::~SCSI2()
{
	FreeLibrary(hinstWNASPI32);
}
//----------------------------------------------------------------------------
void SCSI2::SCSISelectDevice(BYTE HA_num, BYTE SCSI_Id, BYTE SCSI_Lun)
{
	m_HA=HA_num;
	m_ID=SCSI_Id;
	m_LUN=SCSI_Lun;
}
//----------------------------------------------------------------------------

bool SCSI2::ASPIStart ( void ) {

// load WNASPI32.DLL
	hinstWNASPI32 = LoadLibrary( "WNASPI32" );
	if( !hinstWNASPI32 )
	{
	    MessageBox ( NULL, "LoadLibrary:\nWNASPI32.DLL not found.",
                           "Error FS 002", MB_ICONSTOP );
        return false;
	}
	pfnGetASPI32Buffer        = (int(_cdecl*)(PASPI32BUFF))GetProcAddress( hinstWNASPI32, "GetASPI32Buffer" );
	pfnFreeASPI32Buffer       = (int(_cdecl*)(PASPI32BUFF))GetProcAddress( hinstWNASPI32, "FreeASPI32Buffer" );
	pfnTranslateASPI32Address = (int(_cdecl*)(PDWORD, PDWORD))GetProcAddress( hinstWNASPI32,"TranslateASPI32Address" );


// load the address of GetASPI32SupportInfo
	pfnGetASPI32SupportInfo   = (DWORD(_cdecl*)(void))GetProcAddress( hinstWNASPI32, "GetASPI32SupportInfo" );
	if ( pfnGetASPI32SupportInfo == NULL )
      {
        MessageBox ( NULL, "GetProcAddress:\nGetASPI32SupportInfo not fount.",
                           "Error FS 003", MB_ICONSTOP );
        return false;
      }

// load the address of SendASPI32Command
	pfnSendASPI32Command      = (DWORD (_cdecl*)( LPSRB ))GetProcAddress( hinstWNASPI32, "SendASPI32Command" );
	if ( pfnSendASPI32Command == NULL )
      {
        MessageBox ( NULL, "GetProcAddress:\npfnSendASPI32Command not found.",
                           "Error FS 004", MB_ICONSTOP );
        return false;
      }

// call GetASPI32SupportInfo
   DWORD dwSupportInfo = pfnGetASPI32SupportInfo ( );
   BYTE  byHaCount;
   BYTE  byASPIStatus;
   byHaCount = LOBYTE ( LOWORD ( dwSupportInfo ) );
   byASPIStatus = HIBYTE ( LOWORD ( dwSupportInfo ) );
   switch ( byASPIStatus )
      {
        case SS_COMP: // ASPI support OK, now create the event object
             hEventSRB = CreateEvent ( NULL, true, false, NULL );
             if ( !hEventSRB )
                {
                  MessageBox ( NULL, "Could not create the event object.",
                               "Error FS 005", MB_ICONEXCLAMATION );
                  return false;
                }
             return true; // true = everything OK !!!
		case SS_NO_ADAPTERS:
			 AfxMessageBox("No SCSI2 device found.");
			 return false;
        case SS_NO_ASPI:
             MessageBox ( NULL, "Could not find the ASPI manager.",
                          "GetASPISupportInfo:", MB_ICONSTOP );
             return false;
        case SS_ILLEGAL_MODE:
             MessageBox ( NULL, "ASPI for Windows does not support real mode.",
                          "GetASPISupportInfo:", MB_ICONSTOP );
             return false;
        case SS_OLD_MANAGER:
             MessageBox ( NULL, "Old ASPI manager.",
                          "GetASPISupportInfo:", MB_ICONSTOP );
             return false;
        default:
             MessageBox ( NULL, "Error initializing ASPI.",
                          "GetASPISupportInfo:", MB_ICONSTOP );
             return false;
      }
   

}
//----------------------------------------------------------------------------

void SCSI2::ASPIStop ( void ) {

// release the event object
   if(hEventSRB!=NULL) CloseHandle ( hEventSRB );
// unload WNASPI32.DLL
   FreeLibrary ( hinstWNASPI32 );
   return;
}
//--------------------------------------------------------------------------
bool SCSI2::ASPIReset () {

	CString szReturnString;
	unsigned char szBuffer[40];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_RESET_DEV;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 0;

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );
	return srbExec.SRB_Status == SS_COMP;
}
//----------------------------------------------------------------------------
int SCSI2::SCSIBusScan ( DRIVEINFO* Info,BYTE type,bool silent ) {

	// PHASE 1: determine how many host adapters are installed and the
	//          name and version of the ASPI manager

	// initialize the SRB for the first inquiry
	SRB_HAInquiry srbHAInquiry;
	memset ( &srbHAInquiry, 0, sizeof ( SRB_HAInquiry ) );
	srbHAInquiry . SRB_Cmd = SC_HA_INQUIRY;
	srbHAInquiry . SRB_HaId = 0;

	// get the number of host adapters installed
	pfnSendASPI32Command ( (LPSRB)&srbHAInquiry );
	if ( srbHAInquiry.SRB_Status != SS_COMP ){
		MessageBox ( NULL, "Host adapter inquiry failed.",
						   "Error FS 006:", MB_ICONSTOP );
		return 0;
	}
	BYTE HA_Count = srbHAInquiry . HA_Count;
	int HA=m_HA;
	int ID=m_ID;
	int LUN=m_LUN;
	int count=0;
	// for each host adapter...
   for ( m_HA = 0; m_HA < HA_Count; m_HA++ )
       {
         memset ( &srbHAInquiry, 0, sizeof ( SRB_HAInquiry ) );
         srbHAInquiry . SRB_Cmd = SC_HA_INQUIRY;
         srbHAInquiry . SRB_HaId = m_HA;
         pfnSendASPI32Command ( ( LPSRB ) &srbHAInquiry );
         if ( srbHAInquiry . SRB_Status != SS_COMP )
            {
              CString s;
			  s.Format("Host adapter %d inquiry failed.",m_HA);
              AfxMessageBox ( s );
            }
         else
            {
              	// for each SCSI id...
              for ( m_ID = 0; m_ID < 8; m_ID++ )
                  {
                    
					// for each logical unit...
                    for ( m_LUN = 0; m_LUN < 8; m_LUN++ )
                        {
                          CString szDevice = "Unknown device type.";
                          SRB_GDEVBlock srbGDEVBlock;
                          memset ( &srbGDEVBlock, 0, sizeof ( srbGDEVBlock ) );
                          srbGDEVBlock.SRB_Cmd = SC_GET_DEV_TYPE;
                          srbGDEVBlock.SRB_HaId = m_HA;
                          srbGDEVBlock.SRB_Target = m_ID;
                          srbGDEVBlock.SRB_Lun = m_LUN;
                          pfnSendASPI32Command ( ( LPSRB ) &srbGDEVBlock );
                          if ( srbGDEVBlock.SRB_Status != SS_COMP ) continue;
						  BYTE devType=srbGDEVBlock.SRB_DeviceType;
						  switch(devType){
						  case  DTYPE_DASD:
                              szDevice= "Direct access storage device" ;
							  break;
                          case DTYPE_SEQD:
                              szDevice= "Sequntial access storage device";
							  break;
                          case DTYPE_PRNT:
                              szDevice= "Printer device" ;
							  break;
                          case DTYPE_PROC:
                              szDevice= "Processor device" ;
							  break;
                          case DTYPE_WORM:
                              szDevice= "WORM device" ;
							  break;
                          case DTYPE_CDROM:
                              szDevice= "CD-ROM device" ;
							  break;
                          case DTYPE_SCAN:
                              szDevice= "Scanner device" ;
							  break;
                          case DTYPE_OPTI:
                              szDevice= "Optical memory device" ;
							  break;
                          case DTYPE_JUKE:
                              szDevice= "Medium changer device" ;
							  break;
                          case DTYPE_COMM:
                              szDevice= "Communication device" ;
							  break;
						  }
						  CString inq=SCSIInquiry(false);
						  if(type!=0xff&&type!=devType)	continue;
						  if(!silent){
							CString szMsg ;
							szMsg.Format("Host adapter:%d\nSCSI ID:%d\nLogical Unit:%d\n%s\r\n%s",
								m_HA,m_ID,m_LUN,szDevice,inq);
							AfxMessageBox ( szMsg );
						  }
						  Info[count].m_HA=m_HA;
						  Info[count].m_ID=m_ID;
						  Info[count].m_LUN=m_LUN;
						  Info[count].m_name=inq;
						  count++;
                        }
                  }
           }
      }

   SCSISelectDevice(HA,ID,LUN);
   return count;
}

//--------------------------------------------------------------------------
CString SCSI2::SCSIInquiry (bool multiline) {

	CString s,temp;
	unsigned char szBuffer[40];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 6;
	srbExec.CDBByte [ 0 ] = SCSI_INQUIRY;
	srbExec.CDBByte [ 4 ] = 36;  // allocation length per szBuffer [ ]

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );
	scsi_inquiry* result=(scsi_inquiry*)szBuffer;

	if ( srbExec.SRB_Status != SS_COMP )
		s="Inquiry error.";
	else{
		if(multiline)
			s="Vendor:\t"+CString(result->vendor_info).Left(8)+
						"\nProduct :\t"+CString(result->prod_ident).Left(16)+
						"\nVersion :\t"+CString(result->prod_revision).Left(4);
		else{
			temp=CString(result->vendor_info).Left(8);
			temp.TrimRight();
			if(!temp.IsEmpty())	s=temp+" ";
			temp=CString(result->prod_ident).Left(16);
			temp.TrimRight();
			s+=temp+" (Ver ";
			temp=CString(result->prod_revision).Left(4);
			temp.TrimRight();
			s+=temp+")";
		}
	}
	return s;
}
//--------------------------------------------------------------------------
bool SCSI2::CloseSession () {

	CString szReturnString;
	unsigned char szBuffer[40];
	SRB_ExecSCSICmd srbExec;
	BYTE buffer[block_size*0x168];

	//Anchor Volume Descriptor Pointer
	//ECMA167 3/14
	anchorVolDescPtr AVDP;
	memset(&AVDP,0,sizeof(anchorVolDescPtr));
	AVDP.mainVolDescSeqExt.extLocation=0x201;
	AVDP.mainVolDescSeqExt.extLength=0x8000;
	AVDP.reserveVolDescSeqExt.extLocation=0x211;
	AVDP.reserveVolDescSeqExt.extLength=0x8000;

	//Volume Identifiers
	//ECMA167 2/4
	memset(buffer,0,block_size*0x168);
	sprintf((char*)buffer+0x10*block_size+1,"BEA01\1");
	sprintf((char*)buffer+0x11*block_size+1,"NSR02\1");
	sprintf((char*)buffer+0x12*block_size+1,"TEA01\1");
	AVDP.descTag=fillTag(TAG_IDENT_AVDP,(BYTE*)&AVDP+0x10,0x1f0,0x100);
	*(anchorVolDescPtr*)(buffer+0x100*block_size)=AVDP;
	while( TestUnitReady() );
	if(!SetWriteParameters(1,10,4,0x20))		return false;
	if(!WritePacket(buffer,0,0x168,false))		return false;
	

	//Write End of Session Data, which includes VAT ICB and AVDPs
	//UNIVERSAL DISK FORMAT SPECIFICATION REV2.01 P133
	while( TestUnitReady() );
	memset(buffer,0,block_size*0x168);
	track_info p1;
	ReadTrackInfo(0,&p1);
	int lastICB=toInt32(p1.next_writtable_addr)-8;
	SCSIRead(buffer,lastICB,1);
	fileEntry lastVAT=*(fileEntry*)buffer;
	lastVAT.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&lastVAT+0x10,
		lastVAT.descTag.descCRCLength,lastICB-0x223+0x108);
	memset(buffer,0,block_size*0x168);
	AVDP.descTag=fillTag(TAG_IDENT_AVDP,(BYTE*)&AVDP+0x10,0x1f0,lastICB+8);
	for(int j=0;j<0x100;j++)
	*(anchorVolDescPtr*)(buffer+j*block_size)=AVDP;
	memcpy(buffer+0x100*block_size,&lastVAT,lastVAT.descTag.descCRCLength+0x10);
	while( TestUnitReady() );
	if(!SetWriteParameters(0,10,5,0x20))		return false;
	if(!WritePacket(buffer,lastICB+8,0x101))	return false;
	

	//Close Track
	while( TestUnitReady() );
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x5b;
	srbExec.CDBByte [ 1 ] = 1;	//Immediate
	srbExec.CDBByte [ 2 ] = 1;  //Close Track
	srbExec.CDBByte [ 5 ] = 2;
	
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );
	if(checkError(srbExec.SRB_Status)!="SUCCESS"&&!m_silence){
		m_sense=*(scsi_sense*)srbExec.SenseArea;
		AfxMessageBox(checkSense());
		return false;
	}
	
	//Close Session
	while( TestUnitReady() );
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x5b;
	srbExec.CDBByte [ 1 ] = 1;	//Immediate
	srbExec.CDBByte [ 2 ] = 2;  //Close Session
	srbExec.CDBByte [ 5 ] = 1;
	
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );
	if(checkError(srbExec.SRB_Status)!="SUCCESS"&&!m_silence){
		m_sense=*(scsi_sense*)srbExec.SenseArea;
		AfxMessageBox(checkSense());
	}
	return srbExec.SRB_Status == SS_COMP;

}
//--------------------------------------------------------------------------
bool SCSI2::SaveFileAs(int ID,CString path){

	disk_info di;
	ReadDiskInfo(&di);
	track_info ti;
	ReadTrackInfo(di.numsess>1?2:0,&ti);
	if(di.numsess>1)
		m_lba=toInt32(ti.track_start_addr)+toInt32(ti.track_size)-0x101;
	else
		m_lba=toInt32(ti.next_writtable_addr);
	
	BYTE blk[block_size];
	
	int lastVATICB_Addr=m_lba-8;
	if(!SCSIRead(blk,lastVATICB_Addr,1))	return false;
	fileEntry lastVATICB=*(fileEntry*)blk;
	int UniqueID=(int)lastVATICB.uniqueID+1;
	
	int VAT_addr,FEAddr;
	long_ad		*ad;

	if(lastVATICB.icbTag.flags==3){/*Embedded VAT*/
		FEAddr=*(Uint32*)((BYTE*)&lastVATICB+0xb8+ID*4);
	}
	else if(lastVATICB.icbTag.flags==1){
		ad=(long_ad*)((BYTE*)&lastVATICB+0xb0);
		VAT_addr=ad->extLocation.logicalBlockNum+(8+4*ID)/block_size;
		if(!SCSIRead(blk,VAT_addr+0x223,1,0))	return false;
		FEAddr=*(Uint32*)(blk+(8+4*ID)%block_size);
	}

	
	if(!SCSIRead(blk,FEAddr+0x223,1,0))	return false;
	ad=(long_ad*)((BYTE*)&blk+0x10c);
	int fileLen=ad->extLength;
	int blocks=fileLen/block_size+(fileLen%block_size?1:0);
	BYTE* buffer=new BYTE[block_size*blocks];
	int offset=0;
	while(blocks>0){
		int thisReadBlocks=blocks>16?16:blocks;
		if(!SCSIRead(buffer+offset*block_size,
			ad->extLocation.logicalBlockNum+0x223+offset,
			thisReadBlocks,0))	
			return false;
		offset+=thisReadBlocks;
		blocks-=thisReadBlocks;
		
	}
	CFile outFile;
	if(outFile.Open(path,CFile::modeCreate | CFile::modeWrite)){
		outFile.Write(buffer,fileLen);
		outFile.Close();
	}
	delete buffer;
	return true;

}
//--------------------------------------------------------------------------

CString SCSI2::ListFiles(){

	disk_info di;
	ReadDiskInfo(&di);
	track_info ti;
	ReadTrackInfo(di.numsess>1?2:0,&ti);
	if(di.numsess>1)
		m_lba=toInt32(ti.track_start_addr)+toInt32(ti.track_size)-0x101;
	else
		m_lba=toInt32(ti.next_writtable_addr);
	
	BYTE blk[block_size];
	CString result;
	
	int lastVATICB_Addr=m_lba-8;
	if(!SCSIRead(blk,lastVATICB_Addr,1))	return "";
	fileEntry lastVATICB=*(fileEntry*)blk;
	int UniqueID=(int)lastVATICB.uniqueID+1;
	
	int VATLength=4;
	int totalVATlen=VATLength;
	int lastVAT_len,lastVAT_addr,
		adExtLen,firstVAT_addr,lastFIDDICBAddr;
	bool VATEmbedded,FIDDEmbedded;
	long_ad		*ad;

	if(lastVATICB.icbTag.flags==3){/*Embedded VAT*/
		VATEmbedded=1;
		lastVAT_len=lastVATICB.lengthAllocDescs;
		totalVATlen+=lastVATICB.lengthAllocDescs;
		lastVAT_addr=lastVATICB_Addr;
	}
	else if(lastVATICB.icbTag.flags==1){
		VATEmbedded=0;
		ad=(long_ad*)((BYTE*)&lastVATICB+0xb0);
		adExtLen=ad->extLength;
		firstVAT_addr=ad->extLocation.logicalBlockNum;
		lastVAT_addr=firstVAT_addr+adExtLen/block_size;
		lastVAT_len=adExtLen;
		totalVATlen+=adExtLen;
	}

	int fileID=(totalVATlen-VATLength-0x24)/4;/*Number of existing files*/
	if(VATEmbedded)	lastFIDDICBAddr=*(Uint32*)((BYTE*)&lastVATICB+0xb4);
	else{
		if(!SCSIRead(blk,firstVAT_addr+0x223,1,0))	return "";
		lastFIDDICBAddr=*(Uint32*)(blk+4);
	}
	if(!SCSIRead(blk,lastFIDDICBAddr+0x223,1,0))	return "";
	fileEntry lastFIDDICB=*(fileEntry*)blk;

	if(lastFIDDICB.icbTag.flags==3){
		//Embedded FIDD
		//We can get the file list from it directly
		FIDDEmbedded=true;
		int total_len=lastFIDDICB.lengthAllocDescs;
		fileIdentDesc* FIDD=(fileIdentDesc*)(blk+176+40);
		for(;(BYTE*)FIDD<blk+176+total_len;){
			CString name;
			for(int j=2;j<FIDD->lengthFileIdent;j+=2){
				name+=(char)(FIDD->other[j]);
			}
			int len=38+FIDD->lengthFileIdent;
			len+=(4-(len)%4)%4;
			FIDD=(fileIdentDesc*)((BYTE*)FIDD+len);
			if(!name.IsEmpty())	result+=name+"\r\n";
		}
		
	}
	else if(lastFIDDICB.icbTag.flags==1){
		//Non-Embedded FIDD
		//We have to get the locations of FIDDs,
		//And get the content one by one
		FIDDEmbedded=false;
		int leftOver=0;
		long_ad* p=(long_ad*)((BYTE*)&lastFIDDICB+0xb0);
		BYTE buffer[2*block_size];
			
		while(p->extLength){
			int blocks=p->extLength/block_size+
				p->extLength%block_size?1:0;
			if(!SCSIRead(buffer+leftOver,p->extLocation.logicalBlockNum+0x223,blocks))
				return "";
			int total_len=p->extLength+leftOver;
			leftOver=0;
			fileIdentDesc* FIDD=(fileIdentDesc*)(buffer);
			for(;(BYTE*)FIDD<buffer+total_len;){
				CString name;
				int len=38+FIDD->lengthFileIdent;
				len+=(4-(len)%4)%4;

				if((BYTE*)FIDD>buffer+total_len-len){
					leftOver=buffer+total_len-(BYTE*)FIDD;
					memcpy(buffer,(BYTE*)FIDD,leftOver);
					break;
				}
				for(int j=2;j<FIDD->lengthFileIdent;j+=2){
					name+=(char)(FIDD->other[j]);
				}
				
				FIDD=(fileIdentDesc*)((BYTE*)FIDD+len);
				if(!name.IsEmpty())	result+=name+"\r\n";
			}
			p++;
		}
	}
	return result;
}
//--------------------------------------------------------------------------
bool SCSI2::WriteFiles (CString fileName) {

	timestamp	t;
	time_t		timenow;
	char* impId="*Adaptec DirectCD";		//Pretend it's created by DirectCD
	char* idSuffix="\x050\x001\x006";
	regid*id;

	time( &timenow );
	udf_time_to_stamp(&t, timenow, 0);
	
	CStringList* list=chopFileNames(fileName);
	int filesCount=list->GetCount();
	int totalDataBlocks=0,totalBlocks=0;
	Uint64 totalVATlen,totalFIDDlen,fileID;
	Uint32 FIDDLength=0;
	for(int j=0;j<filesCount;j++){
		CString name=list->GetAt(list->FindIndex(j));
		CFile file(name,CFile::modeRead);
		if(name.ReverseFind('\\')>=0)	name=name.Mid(name.ReverseFind('\\')+1);
		totalDataBlocks+=(int)ceil(file.GetLength()/(double)block_size);
		int len=39+2*name.GetLength();
		FIDDLength+=len+(4-len%4)%4;
	}
	int		VATLength=4*filesCount;
	Uint32	lastFIDD_len,lastVAT_len;
	Uint32	lastFIDD_addr,lastVAT_addr;
	bool	FIDDEmbedded,VATEmbedded;
	int		newFIDDBlocks,newVATBlocks,existingVATBlocks,firstVAT_addr;

	BYTE blk[block_size];
	memset(blk,0,block_size);
	track_info ti;
	ReadTrackInfo(0,&ti);
	int lastLeadOut=toInt32(ti.track_start_addr)+toInt32(ti.track_size);
	m_lba=toInt32(ti.next_writtable_addr);
	
	int lastVATICB_Addr=m_lba-8;
	SCSIRead(blk,lastVATICB_Addr,1);
	fileEntry lastVATICB=*(fileEntry*)blk;
	int UniqueID=(int)lastVATICB.uniqueID+1;

	totalVATlen=VATLength;
	if(lastVATICB.icbTag.flags==3){//Embedded VAT
		VATEmbedded=true;
		lastVAT_len=lastVATICB.lengthAllocDescs;
		totalVATlen+=lastVATICB.lengthAllocDescs;
		lastVAT_addr=lastVATICB_Addr;
		existingVATBlocks=1;
		if(0xb0+lastVAT_len+VATLength<=block_size)		newVATBlocks=0;	/*Use old embedded VAT*/
		else	newVATBlocks=1;/*Add new VAT(s) not embedded*/
	}
	else if(lastVATICB.icbTag.flags==1){
		VATEmbedded=false;
		long_ad* p=(long_ad*)((BYTE*)&lastVATICB+0xb0);
		firstVAT_addr=p->extLocation.logicalBlockNum;
		lastVAT_addr=firstVAT_addr+p->extLength/block_size;
		lastVAT_len=p->extLength;
		totalVATlen+=p->extLength;
		existingVATBlocks=p->extLength/block_size+(p->extLength%block_size?1:0);	
		newVATBlocks=totalVATlen/block_size+(totalVATlen%block_size?1:0);
		/*Add new VAT(s) not embedded*/
	}

	fileID=(totalVATlen-VATLength-0x24)/4;
	Uint32 lastFIDDICBAddr;
	if(VATEmbedded)	lastFIDDICBAddr=*(Uint32*)((BYTE*)&lastVATICB+0xb4);
	else{
		if(SCSIRead(blk,firstVAT_addr+0x223,1,0))	return false;
		lastFIDDICBAddr=*(Uint32*)(blk+4);
	}
	if(!SCSIRead(blk,lastFIDDICBAddr+0x223,1))	return false;
	fileEntry lastFIDDICB=*(fileEntry*)blk;

	
	
	totalFIDDlen=FIDDLength;
	if(lastFIDDICB.icbTag.flags==3){//Embedded FIDD
		FIDDEmbedded=true;
		lastFIDD_len=lastFIDDICB.lengthAllocDescs;
		totalFIDDlen+=lastFIDD_len;
		lastFIDD_addr=lastFIDDICBAddr;
		newFIDDBlocks=0xb0+lastFIDD_len+FIDDLength<block_size?0:	//Use old embedded FIDD
			(int)ceil((double)(lastFIDD_len+FIDDLength)/block_size);//Add new FIDD(s) not embedded
	}
	else if(lastFIDDICB.icbTag.flags==1){
		FIDDEmbedded=false;
		long_ad* p=(long_ad*)((BYTE*)&lastFIDDICB+0xb0);
		while(p->extLength){
			lastFIDD_addr=p->extLocation.logicalBlockNum+p->extLength/block_size;
			lastFIDD_len=p->extLength%block_size;
			totalFIDDlen+=p->extLength;
			p++;
		}
		newFIDDBlocks=(int)ceil((double)(lastFIDD_len+FIDDLength)/block_size);
		//Add new FIDD(s) not embedded
	}

	totalBlocks=totalDataBlocks+list->GetCount()+2+newFIDDBlocks+newVATBlocks;
	BYTE* buffer=new BYTE[block_size*totalBlocks];
		
	if(m_lba+totalBlocks+7>lastLeadOut){
		AfxMessageBox("Disk Full!");
		return false;
	}
	memset(buffer,0,block_size*totalBlocks);
	int offset=0;
	for(j=0;j<filesCount;j++){

		CString name=list->GetAt(list->FindIndex(j));
		CFile file(name,CFile::modeRead);
		int len=file.Read(buffer+offset,file.GetLength());
		offset+=len+(block_size-len%block_size)%block_size;
	}
	int firstNonDataBlock=offset/block_size;
	int firstEntrySector=m_lba+totalDataBlocks-0x223+newFIDDBlocks+newVATBlocks;
	
	//ADD NEW FIDD BLOCKS HERE
	//ECMA167 4/20,4/11
	if(newFIDDBlocks){
		if(FIDDEmbedded){
			//Copy the old part first
			memcpy(buffer+offset,(BYTE*)&lastFIDDICB+0xb0,lastFIDD_len);
			//Write the new part		
			fileIdentDesc	FIDD;
			memset(&FIDD,0,sizeof(fileIdentDesc));
			for(int j=0;j<filesCount;j++){
				CString name=list->GetAt(list->FindIndex(j));
				if(name.ReverseFind('\\')>=0)	name=name.Mid(name.ReverseFind('\\')+1);
				int len=39+2*name.GetLength();
				char* uniname=(char*)((BYTE*)&FIDD+38);
				memset(uniname,0,2*name.GetLength()+1);
				uniname[0]=0x10;
				for(int i=0;i<name.GetLength();i++)
					uniname[2*(i+1)]=name[i];
				FIDD.fileVersionNum=1;
				FIDD.fileCharacteristics=0;
				FIDD.lengthFileIdent=2*name.GetLength()+1;
				FIDD.icb.extLength=0x800;
				FIDD.icb.extLocation.logicalBlockNum=(Uint32)fileID+j;
				FIDD.icb.extLocation.partitionReferenceNum=1;//Virtual
				FIDD.descTag=fillTag(TAG_IDENT_FID,(BYTE*)&FIDD+0x10,len+(4-len%4)%4-0x10,
					m_lba+offset/block_size-0x223);//Need to change tagLoc at different blocks
				memcpy(buffer+offset+lastFIDD_len,(BYTE*)&FIDD,len+(4-len%4)%4);
				offset+=len+(4-len%4)%4;
			}	
		}
		else{
			//Copy the old part first
			if(!SCSIRead(buffer+offset,lastFIDD_addr+0x223,1))	return false;
			//Write the new part
			fileIdentDesc	FIDD;
			memset(&FIDD,0,sizeof(fileIdentDesc));
			for(int j=0;j<filesCount;j++){
				CString name=list->GetAt(list->FindIndex(j));
				if(name.ReverseFind('\\')>=0)	name=name.Mid(name.ReverseFind('\\')+1);
				int len=39+2*name.GetLength();
				char* uniname=(char*)((BYTE*)&FIDD+38);
				memset(uniname,0,2*name.GetLength()+1);
				uniname[0]=0x10;
				for(int i=0;i<name.GetLength();i++)
					uniname[2*(i+1)]=name[i];
				FIDD.fileVersionNum=1;
				FIDD.fileCharacteristics=0;
				FIDD.lengthFileIdent=2*name.GetLength()+1;
				FIDD.icb.extLength=0x800;
				FIDD.icb.extLocation.logicalBlockNum=(Uint32)fileID+j;
				FIDD.icb.extLocation.partitionReferenceNum=1;//Virtual
				FIDD.descTag=fillTag(TAG_IDENT_FID,(BYTE*)&FIDD+0x10,len+(4-len%4)%4-0x10,
					m_lba+offset/block_size-0x223);//Need to change tagLoc at different blocks
				memcpy(buffer+offset+lastFIDD_len,(BYTE*)&FIDD,len+(4-len%4)%4);
				offset+=len+(4-len%4)%4;
			}	
		}
	}

	offset+=(block_size-offset%block_size)%block_size;
	
	//ADD NEW VAT BLOCKS HERE
	//UNIVERSAL DISK FORMAT SPECIFICATIN Rev2.01 P33
	if(newVATBlocks){
		if(VATEmbedded){
			memcpy(buffer+offset,(BYTE*)&lastVATICB+0xb0,lastVAT_len);
		}
		else{
			if(SCSIRead(buffer+offset,firstVAT_addr+0x223,existingVATBlocks,0))	
				return false;	
		}
		//MODIFY ROOT FILEENTRY VA FIRST
		*(Uint32*)(buffer+offset+4)=firstEntrySector;
		offset+=lastVAT_len-0x24;
		memset(buffer+offset,0,existingVATBlocks*block_size-lastVAT_len);
		//Write the new part		
		*(Uint32*)(buffer+offset)=firstEntrySector+1;
		id=(regid*)(buffer+offset+4);
		id->flags=0;
		memcpy(id->identSuffix,idSuffix,3);
		char* str=UDF_ID_ALLOC;
		for(BYTE i=0;i<strlen(str);i++)		id->ident[i]=str[i];
		offset+=VATLength+0x24;
	}

	offset+=(block_size-offset%block_size)%block_size;

	//WRITE THE FIDD ICB or FIDD(EMBEDDED)
	//ECMA167 4/20,4/11
	fileEntry	FE;
	memset(&FE,0,sizeof(fileEntry));
	FE.icbTag.strategyType=4;
	FE.icbTag.numEntries=1;
	FE.icbTag.fileType=4;
	FE.uid=0xffffffff;
	FE.gid=0xffffffff;
	FE.permissions=0x7fff;
	FE.fileLinkCount=1;
	FE.modificationTime=t;
	FE.uniqueID=lastFIDDICB.uniqueID;
	FE.impIdent.flags=0;
	for(BYTE i=0;i<strlen(impId);i++)		FE.impIdent.ident[i]=impId[i];
	FE.impIdent.identSuffix[0]=6;
	FE.impIdent.identSuffix[6]=5;
	FE.informationLength=totalFIDDlen;

	if(FIDDEmbedded&&newFIDDBlocks==0)
	{//USE THE OLD EMBEDDED FIDD
		FE.icbTag.flags=0x3;
		FE.lengthAllocDescs=(Uint32)totalFIDDlen;
	
		int FIDD_Offset=0xB0;
		//COPY THE OLD PART FIRST
		memcpy((BYTE*)&FE+FIDD_Offset,(BYTE*)&lastFIDDICB+FIDD_Offset,lastFIDD_len);
		FIDD_Offset+=lastFIDD_len;

		fileIdentDesc	FIDD;
		memset(&FIDD,0,sizeof(fileIdentDesc));
		for(int j=0;j<filesCount;j++){
			//ADD NEW ENTRY FOR EACH NEW FILE
			CString name=list->GetAt(list->FindIndex(j));
			if(name.ReverseFind('\\')>=0)	name=name.Mid(name.ReverseFind('\\')+1);
			int len=40+2*name.GetLength();
			char* uniname=(char*)((BYTE*)&FIDD+38);
			memset(uniname,0,2*name.GetLength()+1);
			uniname[0]=0x10;
			for(int i=0;i<name.GetLength();i++)
				uniname[2*(i+1)]=name[i];
			FIDD.fileVersionNum=1;
			FIDD.fileCharacteristics=0;
			FIDD.lengthFileIdent=2*name.GetLength()+1;
			FIDD.icb.extLength=0x800;
			FIDD.icb.extLocation.logicalBlockNum=(Uint32)fileID+j;
			FIDD.icb.extLocation.partitionReferenceNum=1;
			FIDD.descTag=fillTag(TAG_IDENT_FID,(BYTE*)&FIDD+0x10,len+(4-len%4)%4-0x10,1);
			memcpy((BYTE*)&FE+FIDD_Offset,(BYTE*)&FIDD,len+(4-len%4)%4);
			FIDD_Offset+=len+(4-len%4)%4;
		}	
		FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0xa0+lastFIDD_len+FIDDLength,1);
	}
	else if(FIDDEmbedded){
		//THE FIDD IS NO LONGER EMBEDDED,THE FIDD ICB HAS TO BE REWRITTEN HERE
		//THE FIDD ITSELF IS ALREADY WRITTEN AT THE BEGINNING OF THIS FUNCTION
		FE.icbTag.flags=0x1;
		FE.lengthAllocDescs=0x750;
		long_ad* p=(long_ad*)((BYTE*)&FE+0xb0);
		p->extLength=(Uint32)(FIDDLength+lastFIDD_len);
		p->extLocation.logicalBlockNum=m_lba-0x223+totalDataBlocks;
		p->extLocation.partitionReferenceNum=0;	//Physical Partition
		
		FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0x7f0,1);
	}
	else{
		memcpy(&FE,&lastFIDDICB,block_size);
		FE.informationLength=totalFIDDlen;
		long_ad* p=(long_ad*)((BYTE*)&FE+0xb0);
		while(p->extLength) p++;
		p--;//Last FIDD must be rewritten
		if(p->extLength>0x800){
			p->extLength-=p->extLength%block_size;
			p++;
		}
		p->extLength=(Uint32)(FIDDLength+lastFIDD_len);
		p->extLocation.logicalBlockNum=m_lba-0x223+totalDataBlocks;
		p->extLocation.partitionReferenceNum=0;	//Physical Partition
		
		FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0x7f0,1);
	}

	*(fileEntry*)(buffer+offset)=FE;
	offset+=block_size;

	memset(&FE,0,sizeof(fileEntry));
	FE.icbTag.strategyType=4;
	FE.icbTag.numEntries=1;
	FE.icbTag.fileType=5;
	FE.icbTag.flags=0x1;
	FE.uid=0xffffffff;
	FE.gid=0xffffffff;
	FE.permissions=0x7BDE;
	FE.fileLinkCount=1;
	FE.modificationTime=t;
	for(i=0;i<strlen(impId);i++)		FE.impIdent.ident[i]=impId[i];
	FE.impIdent.identSuffix[0]=6;
	FE.impIdent.identSuffix[6]=5;
	FE.uniqueID=UniqueID++;
	FE.lengthExtendedAttr=0x5c;
	FE.lengthAllocDescs=0x6f0;
	
	Uint32 fileLocation=m_lba-0x223;
	for(j=0;j<filesCount;j++){
		//ADD ONE FILE ENTRY FOR EACH FILE
		//ECMA-167 4/28
		CString name=list->GetAt(list->FindIndex(j));
		CFile file(name,CFile::modeRead);
		int len=file.GetLength();
		int blocks=(int)ceil(len/(double)block_size);
		FE.informationLength=len;
		FE.logicalBlocksRecorded=blocks;
		FE.uniqueID=UniqueID++;
		BYTE* other=&FE.other[0];
		*(Uint32*)(other+0x10)=0xffffffff;
		*(Uint32*)(other+0x14)=0xffffffff;
		fileTimesExtAttr* FTEA=(fileTimesExtAttr*)(other+0x18);
		FTEA->attrType=5;
		FTEA->attrSubtype=1;
		FTEA->attrLength=0x5c;
		FTEA->dataLength=0x0c;
		FTEA->fileTimeExistence=1;
		FTEA->fileTimes=t;
		short_ad* ad=(short_ad*)(other+0x5c);
		ad->extLength=len;
		ad->extPosition=fileLocation;
		fileLocation+=blocks;
		*(tag*)other=fillTag(0x106,(BYTE*)other+0xc0,0x4c,j+2);
		FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0x7ec,(Uint32)fileID+j);
		*(fileEntry*)(buffer+offset)=FE;
		offset+=block_size;
	}
	
	//VAT ICB or VAT(EMBEDDED)
	//UNIVERSAL DISK FORMAT SPECIFICATIN Rev2.01 P33
	memset(&FE,0,sizeof(fileEntry));
	FE.icbTag.strategyType=4;
	FE.icbTag.numEntries=1;
	FE.uid=0xffffffff;
	FE.gid=0xffffffff;
	FE.permissions=0x7fff;
	FE.modificationTime=t;
	for(i=0;i<strlen(impId);i++)		FE.impIdent.ident[i]=impId[i];
	FE.impIdent.identSuffix[0]=6;
	FE.impIdent.identSuffix[6]=5;
	FE.uniqueID=UniqueID++;
	FE.informationLength=totalVATlen;
	
	if(VATEmbedded&&newVATBlocks==0)
	{
		//USE OLD EMBEDDED VAT
		FE.icbTag.flags=0x3;
		FE.lengthAllocDescs=(Uint32)totalVATlen;
		//COPY THE OLD VAT
		memcpy((BYTE*)&FE+0xb0,(BYTE*)&lastVATICB+0xb0,lastVATICB.lengthAllocDescs-0x24);
		//MODIFY THE ROOT FILE ENTRY OF VAT TO NEW FIDD ADDRESS
		*(Uint32*)((BYTE*)&FE+0xB4)=firstEntrySector;
		//ADD NEW ENTRIES FOR THE EMBEDDED VAT
		BYTE* newVATEntryAddr=(BYTE*)&FE+0xB0+lastVATICB.lengthAllocDescs-0x24;
		for(i=0;i<filesCount;i++){
			//Add one entry for each file
			*(Uint32*)(newVATEntryAddr+i*4)=firstEntrySector+1+i;
		}
		
		//OTHER STUFF TO FILL
		regid* id=(regid*)(newVATEntryAddr+4*filesCount);
		id->flags=0;
		id->identSuffix[0]=0x50;
		id->identSuffix[1]=0x01;
		id->identSuffix[2]=0x06;
		char* str=UDF_ID_ALLOC;
		for(i=0;i<strlen(str);i++)		id->ident[i]=str[i];

		*(Uint32*)(newVATEntryAddr+4*filesCount+0x20)=lastVATICB_Addr-0x223;
		FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0xa0+lastVATICB.lengthAllocDescs+4*filesCount,
			firstEntrySector+1+filesCount);
		
	}
	else if(VATEmbedded){
		//THE VAT IS NO LONGER EMBEDDED,THE VAT ICB HAS TO BE REWRITTEN HERE
		//THE VAT ITSELF IS ALREADY WRITTEN AT THE BEGINNING OF THIS FUNCTION
		FE.icbTag.flags=0x1;
		FE.lengthAllocDescs=0x750;
		//LOCATION OF THE VAT
		long_ad* p=(long_ad*)((BYTE*)&FE+0xb0);
		p->extLength=(Uint32)(VATLength+lastVAT_len);
		p->extLocation.logicalBlockNum=m_lba-0x223+totalDataBlocks+newFIDDBlocks;
		p->extLocation.partitionReferenceNum=0;	//Physical Partition
		
		FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0x7f0,firstEntrySector+1+filesCount);
	}
	else{
		//ONLY NEED TO CHANGE THE LAST VAT ENTRY IN THE VAT ICB
		memcpy(&FE,&lastFIDDICB,block_size);
		FE.informationLength=totalVATlen;
		long_ad* p=(long_ad*)((BYTE*)&FE+0xb0);
		while(p->extLength) p++;
		p--;//Last VAT must be rewritten
		if(p->extLength>0x800){
			p->extLength-=p->extLength%block_size;
			p++;
		}
		p->extLength=(Uint32)(VATLength+lastVAT_len);
		p->extLocation.logicalBlockNum=m_lba-0x223+totalDataBlocks+newFIDDBlocks;
		p->extLocation.partitionReferenceNum=0;	//Physical Partition
		
		FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0x7f0,firstEntrySector+1+filesCount);
	}
	*(fileEntry*)(buffer+offset)=FE;

	if(!SetWriteParameters(0,10,5,0x20))		return false;
	bool result=WritePacket(buffer,m_lba,totalBlocks);
	delete buffer;
	delete list;
	return result;
}

//--------------------------------------------------------------------------
bool SCSI2::WritePacket(long len) {
	BYTE* buffer=new BYTE[block_size*len];
	memset(buffer,0,block_size*len);
	bool res= WritePacket (buffer,m_lba,len);
	delete buffer;
	return res;
}
//--------------------------------------------------------------------------
bool SCSI2::WritePacket (unsigned char* buffer,long len) {
	return WritePacket (buffer,m_lba,len);
}
//--------------------------------------------------------------------------
bool SCSI2::WritePacket (unsigned char* buffer,long addr,long len,bool packet) {

	while(TestUnitReady());
	
	m_lba=addr;
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
		
	for(int i=0;len-i*0x10>0;i++){
		int thisLen=len-i*0x10<0x10?len-i*0x10:0x10;
		memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
		srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
		srbExec.SRB_HaId = m_HA;
		srbExec.SRB_Target = m_ID;
		srbExec.SRB_Lun = m_LUN;
		srbExec.SRB_Flags = SRB_DIR_OUT;
		srbExec.SRB_BufLen = block_size*thisLen;
		srbExec.SRB_BufPointer = buffer+i*0x10*block_size;
		srbExec.SRB_SenseLen = SENSE_LEN;
		srbExec.SRB_CDBLen = 10;
		srbExec.CDBByte [ 0 ] = SCSI_WRITE10;
		srbExec.CDBByte [ 1 ] = 0x00;	//0x08=FUA
		srbExec.CDBByte [ 2 ] = (m_lba>>24)&0xff;
		srbExec.CDBByte [ 3 ] = (m_lba>>16)&0xff;
		srbExec.CDBByte [ 4 ] = (m_lba>>8)&0xff;
		srbExec.CDBByte [ 5 ] =  m_lba&0xff;
		srbExec.CDBByte [ 7 ] = (thisLen>>8)&0xff;
		srbExec.CDBByte [ 8 ] = thisLen&0xff;

		pfnSendASPI32Command ( ( LPSRB ) &srbExec );
		while ( srbExec.SRB_Status == SS_PENDING );
		if(checkError(srbExec.SRB_Status)!="SUCCESS"&&!m_silence){
			m_sense=*(scsi_sense *)srbExec.SenseArea;
			AfxMessageBox(checkSense());
			break;
		}
		if(srbExec.SRB_Status == SS_COMP)	m_lba+=thisLen;
	}

	if(srbExec.SRB_Status == SS_COMP&&packet){

		m_lba+=7;
		srbExec.SRB_BufLen = 0;
		srbExec.SRB_BufPointer=0;
		srbExec.CDBByte [ 2 ] = (m_lba>>24)&0xff;
		srbExec.CDBByte [ 3 ] = (m_lba>>16)&0xff;
		srbExec.CDBByte [ 4 ] = (m_lba>>8)&0xff;
		srbExec.CDBByte [ 5 ] =  m_lba&0xff;
		srbExec.CDBByte [ 7 ] = 0;
		srbExec.CDBByte [ 8 ] = 0;
		pfnSendASPI32Command ( ( LPSRB ) &srbExec );
		while ( srbExec.SRB_Status == SS_PENDING );
		if(checkError(srbExec.SRB_Status)!="SUCCESS"&&!m_silence){
			m_sense=*(scsi_sense *)srbExec.SenseArea;
			AfxMessageBox(checkSense());
		}
	}

	return srbExec.SRB_Status == SS_COMP;

}
//--------------------------------------------------------------------------

bool SCSI2::ReserveTrack(int size){	
	
	BYTE *buffer=new BYTE[block_size];
	memset(buffer,0,block_size);
	
	while(TestUnitReady());
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_BufLen = block_size;
	srbExec.SRB_BufPointer = buffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x53;	//Reserve Track
	srbExec.CDBByte [ 7 ] = (size>>8)&0xff;
	srbExec.CDBByte [ 8 ] = size&0xff;
	
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );
	if(checkError(srbExec.SRB_Status)!="SUCCESS"&&!m_silence){
		m_sense=*(scsi_sense *)srbExec.SenseArea;
		AfxMessageBox(checkSense());
	}
	delete buffer;
	return srbExec.SRB_Status == SS_COMP;
}
//--------------------------------------------------------------------------
bool SCSI2::FormatDisc (const char* label) {

	//Set write mode to TAO
	if(!SetWriteParameters(1,10,4,0x20))	return false;
	//Reserve Track of length 0x168, which will be used
	//closing the session
	if(!ReserveTrack(0x168))				return false;
	//Set write mode back to variable packet
	if(!SetWriteParameters(0,10,5,0x20))	return false;

	int HEADER_SIZE=0x26;
	int FIRST_VRS=0x201;
	int SECOND_VRS=0x211;
	BYTE *buffer=new BYTE[block_size*HEADER_SIZE];
	
	char* str;
	char* impId="*Adaptec DirectCD";	
	char* volID=new char[32];
	memset(volID,0,32);
	volID[0]=0x10;	//16bits per character
	for(BYTE i=0;i<strlen(label);i++)	volID[2*(i+1)]=label[i];	//Unicode
	
	memset(buffer,0,block_size*HEADER_SIZE);
	anchorVolDescPtr AVDP;
	memset(&AVDP,0,sizeof(anchorVolDescPtr));
	AVDP.mainVolDescSeqExt.extLocation=FIRST_VRS;
	AVDP.mainVolDescSeqExt.extLength=0x8000;
	AVDP.reserveVolDescSeqExt.extLocation=SECOND_VRS;
	AVDP.reserveVolDescSeqExt.extLength=0x8000;
	AVDP.descTag=fillTag(TAG_IDENT_AVDP,(BYTE*)&AVDP+0x10,0x1f0,0x200);
	*(anchorVolDescPtr*)buffer=AVDP;
	
	timestamp	t;
	time_t	timenow;
	time( &timenow );
	udf_time_to_stamp(&t, timenow, 0);
	
	int offset=block_size;
	for(int repeat=0;repeat<2;repeat++){
		int base=repeat?SECOND_VRS:FIRST_VRS;
		offset=repeat?0x11*block_size:block_size;
		//Write PVD
		primaryVolDesc PVD;
		memset(&PVD,0,sizeof(primaryVolDesc));
		PVD.volDescSeqNum=1;
		for(i=0;i<32;i++)		PVD.volIdent[i]=volID[i];
		PVD.volIdent[31]=2*strlen(label)+1;	//Length of dstring
		PVD.volSeqNum=1;
		PVD.maxVolSeqNum=1;
		PVD.interchangeLvl=2;
		PVD.maxInterchangeLvl=3;
		PVD.charSetList=1;
		PVD.maxCharSetList=1;
		PVD.volSetIdent[0]=0x08;
		PVD.volSetIdent[1]='0';
		PVD.volSetIdent[2]='C';
		PVD.volSetIdent[3]='F';
		PVD.volSetIdent[4]='E';
		PVD.volSetIdent[5]='9';
		PVD.volSetIdent[6]='0';
		PVD.volSetIdent[7]='C';
		PVD.volSetIdent[8]='B';
		PVD.volSetIdent[127]=0x09;	//Length of dstring
		PVD.descCharSet.charSetType=UDF_CHAR_SET_TYPE;
		PVD.explanatoryCharSet.charSetType=UDF_CHAR_SET_TYPE;
		str=UDF_CHAR_SET_INFO;
		for(i=0;i<strlen(str);i++){
			PVD.descCharSet.charSetInfo[i]=str[i];
			PVD.explanatoryCharSet.charSetInfo[i]=str[i];
		}
		
		PVD.recordingDateAndTime=t;
		PVD.impIdent.flags=0;
		for(i=0;i<strlen(impId);i++)		PVD.impIdent.ident[i]=impId[i];
		PVD.impIdent.identSuffix[0]=6;
		PVD.impIdent.identSuffix[6]=5;
	
		PVD.descTag=fillTag(TAG_IDENT_PVD,(BYTE*)&PVD+0x10,0x1f0,base);
		*(primaryVolDesc*)(buffer+offset)=PVD;
		

		//Write LVD
		logicalVolDesc LVD;
		memset(&LVD,0,sizeof(logicalVolDesc));
		LVD.volDescSeqNum=2;
		LVD.descCharSet.charSetType=0;
		str=UDF_CHAR_SET_INFO;
		for(i=0;i<strlen(str);i++)		LVD.descCharSet.charSetInfo[i]=str[i];
		for(i=0;i<32;i++)		LVD.logicalVolIdent[i]=volID[i];
		LVD.logicalVolIdent[127]=2*strlen(label)+1;	//Length of dstring
		LVD.logicalBlockSize=block_size;
		LVD.domainIdent.flags=0;
		str=UDF_ID_COMPLIANT;
		for(i=0;i<strlen(str);i++)		LVD.domainIdent.ident[i]=str[i];
		LVD.domainIdent.identSuffix[0]=0x50;
		LVD.domainIdent.identSuffix[1]=0x01;
		LVD.logicalVolContentsUse.extLength=block_size;
		LVD.logicalVolContentsUse.extLocation.logicalBlockNum=0;
		LVD.logicalVolContentsUse.extLocation.partitionReferenceNum=1;
		LVD.mapTableLength=0x46;
		LVD.numPartitionMaps=2;
		LVD.impIdent.flags=0;
		for(i=0;i<strlen(impId);i++)		LVD.impIdent.ident[i]=impId[i];
		LVD.impIdent.identSuffix[0]=6;
		LVD.impIdent.identSuffix[6]=5;
		LVD.integritySeqExt.extLength=2*block_size;
		LVD.integritySeqExt.extLocation=0x221;
		LVD.partitionMap1.type=1;
		LVD.partitionMap1.len=6;
		LVD.partitionMap1.volSeqNumber=1;
		LVD.partitionMap1.partitionNumber=0;
		LVD.partitionMap2.type=2;
		LVD.partitionMap2.len=0x40;
		LVD.partitionMap2.ident.flags=0;
		str=UDF_ID_VIRTUAL;
		for(i=0;i<strlen(str);i++)		LVD.partitionMap2.ident.ident[i]=str[i];
		LVD.partitionMap2.ident.identSuffix[0]=0x50;
		LVD.partitionMap2.ident.identSuffix[1]=0x01;
		LVD.partitionMap2.ident.identSuffix[2]=0x06;
		LVD.partitionMap2.volSeqNumber=1;
		LVD.partitionMap2.partitionNumber=0;
		LVD.partitionMap2.reserved[0]=1;
		LVD.descTag=fillTag(TAG_IDENT_LVD,(BYTE*)&LVD+0x10,0x1EE,base+1);
		*(logicalVolDesc*)(buffer+offset+block_size)=LVD;


		//Write PD
		partitionDesc PD;
		memset(&PD,0,sizeof(partitionDesc));
		PD.volDescSeqNum=3;
		PD.partitionFlags=1;
		PD.partitionNumber=0;
		PD.partitionContents.flags=0;
		char* temp="+NSR02";
		for(i=0;i<6;i++)		PD.partitionContents.ident[i]=temp[i];
		PD.partitionContents.identSuffix[0]=0x50;
		PD.partitionContents.identSuffix[1]=0x01;
		PD.partitionContents.identSuffix[2]=0x06;
		PD.accessType=2;	//Write-Once
		PD.partitionStartingLocation=0x223;
		PD.partitionLength=0x511a4;
		PD.impIdent.flags=0;
		for(i=0;i<strlen(impId);i++)		PD.impIdent.ident[i]=impId[i];
		PD.impIdent.identSuffix[0]=6;
		PD.impIdent.identSuffix[6]=5;
		PD.descTag=fillTag(TAG_IDENT_PD,(BYTE*)&PD+0x10,0x1f0,base+2);
		*(partitionDesc*)(buffer+offset+2*block_size)=PD;

		//Write USD
		unallocSpaceDesc USD;
		memset(&USD,0,sizeof(unallocSpaceDesc));
		USD.volDescSeqNum=4;
		USD.numAllocDescs=0;
		USD.descTag=fillTag(TAG_IDENT_USD,(BYTE*)&USD+0x10,0x08,base+3);
		*(unallocSpaceDesc*)(buffer+offset+3*block_size)=USD;
		
		//Write IUVD
		impUseVolDesc IUVD;
		memset(&IUVD,0,sizeof(impUseVolDesc));
		IUVD.volDescSeqNum=5;
		IUVD.impIdent.flags=0;
		str=UDF_ID_LV_INFO;
		for(i=0;i<strlen(str);i++)		IUVD.impIdent.ident[i]=str[i];
		IUVD.impIdent.identSuffix[0]=0x50;
		IUVD.impIdent.identSuffix[1]=0x01;
		IUVD.impIdent.identSuffix[2]=0x06;
		IUVD.impUse.LVICharSet.charSetType=0;
		str=UDF_CHAR_SET_INFO;
		for(i=0;i<strlen(str);i++)		IUVD.impUse.LVICharSet.charSetInfo[i]=str[i];
		for(i=0;i<32;i++)				IUVD.impUse.LVId[i]=volID[i];
		IUVD.impUse.LVId[127]=2*strlen(label)+1;
		IUVD.impUse.impIdent.flags=0;
		for(i=0;i<strlen(impId);i++)		IUVD.impUse.impIdent.ident[i]=impId[i];
		IUVD.impUse.impIdent.identSuffix[0]=0x06;
		IUVD.impUse.impIdent.identSuffix[6]=0x05;
		IUVD.descTag=fillTag(TAG_IDENT_IUVD,(BYTE*)&IUVD+0x10,0x1f0,base+4);
		*(impUseVolDesc*)(buffer+offset+4*block_size)=IUVD;
		
		//Write TD
		terminatingDesc TD;
		memset(&TD,0,sizeof(terminatingDesc));
		TD.descTag=fillTag(TAG_IDENT_TD,(BYTE*)&TD+0x10,0x1f0,base+5);
		*(terminatingDesc*)(buffer+offset+5*block_size)=TD;
	}

	//Write LVID
	logicalVolIntegrityDesc LVID;
	memset(&LVID,0,sizeof(logicalVolIntegrityDesc));
	LVID.recordingDateAndTime=t;
	LVID.integrityType=0;	//Open
	LVID.numOfPartitions=2;
	LVID.lengthOfImpUse=0x30;
	Uint32* p=&LVID.freeSpaceTable[0];
	*(p++)=0x511a4-0x12;	//?
	*(p++)=0xffffffff;
	*(p++)=0x511a4;//?
	*(p++)=0xffffffff;
	logicalVolIntegrityDescImpUse* impUse=
		(logicalVolIntegrityDescImpUse*)&LVID.impUse;
	impUse->impIdent.flags=0;
	for(i=0;i<strlen(impId);i++)		impUse->impIdent.ident[i]=impId[i];
	impUse->impIdent.identSuffix[0]=0x06;
	impUse->impIdent.identSuffix[6]=0x05;
	impUse->minUDFReadRev=0x150;
	impUse->minUDFWriteRev=0x150;
	impUse->maxUDFWriteRev=0x150;
	LVID.descTag=fillTag(TAG_IDENT_LVID,(BYTE*)&LVID+0x10,0x80,0x221);
	*(logicalVolIntegrityDesc*)(buffer+block_size*0x21)=LVID;

	terminatingDesc	TD;
	memset(&TD,0,sizeof(terminatingDesc));
	TD.descTag=fillTag(TAG_IDENT_TD,(BYTE*)&TD+0x10,0x1f0,0x222);
	*(terminatingDesc*)(buffer+block_size*0x22)=TD;

	//Write FSD
	fileSetDesc	FSD;
	memset(&FSD,0,sizeof(fileSetDesc));
	FSD.recordingDateAndTime=t;
	FSD.interchangeLvl=3;
	FSD.maxInterchangeLvl=3;
	FSD.charSetList=1;
	FSD.maxCharSetList=1;
	FSD.fileSetNum=0;
	FSD.fileSetDescNum=0;
	FSD.logicalVolIdentCharSet.charSetType=0;
	str=UDF_CHAR_SET_INFO;
	for(i=0;i<strlen(str);i++){
		FSD.logicalVolIdentCharSet.charSetInfo[i]=str[i];
	}
	
	for(i=0;i<32;i++)		FSD.logicalVolIdent[i]=volID[i];
	FSD.logicalVolIdent[127]=2*strlen(label)+1;

	FSD.fileSetCharSet.charSetType=0;
	for(i=0;i<strlen(str);i++){
		FSD.fileSetCharSet.charSetInfo[i]=str[i];
	}
	for(i=0;i<32;i++)		FSD.fileSetIdent[i]=volID[i];
	FSD.fileSetIdent[31]=2*strlen(label)+1;

	FSD.rootDirectoryICB.extLength=0x800;
	FSD.rootDirectoryICB.extLocation.logicalBlockNum=1;
	FSD.rootDirectoryICB.extLocation.partitionReferenceNum=1;
	FSD.domainIdent.flags=0;
	str=UDF_ID_COMPLIANT;
	for(i=0;i<strlen(str);i++)	FSD.domainIdent.ident[i]=str[i];
	FSD.domainIdent.identSuffix[0]=0x50;
	FSD.domainIdent.identSuffix[1]=0x01;
	FSD.descTag=fillTag(TAG_IDENT_FSD,(BYTE*)&FSD+0x10,0x1f0,0);
	*(fileSetDesc*)(buffer+block_size*0x23)=FSD;
	
	//FIDD
	fileEntry	FE;
	memset(&FE,0,sizeof(fileEntry));
	FE.icbTag.strategyType=4;
	FE.icbTag.numEntries=1;
	FE.icbTag.fileType=4;
	FE.icbTag.flags=0x3;
	FE.uid=0xffffffff;
	FE.gid=0xffffffff;
	FE.permissions=0x7fff;
	FE.fileLinkCount=1;
	FE.informationLength=0x28;
	FE.modificationTime=t;
	FE.impIdent.flags=0;
	for(i=0;i<strlen(impId);i++)		FE.impIdent.ident[i]=impId[i];
	FE.impIdent.identSuffix[0]=0x06;
	FE.impIdent.identSuffix[6]=0x05;
	FE.uniqueID=0x11;
	FE.lengthAllocDescs=0x28;
	{//Fill in the Embedded FIDD
		int FIDD_Offset=0xB0;
		fileIdentDesc	FIDD;
		memset(&FIDD,0,sizeof(fileIdentDesc));
		FIDD.fileVersionNum=1;
		FIDD.fileCharacteristics=0xA;
		FIDD.icb.extLength=0x800;
		FIDD.icb.extLocation.logicalBlockNum=1;
		FIDD.icb.extLocation.partitionReferenceNum=1;
		FIDD.descTag=fillTag(TAG_IDENT_FID,(BYTE*)&FIDD+0x10,0x18,1);
		*(fileIdentDesc*)((BYTE*)&FE+FIDD_Offset)=FIDD;
	}

	FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0xC8,1);
	*(fileEntry*)(buffer+block_size*0x24)=FE;
	
	//VAT ICB
	FE.icbTag.fileType=0;	
	FE.permissions=0x7fff;
	FE.fileLinkCount=0;
	FE.uniqueID=0x12;
	FE.informationLength=0x2c;
	FE.logicalBlocksRecorded=0;
	FE.lengthAllocDescs=0x2c;
	FE.lengthExtendedAttr=0;
	*(Uint32*)((BYTE*)&FE+0xB0)=0;
	*(Uint32*)((BYTE*)&FE+0xB4)=1;
	regid* id=(regid*)((BYTE*)&FE+0xB8);
	str=UDF_ID_ALLOC;
	id->flags=0;
	for(i=0;i<strlen(str);i++)		id->ident[i]=str[i];
	id->identSuffix[0]=0x50;
	id->identSuffix[1]=0x01;
	id->identSuffix[2]=0x06;
	*(Uint32*)((BYTE*)&FE+0xD8)=0xffffffff;
	FE.descTag=fillTag(TAG_IDENT_FE,(BYTE*)&FE+0x10,0xCC,2);
	*(fileEntry*)(buffer+block_size*0x25)=FE;

	//Write the buffer to the disk
	bool result=WritePacket(buffer,0x200,0x26);
	delete volID;
	delete buffer;
	return result;
}
//--------------------------------------------------------------------------
bool SCSI2::SCSIRead ( unsigned char* buffer,long addr,long size,bool header) {

	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_BufLen = size*2448;
	srbExec.SRB_BufPointer = buffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 12;
	srbExec.CDBByte [ 0 ] = 0xbe;
	srbExec.CDBByte [ 2 ] = (addr>>24)&0xff;
	srbExec.CDBByte [ 3 ] = (addr>>16)&0xff;
	srbExec.CDBByte [ 4 ] = (addr>>8)&0xff;
	srbExec.CDBByte [ 5 ] = addr&0xff;
	srbExec.CDBByte [ 6 ] = (size>>16)&0xff;
	srbExec.CDBByte [ 7 ] = (size>>8)&0xff;
	srbExec.CDBByte [ 8 ] = size&0xff;
	srbExec.CDBByte [ 9 ] = header?0x70:0x10;
	
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );
	if(checkError(srbExec.SRB_Status)!="SUCCESS"&&!m_silence){
		m_sense=*(scsi_sense *)srbExec.SenseArea;
		AfxMessageBox(checkSense());
	}
	return srbExec.SRB_Status == SS_COMP;

}
//--------------------------------------------------------------------------
CString SCSI2::SCSICDROMCapacity () {

	CString szReturnString;
	unsigned char szBuffer[40];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = SCSI_READCDCAP;
	
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );

	if ( srbExec.SRB_Status != SS_COMP )
		szReturnString="Inquiry error.";
	else{
		char s[80];
		sprintf(s,"Blocks:\t%d",(szBuffer[0]<<24)+(szBuffer[1]<<16)+(szBuffer[2]<<8)+szBuffer[3]+1);
		szReturnString=s;
		sprintf(s,"\nBlock length :\t%d",(szBuffer[4]<<24)+(szBuffer[5]<<16)+(szBuffer[6]<<8)+szBuffer[7]);
		szReturnString+=s;
	}
	return szReturnString;
}
//--------------------------------------------------------------------------
CString SCSI2::SCSICDRScan ( ) {

	CString szReturnString;
	unsigned char szBuffer[40];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = SENSE_LEN;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = SCSI_MEDIUM_SCN;
	srbExec.CDBByte [ 8 ] = 8;
	srbExec.CDBByte [ 9 ] = 1;
	srbExec.CDBByte [ 13] = 1;
	srbExec.CDBByte [ 14] = 1;
	srbExec.SenseArea[3]=1;
	srbExec.SenseArea[4]=1;

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	
	while ( srbExec.SRB_Status == SS_PENDING );
	if(srbExec.SRB_Status&STATUS_CONDMET){
		//memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
		srbExec.SRB_CDBLen = 6;
		srbExec.CDBByte [ 0 ] = SCSI_REQ_SENSE;
		srbExec.CDBByte [ 4 ] = 18;
		pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	}

	if ( srbExec.SRB_Status != SS_COMP|| szBuffer[0]==0x70||szBuffer[0]==0x71)
		szReturnString="Medium scan error.";
	else{
		char s[80];
		sprintf(s,"Block:\t%d",(szBuffer[0]<<24)+(szBuffer[1]<<16)+(szBuffer[2]<<8)+szBuffer[3]);
		szReturnString=s;
		//sprintf(s,"\nBlock length :\t%d",(szBuffer[4]<<24)+(szBuffer[5]<<16)+(szBuffer[6]<<8)+szBuffer[7]);
		//szReturnString+=s;
	}
	return szReturnString;
}
//--------------------------------------------------------------------------
CString SCSI2::SCSICapabilities () {

	CString szReturnString;
	unsigned char szBuffer[100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 18;
	srbExec.SRB_CDBLen = 6;
	srbExec.CDBByte [ 0 ] = SCSI_MODE_SEN6;
	srbExec.CDBByte [ 1 ] = 0x08;
	srbExec.CDBByte [ 2 ] = 0x2A;
	srbExec.CDBByte [ 4 ] = 100;

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );

	if ( srbExec.SRB_Status != SS_COMP )
		szReturnString="Mode Sense error.";
	else{
		cd_mode_page_2A *p=(cd_mode_page_2A *)(szBuffer+4);
		//BYTE* page=szBuffer+4;
		if(p->cd_r_write)
			szReturnString="CDR Writing:Yes\n";
		else
			szReturnString="CDR Writing:No\n";
		if(p->cd_rw_write)
			szReturnString+="CDRW Writing:Yes\n";
		else
			szReturnString+="CDRW Writing:No\n";
		if(p->multi_session)
			szReturnString+="Multisession:Yes\n";
		else
			szReturnString+="Multisession:No\n";
		char s[80];
		sprintf(s,"Buffer Size: %dKB\n",toInt16(p->buffer_size));
		szReturnString+=s;
		
	}
	return szReturnString;
}
//--------------------------------------------------------------------------

bool SCSI2::SCSISetSpeed(int read,int write){
	unsigned char szBuffer[0x100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 0xff;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 18;
	srbExec.SRB_CDBLen = 12;
	srbExec.CDBByte [ 0 ] = 0xbb;
	srbExec.CDBByte [ 2 ] = (read>>8)&0xff;
	srbExec.CDBByte [ 3 ] = read&0xff;
	srbExec.CDBByte [ 4 ] = (write>>8)&0xff;
	srbExec.CDBByte [ 5 ] = write&0xff;
	
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	if(srbExec.SRB_TargStat == STATUS_CHKCOND&&!m_silence){
		m_sense=*(scsi_sense *)srbExec.SenseArea;
		AfxMessageBox(checkSense());
	}
	return srbExec.SRB_Status == SS_COMP;
}
//--------------------------------------------------------------------------
CString  SCSI2::ReadTrackInfo(int track,track_info*result){

	unsigned char szBuffer[0x100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = sizeof(track_info);
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 18;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x52;
	srbExec.CDBByte [ 1 ] = 0x01;	
	srbExec.CDBByte [ 5 ] = track<1?0xff:track;
	srbExec.CDBByte [ 8 ] = 0xff;

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );

	if ( srbExec.SRB_Status != SS_COMP ){
		m_sense=*(scsi_sense *)srbExec.SenseArea;
		AfxMessageBox(checkSense());
		return "";
	}

	else{
		track_info *p=(track_info *)szBuffer;
		if(result!=NULL)*result=*(track_info *)szBuffer;

		CString szReturnString,s;
		s.Format("Track Number:%d,Session Number:%d\n",
			p->track_number_LSB,p->session_number_LSB);
		szReturnString+=s;

		switch(p->track_mode&0xD){
		case 4:			szReturnString+="Data Track,Uninteruppted\n";
						break;
		case 5:			szReturnString+="Data Track,Incremental\n";
						break;
		}
		szReturnString+=p->damage?"Damaged,":"Not Damaged\n";
		if(p->damage)	szReturnString+=p->NWA_V?"Writting allowed\n":"No writting allowed\n";
		szReturnString+=p->RT?"Reserved\n":"Not Reserved\n";
		szReturnString+=p->blank?"Blank\n":"Not Blank\n";
		szReturnString+=p->packet?"Packet":"Not Packet\n";
		if(p->packet)	szReturnString+=p->fp?"(Fixed Size)\n":"(Variable)\n";
		switch(p->data_mode){
		case 1:			szReturnString+="Mode1\n";
						break;
		case 2:			szReturnString+="Mode2\n";
						break;
		}
		s.Format("Track start address: %Xh\n",SCSI2::toInt32(p->track_start_addr));
		szReturnString+=s;
		if(p->LRA_V){	
			s.Format("Last Record address: %Xh\n",SCSI2::toInt32(p->last_record_addr));
			szReturnString+=s;
		}
		else
			szReturnString+="Last Record address: Not Available\n";
		s.Format("Track size: %Xh\n",SCSI2::toInt32(p->track_size));
		szReturnString+=s;
		if(p->NWA_V){
			s.Format("Next writable address: %Xh\n",SCSI2::toInt32(p->next_writtable_addr));
			szReturnString+=s;
		}
		else
			szReturnString+="Next Writable address: Not Available\n";
		return szReturnString;	
	}
}
//--------------------------------------------------------------------------
CString  SCSI2::ReadDiskInfo(disk_info *result){

	CString szReturnString;
	unsigned char szBuffer[0x100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = sizeof(disk_info);
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 18;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x51;
	srbExec.CDBByte [ 8 ] = 0xff;

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );

	if ( srbExec.SRB_Status != SS_COMP ){
		m_sense=*(scsi_sense *)srbExec.SenseArea;
		AfxMessageBox(checkSense());
		szReturnString="Read Track Info error.";
	}

	else{
		disk_info *p=(disk_info *)(szBuffer);
		char s[80];
		
		szReturnString="Disk Status: ";
		switch(p->disk_status){
		case 0:			szReturnString+="Empty\n";
						break;
		case 1:			szReturnString+="Incomplete\n";
						break;
		case 2:			szReturnString+="Complete\n";
						break;
		default:		szReturnString+="Other\n";
						break;
		}

		szReturnString="State of Last Session: ";
		switch(p->disk_status){
		case 0:			szReturnString+="Empty\n";
						break;
		case 1:			szReturnString+="Incomplete\n";
						break;
		case 3:			szReturnString+="Complete\n";
						break;
		default:		szReturnString+="Other\n";
						break;
		}
		szReturnString+=p->erasable?"Erasable,":"Not Erasable\n";
		
		sprintf(s,"Frist Track: %d\n",p->first_track);
		szReturnString+=s;
		sprintf(s,"Sessions: %d\n",p->numsess);
		szReturnString+=s;
		szReturnString+="Disk Type: ";
		switch(p->disk_type){
		case 0:			szReturnString+="CD-DA/CDROM\n";
						break;
		case 0x10:			szReturnString+="CD-I\n";
						break;
		case 0x20:			szReturnString+="CDROM-XA\n";
						break;
		default:		szReturnString+="Unknown\n";
						break;
		}		
	}
	if(result!=NULL)	*result=*(disk_info *)(szBuffer);
	return szReturnString;
}
//--------------------------------------------------------------------------
CString SCSI2::WriteParameters () {

	CString szReturnString;
	unsigned char szBuffer[0x100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = sizeof(cd_mode_page_05);
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 18;
	srbExec.SRB_CDBLen = 6;
	srbExec.CDBByte [ 0 ] = SCSI_MODE_SEN6;
	srbExec.CDBByte [ 1 ] = 0x08;
	srbExec.CDBByte [ 2 ] = 0x05;
	srbExec.CDBByte [ 4 ] = sizeof(cd_mode_page_05);

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );

	if ( srbExec.SRB_Status != SS_COMP )
		szReturnString="Mode Sense error.";
	else{
		cd_mode_page_05 *p=(cd_mode_page_05 *)(szBuffer+4);
		char s[80];
		
		szReturnString="Write Type: ";
		switch(p->write_type){
		case 0:			szReturnString+="Packet/Incremental\n";
						break;
		case 1:			szReturnString+="Track At Once\n";
						break;
		case 2:			szReturnString+="Session At Once\n";
						break;
		case 3:			szReturnString+="Raw\n";
						break;
		default:		szReturnString+="Unknown\n";
						break;
		}
		szReturnString+="Multisession: ";
		szReturnString+=p->multi_session==3?"Yes\n":"No\n";
		if(p->ls_v){
			sprintf(s,"Link size: %d sectors\n",p->link_size);
			szReturnString+=s;
		}
		else
			szReturnString+="Link Size: 7 sectors\n";

		szReturnString+="Buffer Underrun Free: ";
		szReturnString+=p->BUFE?"Yes\n":"No\n";
		
		szReturnString+="Track Mode: ";
		switch(p->track_mode&0xD){
		case 8:
		case 0:			szReturnString+="2 Audio Channels, No Pre-emphasis\n";
						break;
		case 9:
		case 1:			szReturnString+="2 Audio Channels, Pre-emphasis:50/15uS\n";
						break;
		case 4:			szReturnString+="Data Track,Uninteruppted\n";
						break;
		case 5:			szReturnString+="Data Track,Incremental\n";
						break;
		default:		szReturnString+="Unknown\n";
						break;
		}
		
		szReturnString+="Data Block Type: ";
		switch(p->dbtype){
		case 0:			szReturnString+="Raw Data(2352 Bytes)\n";
						break;
		case 1:			szReturnString+="Raw Data with P,Q Sub-channel(2368 Bytes)\n";
						break;
		case 2:			szReturnString+="Raw data with P-W Sub-channel(2448 Bytes)\n";
						break;
		case 3:			szReturnString+="Raw data with raw P-W Sub-channel(2448 Bytes)\n";
						break;
		case 8:			szReturnString+="Mode1(2048 Bytes)\n";
						break;
		case 9:			szReturnString+="Mode2(2336 Bytes)\n";
						break;
		case 10:		szReturnString+="Mode2(2048 Bytes)\n";
						break;
		case 11:		szReturnString+="Mode2(2056 Bytes)\n";
						break;
		case 12:		szReturnString+="Mode2(2324 Bytes)\n";
						break;
		case 13:		szReturnString+="Mode2(2332 Bytes)\n";
						break;
		default:		szReturnString+="Unknown\n";
						break;
		}
		
		szReturnString+="Session format: ";
		switch(p->session_format){
		case 0:			szReturnString+="CD-DA/CDROM\n";
						break;
		case 0x10:			szReturnString+="CD-I\n";
						break;
		case 0x20:			szReturnString+="CDROM-XA\n";
						break;
		default:		szReturnString+="Unknown\n";
						break;
		}
		if(p->write_type==0){
			if(p->fp==1){
				sprintf(s,"Packet size: %d user data blocks\n",toInt32(p->packet_size));
				szReturnString+=s;
			}
			else
				szReturnString+="Packet size: Variable\n";
			
		}
		sprintf(s,"Subheader: 0x%02X 0x%02X 0x%02X 0x%02X\n",
			p->sub_h.fileNumber,p->sub_h.channelNumber,p->sub_h.subMode,p->sub_h.coding);
		szReturnString+=s;
	}
	return szReturnString;
}
//--------------------------------------------------------------------------
bool SCSI2::SetWriteParameters (int write_type,int dbtype,int track_mode,
								int session_format) {

	unsigned char szBuffer[0x100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_BufLen = sizeof(cd_mode_page_05);
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 18;
	srbExec.SRB_CDBLen = 6;
	srbExec.CDBByte [ 0 ] = SCSI_MODE_SEN6;
	srbExec.CDBByte [ 1 ] = 0x08;
	srbExec.CDBByte [ 2 ] = 0x05;
	srbExec.CDBByte [ 4 ] = sizeof(cd_mode_page_05);

	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	while ( srbExec.SRB_Status == SS_PENDING );
	if ( srbExec.SRB_Status == SS_COMP ){
		cd_mode_page_05 *p=(cd_mode_page_05 *)(szBuffer+4);
		p->write_type=write_type;		//Packet
		p->fp=0;						//Variable Packet Size
		p->dbtype=dbtype;				//Mode 2 form 1
		p->track_mode=track_mode;		//Data,incremental
		p->session_format=session_format;	//CDROM
		p->sub_h.subMode=0x08;

		srbExec.SRB_Status = 0;
		srbExec.SRB_HaStat=0;
		srbExec.SRB_Flags = SRB_DIR_OUT;
		srbExec.SRB_SenseLen = 18;
		srbExec.SRB_CDBLen = 6;
		srbExec.CDBByte [ 0 ] = SCSI_MODE_SEL6;
		srbExec.CDBByte [ 1 ] = 0x10;
		srbExec.CDBByte [ 2 ] = 0;
		pfnSendASPI32Command ( ( LPSRB ) &srbExec );
		while ( srbExec.SRB_Status == SS_PENDING );
		if(srbExec.SRB_TargStat == STATUS_CHKCOND&&!m_silence){
			m_sense=*(scsi_sense *)srbExec.SenseArea;
			AfxMessageBox(checkSense());
		}
	}

	return srbExec.SRB_Status == SS_COMP;
}
//--------------------------------------------------------------------------
void SCSI2::LoadUnload (bool load ) {

	CString szReturnString;
	unsigned char szBuffer[100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 18;
	srbExec.SRB_CDBLen = 6;
	srbExec.CDBByte [ 0 ] = 0x1E;
	srbExec.CDBByte [ 4 ] = 0;
	
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	
	if(checkError(srbExec.SRB_Status)=="SUCCESS"){
		srbExec.SRB_CDBLen = 12;
		srbExec.CDBByte [ 0 ] = 0xA6;
		srbExec.CDBByte [ 4 ] = load?3:2;
		pfnSendASPI32Command ( ( LPSRB ) &srbExec );
		if(checkError(srbExec.SRB_Status)!="SUCCESS"){
			//ASPIReset(m_HA,m_ID,m_LUN);
			srbExec.SRB_CDBLen = 6;
			srbExec.CDBByte [ 0 ] = 0x1B;
			srbExec.CDBByte [ 4 ] = load?3:2;
			pfnSendASPI32Command ( ( LPSRB ) &srbExec );
		}
	}
}
//--------------------------------------------------------------------------
CString SCSI2::PMA () {

	CString szReturnString;
	unsigned char szBuffer[1024];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 1024;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 28;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x43;
	srbExec.CDBByte [ 2 ] = 0x03;
	srbExec.CDBByte [ 7 ] = 4;
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	if(checkError(srbExec.SRB_Status)=="SUCCESS"){
		char s[80];
		cd_pma* pma=(cd_pma*)szBuffer;
		int	length=toInt16(pma->header.dataLen)-2;
		if(length==0)	return CString("No PMA available");
		cd_PMA_desc* p=&(pma->desc);
		for(int i=0;i<length;i+=11){
			szReturnString+="============PMA====================\n";
			if(p->TNO==0&&p->point==0&&p->pmin==0&&p->pframe==0){
				sprintf(s,"Disk ID:%02d%02d%02d\n",p->min,p->sec,p->frame);
				szReturnString+=s;
				szReturnString+="Session Format:";
				switch(p->psec){
				case 0:		szReturnString+="CDDA/CD-ROM\n";
							break;
				case 0x10:
				case 10:	szReturnString+="CDI\n";
							break;
				case 0x20:
				case 20:	szReturnString+="CD-ROM XA\n";
							break;
				default:	szReturnString+="Unknown\n";
							break;
				}	
			}
			else{
				sprintf(s,"Track:%d\n",p->point);
				szReturnString+=s;
				sprintf(s,"Track Start Time %02d:%02d:%02d\n",p->pmin,p->psec,p->pframe);
				szReturnString+=s;
				sprintf(s,"Track End Time %02d:%02d:%02d\n",p->min,p->sec,p->frame);
				szReturnString+=s;
			}
			p++;
		}		
	}
	else if(srbExec.SRB_TargStat== STATUS_CHKCOND){
		m_sense=*(scsi_sense *)srbExec.SenseArea;
		szReturnString=checkSense();
	}
	return szReturnString;
}
//--------------------------------------------------------------------------
CString SCSI2::ATIP() {

	CString szReturnString;
	unsigned char szBuffer[100];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 36;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 28;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x43;
	srbExec.CDBByte [ 2 ] = 0x04;
	srbExec.CDBByte [ 8 ] = 100;
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );

	cd_atip* atip=(cd_atip*)szBuffer;

	if(checkError(srbExec.SRB_Status)=="SUCCESS"){
		if(atip->desc.lead_in[1]==0&&atip->desc.lead_in[2]==0&&atip->desc.lead_in[3]==0)
			szReturnString="CDROM";
		else		szReturnString=(atip->desc.erasable)?"CDRW\n":"CDR\n";
		char s[80];
		sprintf(s,"Possible Start Time of First Lead-In:%dMin:%dSec:%dFrm\n",
			atip->desc.lead_in[0],atip->desc.lead_in[1],atip->desc.lead_in[2]);
		szReturnString+=s;
		sprintf(s,"Possible Start Time of Last Lead-Out:%dMin:%dSec:%dFrm\n",
			atip->desc.lead_out[0],atip->desc.lead_out[1],atip->desc.lead_out[2]);
		szReturnString+=s;
		if(atip->desc.a1_v){
			sprintf(s,"Maximum Recording Speed:%dX\n",(atip->desc.clv_high)*2);
			szReturnString+=s;
		}
			
	}
	else if(srbExec.SRB_TargStat== STATUS_CHKCOND){
		m_sense=*(scsi_sense *)srbExec.SenseArea;
		szReturnString=checkSense();
	}
	return szReturnString;
}
//--------------------------------------------------------------------------
CString SCSI2::TOC () {

	CString szReturnString;
	unsigned char szBuffer[1024];
	SRB_ExecSCSICmd srbExec;
	memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
	srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
	srbExec.SRB_HaId = m_HA;
	srbExec.SRB_Flags = SRB_DIR_IN;
	srbExec.SRB_Target = m_ID;
	srbExec.SRB_Lun = m_LUN;
	srbExec.SRB_BufLen = 37;
	srbExec.SRB_BufPointer = szBuffer;
	srbExec.SRB_SenseLen = 28;
	srbExec.SRB_CDBLen = 10;
	srbExec.CDBByte [ 0 ] = 0x43;
	srbExec.CDBByte [ 2 ] = 0x00;
	srbExec.CDBByte [ 7 ] = 4;
	pfnSendASPI32Command ( ( LPSRB ) &srbExec );
	if(checkError(srbExec.SRB_Status)=="SUCCESS"){
		char s[80];
		cd_toc_header* header=(cd_toc_header*)szBuffer;
		sprintf(s,"Sessions:%d to %d\n",header->firstSession,header->lastSession);
		szReturnString=s;

		int	length=toInt16(header->dataLen)-2;
		if(length==0)	return CString("No PMA available");
		cd_toc_00* p=(cd_toc_00*)(szBuffer+4);
		for(int i=0;i<length;i+=8){
			szReturnString+="===================================\n";
			if(p->firstTrack!=0xaa)
				sprintf(s,"First Track:%d,LBA:%d\n",p->firstTrack,toInt32(p->lba));
			else
				sprintf(s,"Leadout LBA:%d\n",toInt32(p->lba));
			szReturnString+=s;
			p++;
		}
		
			
	}
	else if(srbExec.SRB_TargStat== STATUS_CHKCOND){
		m_sense=*(scsi_sense*)srbExec.SenseArea;
		szReturnString=checkSense();
	}
	return szReturnString;
}
//--------------------------------------------------------------------------
int SCSI2::TestUnitReady () {

   int iRetCode; 
   SRB_ExecSCSICmd srbExec;
   memset ( &srbExec, 0, sizeof ( SRB_ExecSCSICmd ) );
   srbExec . SRB_Cmd = SC_EXEC_SCSI_CMD;
   srbExec . SRB_HaId = m_HA;
   srbExec . SRB_Flags = SRB_EVENT_NOTIFY;
   srbExec . SRB_Target = m_ID;
   srbExec . SRB_SenseLen = SENSE_LEN;
   srbExec . SRB_CDBLen = 6;
   srbExec . SRB_PostProc = ( LPVOID ) hEventSRB;
   srbExec . CDBByte [ 0 ] = SCSI_TST_U_RDY;
   ResetEvent ( hEventSRB );
   pfnSendASPI32Command ( ( LPSRB ) &srbExec );
   if ( srbExec . SRB_Status == SS_PENDING )
      WaitForSingleObject ( hEventSRB, INFINITE );
   if ( srbExec.SRB_Status == SS_COMP )
      iRetCode = 0; // OK

// check what happened (m_sense data automatically returned in the SenseArea)
   else
      {
        BYTE SenseKey = srbExec . SenseArea [ 2 ];
        SenseKey = SenseKey & 15;
        BYTE ASC      = srbExec . SenseArea [ 12 ];
        BYTE ASCQ     = srbExec . SenseArea [ 13 ];
        TRACE3( "TestUnitReady:%d,%d,%d\n", SenseKey, ASC, ASCQ );
        switch ( SenseKey )
           {
			 case 0x06:
               // Power On reset or Bus Device reset
                  if ( ASC == 0x29 && ASCQ == 0x00 ) { iRetCode = 1; break; }
             default:
                  TRACE3( "TestUnitReady:%d,%d,%d\n", srbExec . SRB_Status,
                                  srbExec . SRB_HaStat, srbExec . SRB_TargStat );
                  iRetCode = 99;
           }
      }

   return iRetCode;
}
//----------------------------------------------------------------------------
CString SCSI2::checkError(BYTE status){
	CString result;
	switch(status){
	case SS_PENDING:	result="Pending.";
						break;
	case SS_COMP:		result="SUCCESS";
						break;
	case SS_ABORTED:	result="Aborted.";
						break;
	case SS_ABORT_FAIL:	result="Abort Fail.";
						break;
	case SS_ERR:		result="Finished With Error.";
						break;
	case SS_INVALID_CMD:		result="Invalid Command.";
						break;
	case SS_INVALID_HA:		result="Invalid Host Adapter Number.";
						break;
	case SS_NO_DEVICE:		result="Device Not Installed.";
						break;
	default:		result="Other Errors.";
	}
	return result;
}
//----------------------------------------------------------------------------
CString SCSI2::checkSense(){
	CString s;
	s.Format("sense key:0x%X, ASC=0x%X,ASCQ=0x%X",
		m_sense.key,m_sense.ASC,m_sense.ASCQ);
	return CString(s);
}
//----------------------------------------------------------------------------
int SCSI2::toInt32(unsigned char input[4]){
	return (input[0]<<24)+(input[1]<<16)+
		(input[2]<<8)+input[3];
}
//----------------------------------------------------------------------------
int SCSI2::toInt64(unsigned char input[8]){
	return (input[5]<<24)+(input[6]<<16)+
		(input[7]<<8)+input[8];
}
//----------------------------------------------------------------------------

int SCSI2::toInt16(unsigned char input[2]){
	return (input[0]<<8)+input[1];
}
//----------------------------------------------------------------------------
void	SCSI2::setLBA(long addr){
	m_lba=addr;
}
//----------------------------------------------------------------------------
tag	SCSI2::fillTag(int id,BYTE* data,int size,int location){
	tag result;
	memset(&result,0,16);
	result.tagIdent=id;
	result.descVersion=2;
	result.tagSerialNum=1;
	result.descCRCLength=size;
	result.descCRC=udf_crc(data,size);
	result.tagLocation=location;
	BYTE sum=0;
	for(int i=0;i<16;i++)	sum+=((BYTE*)&result)[i];
	result.tagChecksum=sum;
	return result;
}
//============================================================================

CStringList* SCSI2::chopFileNames(CString s)
{
	int end=0;
	CStringList* outputFileList=new CStringList();
	bool flag=false;
	
	while(!s.IsEmpty()){
		end=s.FindOneOf(",;\t\r\n");
		CString singleFileName;
		if(end==-1)	{
			end=s.GetLength();
			singleFileName=s.Mid(0,end);
			s.Empty();
			continue;
		}
		else{
			singleFileName=s.Mid(0,end);
			s=s.Mid(end+1);
			s.TrimLeft();
		}
		singleFileName.TrimRight();
		outputFileList->AddHead(singleFileName);
	}
	return outputFileList;
}
//----------------------------------------------------------------------------
