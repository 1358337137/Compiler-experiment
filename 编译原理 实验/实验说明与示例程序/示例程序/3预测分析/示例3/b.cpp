#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main()
{
string sheet[5][6]={{"TA","TA","","","",""}, //Ԥ�������
{"","","e","+TA","","e"}, //��:E,A(���� E1),T,B(���� T1),F
{"FB","FB","","","",""}, //��:i,(,),+,*,$
{"","","e","e","*FB","e"}, //e����մ�
{"i","(E)","","","",""}};
vector<char> S;
vector<char> Stc;
vector<char> SOS;
string STC;
int YourChoice;
do{
cout<<endl;
S=SOS; //S�������ջ,ÿ��ִ���ÿյ�SOS��ʼ��
S.push_back('$');
S.push_back('E');
STC=""; //STC�����û��ı��ʽ
cout<<"��������Ҫ�������ַ���:";
cin>>STC;
STC.resize(STC.size()+1);
STC[STC.size()-1]='$';
Stc=SOS; //Stc�ǽ�STC+$����ѹ����û�����ջ
for(int x=STC.size()-1;x>=0;--x)
Stc.push_back(STC[x]);
string YY="EATBF";
string XX="i()+*$";
while(!(S[S.size()-1]=='$'&&Stc[Stc.size()-1]=='$'))
{
int i=0,j=0;
////////////////////����ҵ���Ӧ����////////////////////
for(i=0;i<5;++i)
if(YY[i]==S[S.size()-1])
break;
for(j=0;j<6;++j)
if(XX[j]==Stc[Stc.size()-1])
break;
if(i>=5||j>=6) //������ҳ�����
{
cout<<"������!"<<endl;
break;
}
else if(sheet[i][j]=="") //����鵽��Ϊ�չ���
{
cout<<"������!"<<endl;
break;
}
else
{
///////////////����ջ���ѹջ�뵯ջ////////////////////
S.pop_back();
for(int k=sheet[i][j].size()-1;k>=0;--k)
S.push_back(sheet[i][j][k]);
if(S[S.size()-1]==Stc[Stc.size()-1]) //һ�����
{
S.pop_back();
Stc.pop_back();
}
else if(S[S.size()-1]=='e') //���մ��Ĺ���
{
S.pop_back();
if(S[S.size()-1]!='$'&&Stc[Stc.size()-1]!='$'&&S[S.size()-1]==Stc[Stc.size()-1])
{
S.pop_back();
Stc.pop_back();
}
}
}
}

if(S[S.size()-1]=='$'&&Stc[Stc.size()-1]=='$')
cout<<"�����ɹ�!"<<endl;
cout<<"����0����,�����˳�";
}while(cin>>YourChoice&&YourChoice==0);

return 0;
}
