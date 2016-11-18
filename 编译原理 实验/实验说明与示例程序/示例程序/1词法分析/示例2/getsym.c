
#include "getsym.h"
//�ؼ���
const char* const keytxt[MAX_KEYWORD]=
{
	"of","array","program","mod","and","or",
	"not","begin","end","if","then","else","while",
	"do","call","const","type","var",
	"procedure"
};
//���������
const char opatxt[MAX_OPWORDA]=
{
	'+','-','*','/','=','#','<','>'
};
//˫�������
const char* const opbtxt[MAX_OPWORDB]=
{
	"<=",">=",":=","<>"
};
//���ֽ��
const char eoptxt[MAX_ENDWORD]=
{
	'(',')',',',';','.','[',']',':'
};
//������ʾ��Ϣ
const char* const errtxt[MAX_ERROR]=
{
	"OK",	//Not used.
	"Too long symbol",
	"Too long number",
	"Mixed number and letter",
	"Unkown operator",
};

int getsym(const char *in,struct SYM *out,int *ln,struct FORM *form)
{
	char b[MAX_BUFFER];			//�����Ż�����
	int i,m=0,n=0,e=0;			//���/���ַ���/�ַ���/������
	memset(out,0,sizeof(struct SYM));
	while(!ISCHAR(*in))			//�˳�ǰ��ķ��ַ�
	{
		if(*in==10) (*ln)++;//����ʱ,ln++
		if(*in++) m++; else return 0;	//������ַ����˳�
	}
	out->line=*ln;
	if(ISLETTER(*in))			//��ĸ��ͷ���
	{
		while(ISLETTER(*in)||ISNUMBER(*in))
		{
			if(n<=MAX_SYMLEN) b[n]=*in;
			n++; in++;
		}
		b[MAX_SYMLEN]=0;		//���Ž�β��0
		if(n<MAX_SYMLEN) b[n]=0;
		strcpy(out->name,b);
		if(n>MAX_SYMLEN)		//����������󳤶�
		{
			out->type=TYPE_ERROR;
			out->id=ERR_OVERSYMLEN;
		}
		else
		{
			for(i=0;i<MAX_KEYWORD;i++)
				if(strcmp(b,keytxt[i])==0) break;
			if(i<MAX_KEYWORD)	//���ڹؼ���
			{
				out->type=TYPE_KEYWORD;
				out->id=i;
			}
			else				//�����ڹؼ���
			{
				for(i=0;i<form->symnum;i++)
					if(strcmp(b,form->symf[i].name)==0) break;
				if(i==form->symnum)	//���ڷ��ű��������
				{
					if(form->symnum>=MAX_SYMFORM)
					{			//�������ű�Χ�������ش���
						out->type=TYPE_ERROR;
						out->id=ERR_OVERSYMFORM;
						return m+n;
					}
					form->symf[i].id=i;
					strcpy(form->symf[i].name,b);
					form->symnum++;
				}
				out->type=TYPE_SYMBOL;	//��������
				out->id=i;
			}
		}
		return m+n;
	}
	if(ISNUMBER(*in))			//���ֿ�ͷ���
	{
		e=0;
		while(ISNUMBER(*in)||ISLETTER(*in))
		{
			if(ISLETTER(*in)) e=1;	//����ĸ���ó�����
			if(n<=MAX_NUMLEN) b[n]=*in;
			n++; in++;
		}
		b[MAX_NUMLEN]=0;		//����β��0
		if(n<MAX_NUMLEN) b[n]=0;
		strcpy(out->name,b);
		if(e||n>MAX_NUMLEN)	//�г����ǻ򳬳�������󳤶�
		{
			out->type=TYPE_ERROR;
			if(e)				//����ĸ���
				out->id=ERR_NUMBER;
			else				//����������󳤶����
				out->id=ERR_OVERNUMLEN;
		}
		else					//�޴����
		{
			if(form->numnum>=MAX_NUMFORM)
			{					//����������Χ�������ش���
				out->type=TYPE_ERROR;
				out->id=ERR_OVERNUMFORM;
				return m+n;
			}
			form->numf[form->numnum].id=form->numnum;
			strcpy(form->numf[form->numnum].name,b);
			out->type=TYPE_NUMBER;
			out->id=form->numnum;
			form->numnum++;
		}
		return m+n;
	}
	for(i=0;i<MAX_OPWORDB;i++)	//˫����������
		if(*(short*)in==*(short*)(opbtxt[i])) break;
	if(i<MAX_OPWORDB)
	{
		out->type=TYPE_OPWORD;
		out->id=MAX_OPWORDA+i;
		*(short*)out->name=*(short*)opbtxt[i];
		out->name[2]=0;
		return m+2;
	}
	out->name[0]=*in;
	out->name[1]=0;
	for(i=0;i<MAX_OPWORDA;i++)	//������������
		if(*in==opatxt[i]) break;
	if(i<MAX_OPWORDA)
	{
		out->type=TYPE_OPWORD;
		out->id=i;
		return m+1;
	}
	for(i=0;i<MAX_ENDWORD;i++)	//���ֽ�����
		if(*in==eoptxt[i]) break;
	if(i<MAX_ENDWORD)
	{
		out->type=TYPE_ENDWORD;
		out->id=i;
		return m+1;
	}
	out->type=TYPE_ERROR;
	out->id=ERR_WRONGOP;		//�������������
	return m+1;
}

int getsyminfo(const char *in,struct SYMINFO *out)
{
	int offset,ln=1;			//ÿ��ȡ��ƫ����/��ǰ����
	memset(out,0,sizeof(struct SYMINFO));
	while(1)
	{
		offset=getsym(in,&out->sym[out->num],&ln,&out->form);
		if(offset==0) break;	//���ȡ�����˳�
		if(out->num>=MAX_SYM) return ERR_OVERSYMNUM;//����������Ϣ���ֵ
		if(out->sym[out->num].type==TYPE_ERROR&&out->sym[out->num].id>=10000)
			return out->sym[out->num].id;//�����ش������˳�
		out->num++;
		in+=offset;
	}
	return 0;
}
