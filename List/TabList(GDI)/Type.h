#if !defined _TYPE_H_
#define _TYPE_H_

////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct tagFILETYPE				// �Զ�������ݿ��ļ���ʽ
{
	char Flag[4];						// ��־,�ҵ���"QDB\0"
    long rCount;						// �ܼ�¼��
	long rLen;							// ÿ����¼����
	char rev[116];                      // �����ֽ�,��Ϊ�Ժ���չ��
}FILETYPE;

typedef  struct  tagDATA
{
	char name[80];						// ��˾����                           
	char rev1;							// �����ֽ�,��Ϊ��,�����֤����Ľ�β
	char add[60];						// ��˾��ַ
	char rev2;							// �����ֽ�,��Ϊ��,����Ա������Ľ�β
	char industry[60];					// ��ҵ
	char rev3;							// �����ֽ�,��Ϊ��,����Ա������Ľ�β
	char scale[60];						// ��ģ
	char rev4;							// �����ֽ�,��Ϊ��,�������Ľ�β
	char contact[60];				    // ��ϵ��ʽ
	char rev5;							// �����ֽ�,��Ϊ��,���ֻ�����Ľ�β
	char attrib[40];				    // ����
	char rev6;							// �����ֽ�,��Ϊ��,���ֻ�����Ľ�β
	char source[60];                    // ��Ϣ��Դ     
	char rev7;							// �����ֽ�,��Ϊ��,���ֻ�����Ľ�β
	char npost[40];                     // ְ������     
	char rev8;							// �����ֽ�,��Ϊ��,���ֻ�����Ľ�β
	char salary[40];                    // нˮ����     
	char rev9;							// �����ֽ�,��Ϊ��,���ֻ�����Ľ�β
	char stype;                         // ���»��߰���
    char x1;
	char x2;
	char x3;
	char c1;
	char c2;
	char c3;
 	char end;
	char date[14];
	char rev10;
	char introduction[800];             // �򵥽���     
	char rev11;							// �����ֽ�,��Ϊ��,���ֻ�����Ľ�β
    char level[800];                    // ˮƽҪ��
	char rev12;
	char ls;                            //����
	char lsinfo[800];
	char rev13;
	char rev[136];

}MYDATA;

typedef struct tagRECORD                // ���ݼ�¼˫����
{
	MYDATA    *Data;                    // ��ǰ���ݹܼ�
    struct     tagRECORD *prev;         // ��һ���ݼ�¼
	struct     tagRECORD *next;         // ��һ���ݼ�¼
}RECORD;

////////////////////////////////////////////////////////////////////////////////////////////////
#endif 

