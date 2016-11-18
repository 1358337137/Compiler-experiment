#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
#include <map>
using namespace std;

void show();
//�ķ�G[E]��SLR(1)������֮ACTION
string action[16][8]=
{   {"S5","","","","","S4","",""},
    {"","S6","S7","","","","","acc"},
    {"","r3","r3","S8","S9","","r3","r3"},
    {"","r6","r6","r6","r6","","r6","r6"},
    {"S5","","","","","S4","",""},
    {"","r8","r8","r8","r8","","r8","r8"},
    {"S5","","","","","S4","",""},
    {"S5","","","","","S4","",""},
    {"S5","","","","","S4","",""},
    {"S5","","","","","S4","",""},
    {"","S6","S7","","","","S15",""},
    {"","r1","r1","S8","S9","","r1","r1"},
    {"","r2","r2","S8","S9","","r2","r2"},
    {"","r4","r4","r4","r4","","r4","r4"},
    {"","r5","r5","r5","r5","","r5","r5"},
    {"","r7","r7","r7","r7","","r7","r7"},
};
//�ķ�G[E]��SLR(1)������֮GOTO
int GOTO[16][3]=
{   {1,2,3},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {10,2,3},
    {0,0,0},
    {0,11,3},
    {0,12,3},
    {0,0,13},
    {0,0,14}
};
char str[100];//����ʽ
string redu[9]= {"E->E+T", "E->E-T", "E->T","T->T*F", "T->T/F", "T->F","F->(E)","F->i"};
map<char,int>id;
void init()
{  //���뽫�ս���ͷ��ս���ֱ����
    char s[]="i+-*/()$";
    for(int i=0;i<8;i++) id[s[i]]=i;
    id['E']=0;id['T']=1;id['F']=2;
}
int solve()
{
    stack<int> state;
    stack<char> sign;
    state.push(0); //״̬ջѹ��0
    sign.push('$');//����ջ��ѹ��'$'
    char a;
    int j=0,len;
    len=strlen(str);
    str[len]='$';//���봮��β�����'$'
    do{
        while(str[j]==' ')j++;//ȥ�����ʽ�еĿո�
        a=str[j];//ȡ���봮������ĸ
        if(id.find(a)==id.end())return 1;//�Ƿ������ʽ�д��ڷǷ��ַ�
        string temp=action[state.top()][id[a]];
        if(temp.length()>0)//��Ӧ��ACTION��Ϊ��
        {
            //printf("%s  %d  %c\n",temp.c_str(),state.top(),sign.top());
            if(temp=="acc")return 0;//�Ϸ�
            if(temp[0]=='S')//�ƽ�
            {
                j++;sign.push(a);
                int index=temp[1]-'0';
                if(index==1)index=15;
                state.push(index);//ѹ���µ�״̬
            }
            else//��Լ
            {
                int index=temp[1]-'1';//���ǵڼ�������ʽ
                //״̬ջɾ��L��״̬ �ͷ���ջL������
                for(int l=redu[index].length();l>3;l--)
                {   state.pop();
                    sign.pop();
                }
                sign.push(redu[index][0]);//ѹ�����ʽ��ߵ�
                int tt=GOTO[state.top()][id[sign.top()]];
                state.push(tt);//״̬ջѹ���µ�״̬
            }
        }
        else
            return 2;//�Ƿ�,��Ӧ��ACTIONΪ��
    }while(a!='$'||sign.top()!='$'); //ֻҪ��һ��û��
}
int main()
{
   // show();
    init();
    freopen("in.txt","r",stdin);
   //freopen("out.txt","w",stdout);
    while(gets(str))
    {
        printf("%-20s",str);
        int flag=solve();
        if(flag==0)printf(" �Ϸ���\n");
        else  printf("���Ϸ���\n");
    }
    return 0;
}
/*
void show()
{
    char s[]=" i+-x/()$ETF";
    for(int i=0;i<=11;i++)
        printf("%-5c",s[i]);
        printf("\n");
    for(int i=0;i<=15;i++)
    {
        printf("%-5d",i);
        for(int j=0;j<8;j++)
        {
            if(action[i][j].length()>0)
               printf("%-5s",action[i][j].c_str());
            else
                printf("%-5s","-");
        }
        for(int j=0;j<3;j++)
            printf("%-5d",GOTO[i][j]);
        printf("\n");
    }

}*/
