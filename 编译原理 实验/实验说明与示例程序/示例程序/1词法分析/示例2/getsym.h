
#ifndef _GETSYM_H_
#define _GETSYM_H_

#include <stdlib.h>		//For memset()
#include <string.h>		//For strcpy()

#define ISLETTER(c)	((c)>='A'&&(c)<='Z'||(c)>='a'&&(c)<='z')
#define ISNUMBER(c)	((c)>='0'&&(c)<='9')
#define ISCHAR(c)	((c)>=33 &&(c)<=126)

#define MAX_SYM			32768	//��������
#define MAX_SYMFORM		1024	//�����ű���
#define	MAX_NUMFORM		4096	//���������

#define MAX_SYMLEN		31		//�����ų���
#define MAX_NUMLEN		10		//���������
#define MAX_BUFFER		MAX_SYMLEN+1//��󻺳峤��

#define MAX_KEYWORD		19		//�ؼ�������
#define MAX_OPWORDA		8		//�������������
#define MAX_OPWORDB		4		//˫�����������
#define MAX_ENDWORD		8		//���ֽ������
#define MAX_ERROR		5		//������������

#define TYPE_KEYWORD	1		//�ؼ������ͺ�
#define TYPE_SYMBOL		2		//�������ͺ�
#define TYPE_NUMBER		3		//�������ͺ�
#define TYPE_OPWORD		4		//��������ͺ�
#define TYPE_ENDWORD	5		//������ͺ�
#define TYPE_ERROR		-1		//�������ͺ�

#define ERR_OVERSYMLEN	1		//������һ������
#define ERR_OVERNUMLEN	2
#define ERR_NUMBER		3
#define ERR_WRONGOP		4
#define ERR_OVERSYMFORM	10001	//���������ش����
#define ERR_OVERNUMFORM 10002
#define ERR_OVERSYMNUM	10003
#define ERR_OVERERRNUM	10004

#ifdef __cplusplus
extern "C" {
#endif

struct SYM		//���������ṹ��(�����������ṹ)
{
	int type;		//���ͺ�(0:����)
	int id;			//ID��(����ֵ)
	int line;		//��������

	char name[MAX_SYMLEN+1];	//��ȡ�Ĵ�
};

struct FORM		//���ṹ��
{
	int symnum;
	int numnum;
	struct SYMF		//���ű���ṹ��
	{
		int id;
		char name[MAX_SYMLEN+1];
	}symf[MAX_SYMFORM];
	struct NUMF		//��������ṹ��
	{
		int id;
		char name[MAX_NUMLEN+1];
	}numf[MAX_NUMFORM];
};

struct SYMINFO	//�ʷ�������Ϣ�ṹ��
{
	int num;
	struct SYM sym[MAX_SYM];
	struct FORM form;
};
//ȡ�ʺ���
int __stdcall getsym(const char *in,struct SYM *out,int *ln,struct FORM *form);
//ȡ���дʺ���
int __stdcall getsyminfo(const char *in,struct SYMINFO *out);

#ifdef  __cplusplus
}
#endif
#endif
