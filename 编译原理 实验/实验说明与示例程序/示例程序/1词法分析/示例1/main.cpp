#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;
/**
---�ؼ���---
9
main   1
return 2
int    3
char   4
float  5
double 6
for    7
scan   8
print  9
---��ʶ��---
10
----������----
11
----��ʵ��--
12
----�ֽ��--
8
{  20
}  21
(  22
)  23
;  24
,  25

----�����---
7
+  10
-  11
*  12
/  13
<  14
>  15
=  16

*/
map<string,int>encode;//�ؼ��֡��ֽ���������
FILE *fp;
void ReadEncode()
{
    fp=fopen("encode.txt","r");
    if(fp==NULL)
    {
        printf("�ļ�����������!\n");
        exit(0);
    }
    int n;
    fscanf(fp,"%d",&n);
    char  s[20];
    int value;
    for(int i=0; i<n; i++)
    {
        fscanf(fp,"%s",s);
        fscanf(fp,"%d",&value);
        encode[s]=value;
    }
    fscanf(fp,"%d",&n);
    for(int i=0; i<n; i++)
    {
        fscanf(fp,"%s",s);
        fscanf(fp,"%d",&value);
        encode[s]=value;
    }
    fscanf(fp,"%d",&n);
    for(int i=0; i<n; i++)
    {
        fscanf(fp,"%s",s);
        fscanf(fp,"%d",&value);
        encode[s]=value;
    }
}

void solve()
{
    char ch;
    fp=fopen("code.c","r");
    if(fp==NULL)
    {
        printf("�ļ�����������!\n");
        exit(0);
    }
    ch=fgetc(fp);
    string s;
    while(!feof(fp))
    {
        //1.ʶ��ֽ��
        if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch==';'||ch==',')
        {
            s=ch;
            printf("<%d,%c>\n",encode[s],ch);
            ch=fgetc(fp);
        }//2.�����
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='>'||ch=='<'||ch=='=')
        {
            s=ch;
            printf("<%d,%c>\n",encode[s],ch);
            ch=fgetc(fp);
        }
        //(3).�жϹؼ��ֺͱ���
        else if(isalpha(ch))
        {
            s="";
            //��ʶ������ĸ��ͷ����������ֻ���ĸ
            while(isalpha(ch)||isdigit(ch))
            {
                s+=ch;
                ch=fgetc(fp);
            }
            if(encode.find(s)!=encode.end())//�ؼ���
            {
                printf("<%d,%s>\n",encode[s],s.c_str());
            }
            else//����
                printf("<10,%s>\n",s.c_str());
        }//4.����
        else if(isdigit(ch))
        {
            s="";
            int flag=0;
            while(isdigit(ch)||ch=='.')
            {
                if(ch=='.')flag=1;
                s+=ch;
                ch=fgetc(fp);
            }
            if(flag==0)//������
                printf("<11,%s>\n",s.c_str());
            else  //��ʵ��
                printf("<12,%s>\n",s.c_str());
        }
        else
            ch=fgetc(fp);
    }
}
int main()
{
    freopen("output.txt","w",stdout);
    // ��ȡ�����б�
    encode.clear();
    ReadEncode();
    solve();
    return 0;
}
