//��ȡ�ļ�������Ϣ�ĺ��Ӧֵ
#define	FILE_NAME				0
#define	FILE_SIZE				1
#define FILE_TYPE				2
#define	FILE_CREATE_TIME		3
#define	FILE_CHANGE_TIME		4
#define	FILE_EDIT_TIME			5
#define	FILE_PHOTO_SIZE			6
#define	FILE_TAKE_PHOTO_TIME	7

#define ORDER_NONE				0x0000
#define ORDER_ASC				0x0001					//��������
#define ORDER_DES				0x0002					//��������

//���λ����Ϣ
#define POSITION_OUT						0x0000		//�ڴ�����
#define POSITION_HEAD_ITEM					0x0001		//����Ŀͷ���б�����
#define POSITION_HEAD_MID					0x0002		//����Ŀͷ���м����
#define POSITION_SCROLL_BAR_V_DRAG_SPACE	0x0004		//�ڴ�ֱ�϶�������ק�հ�������
#define POSITION_SCROLL_BAR_V_UP_BT			0x0008		//�ڴ�ֱ�϶������ϰ�ť��
#define POSITION_SCROLL_BAR_V_MID_BT		0x0010		//�ڴ�ֱ�϶����϶�������
#define POSITION_SCROLL_BAR_V_DOWN_BT		0x0020		//�ڴ�ֱ�϶������°�ť��
#define POSITION_SCROLL_BAR_H_DRAG_SPACE	0x0040		//��ˮƽ�϶�������ק�հ�������
#define POSITION_SCROLL_BAR_H_LEFT_BT		0x0080		//��ˮƽ�϶�������ť��
#define POSITION_SCROLL_BAR_H_MID_BT		0x0100		//��ˮƽ�϶����϶�������
#define POSITION_SCROLL_BAR_H_RIGHT_BT		0x0200		//��ˮƽ�϶������Ұ�ť��
#define POSITION_ITEM						0x0400		//����ʾ�����е�ITEM��
#define POSITION_WORKAREA_NONE				0x0800		//����ʾ�����еĿհ�������

//��������Ϣ
#define MOUSE_NONE				0x0000					//��״̬
#define MOUSE_LBT_DOWN			0x0001					//����������
#define MOUSE_RBT_DOWN			0x0002					//����Ҽ�����
#define MOUSE_MBT_DOWN			0x0004					//����м�����
#define MOUSE_DRAG_FILE			0x0008					//��ק�ļ�
#define MOUSE_DRAG_SELECT		0x0010					//��קѡ��
#define MOUSE_DRAG_SCROLL_V		0x0020					//��ק���򻬶�������
#define MOUSE_DRAG_SCROLL_H		0x0040					//��ק���򻬶�������
#define MOUSE_SCROLL_V_UP		0x0080					//��ס�������ϰ�ť
#define MOUSE_SCROLL_V_DOWN		0x0100					//��ס�������°�ť
#define MOUSE_SCROLL_H_LEFT		0x0200					//��ס��������ť
#define MOUSE_SCROLL_H_RIGHT	0x0400					//��ס�������Ұ�ť
#define MOUSE_SCROLL_V_AREA		0x0800					//��ס���򻬶����Ŀհ�����
#define MOUSE_SCROLL_H_AREA		0x1000					//��ס���򻬶����Ŀհ�����
#define MOUSE_DRAG_HEAD_ITEM	0x2000					//�϶���ͷ��Ŀ
#define MOUSE_DRAG_HEAD_MID		0x4000					//�޸ı�ͷ��Ŀ���

#define FILE_UNDEF				0x0000
#define FILE_DISK				0x0001
#define FILE_FLODER				0x0002
#define FILE_PHOTO				0x0004
#define FILE_OHTER				0x0008
#define FILE_ALL				0xffff

#define STYLE_REPORT			0x0001					//��ϸ�б���ʽ
#define STYLE_ICON				0x0002					//ͼ����ʽ
#define STYLE_LIST				0x0004					//�б���ʽ
#define STYLE_SMALL_PHOTO		0x0008					//����ͼ��ʽ
#define STYLE_PPT				0x0010					//�õ�Ƭ��ʽ
#define STYLE_PICASA			0x0011					//PICASA��ʽ

#define HEAD_ALI_LEFT			0x0001					//���������
#define HEAD_ALI_RIGHT			0x0002					//�����Ҷ���
#define HEAD_ALI_CENTER			0x0004					//���ݾ���

#define DEAL_FILE_COPY			0						//�ļ�����
#define DEAL_FILE_CUT			1						//����
#define DEAL_ASK				0						//ѯ��
#define DEAL_RENAME				1						//������
#define DEAL_RECOVER			2						//����
#define DEAL_PASS				3						//����
#define DEAL_DRAG_LV			0						//��ק����
#define DEAL_DRAG_TYPE			1						//��ק����

#define PHOTO_MAX_WIDTH			320						//����ͼ�����
#define PHOTO_MAX_HEIGHT		240						//����ͼ���߶�
#define REPORT_ITEM_HEIGHT		20						//REPORT��ʽʱITEM�ĸ߶�
#define REPORT_HEAD_HEIGHT		20						//REPORT��ʽ��ͷ�ĸ߶�

#define STATE_NONE				0x0000					//����״̬
#define STATE_MOUSE_OVER		0x0001					//����ڷ�Χ��
#define STATE_MOUSE_LDOWN		0x0002					//����������
#define STATE_MOUSE_RDOWN		0x0004					//����Ҽ�����
#define STATE_MOUSE_MDOWN		0x0008					//����м�����		

#define SCROLL_BAR_NONE					0x0000			//���϶���
#define SCROLL_BAR_H					0x0001			//�����϶���
#define SCROLL_BAR_V					0x0002			//�����϶���
#define SCROLL_BAR_WIDTH_HEIGHT			20				//�϶����Ŀ�Ȼ�߶�
#define SCROLL_DRAG_ENABLE_DISTANCE		100				//�϶�����ʱ��Ч����
#define SMALL_PHOTO_ITEM_BORDER			5				//����ͼ��ʾ��ʽʱ��ITEM����Χ�ļ��
#define PHOTO_BORDER_WIDTH				5				//����ͼ����ͼ��ʱ����Χ���
#define PHOTO_SMALL_TARGET_HEIGHT		10				//����ͼ����ʱ�ı�־������Ҫ�߶�
#define PHOTO_SMALL_WORD_HEIGHT			20				//����ͼ����ʱ���ָ߶�
#define PHOTO_SHADOW_WIDTH				3				//����ͼ��Ӱ���
#define PHOTO_SHADOW_MOVE				3				//����ͼ��Ӱ��ԭͼ���

#define MES_ALZQ_OPEN_FLODER (WM_USER+100)				//˫���ļ���ʱ�򸸴��ڷ�����Ϣ
#define MES_ALZQ_SHOW_PHOTO (WM_USER+101)				//����������ʾͼ�����Ϣ
#define MES_ALZQ_VIEW_PHOTO (WM_USER+200)				//˫��ͼ���ļ�ʱ�򸸴��ڷ��͵���Ϣ

#define MES_ALZQ_BEGIN_DRAG_LV (WM_USER+201)			//��ʼ��ק�ȼ�ʱ�����͵���Ϣ
#define MES_ALZQ_BEGIN_DRAG_TYPE (WM_USER+202)			//��ʼ��ק�ļ�����ʱ�����͵���Ϣ
#define MES_ALZQ_END_DRAG_LV (WM_USER+203)				//������ק�ȼ�ʱ�����͵���Ϣ
#define MES_ALZQ_END_DRAG_TYPE (WM_USER+204)			//������ק�ļ�����ʱ�����͵���Ϣ
#define MES_ALZQ_REFRESH_ALL (WM_USER+300)				//ˢ��LIST�ؼ�����ͼ��
#define MES_ALZQ_REFRESH_ITEM (WM_USER+301)				//ˢ��LIST�ؼ���һ��ITEM�������һ������ΪITEM��ʼ��ţ���2������ΪITEM�������