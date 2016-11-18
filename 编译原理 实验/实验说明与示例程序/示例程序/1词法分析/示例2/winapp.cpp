#include "winapp.h"		
#include "getsym.h"	

SYMINFO s;			//�ʷ�������Ϣ�ṹ
HINSTANCE hinst;	
OPENFILENAME ofn;	
FILE *fp;			
char in[65536];		//Դ���򻺳���
char str[256];		//��ʱ�ִ�������

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	hinst=hInstance;
	return(DialogBox(hInstance,MAKEINTRESOURCE(IDD_MAINDLG),NULL,(DLGPROC)dlgproc));
}

BOOL CALLBACK dlgproc(HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam)
{
	int i,j;
	switch(msg)
	{
	case WM_INITDIALOG:
		in[65535]=0;	//��β��0��ֹ���
		SendMessage(hdlg,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(hinst,MAKEINTRESOURCE(IDI_ICON)));
		SendDlgItemMessage(hdlg,IDC_INPUT,WM_SETFONT,(DWORD)GetStockObject(ANSI_FIXED_FONT),0);
		SendDlgItemMessage(hdlg,IDC_OUTPUT,WM_SETFONT,(DWORD)GetStockObject(SYSTEM_FIXED_FONT),0);
		SendDlgItemMessage(hdlg,IDC_ERRPUT,WM_SETFONT,(DWORD)GetStockObject(SYSTEM_FIXED_FONT),0);
		memset(&ofn,0,sizeof(OPENFILENAME));
		ofn.lStructSize=sizeof(OPENFILENAME);
		ofn.hwndOwner=hdlg; 
		ofn.hInstance=hinst; 
		ofn.lpstrFilter="�����ļ�(*.*)\0*.*\0"; 
		ofn.nMaxFile=255;	//����ļ�������������
		ofn.lpstrFile=str;	//ʹ����ʱ�ַ���
		return 1;
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case ID_LISTKEY:
			SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_RESETCONTENT,0,0);
			SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)"�ؼ���:");
			for(i=0;i<MAX_KEYWORD;i++)
			{
				wsprintf(str,"[%-2d]%s",i,keytxt[i]);
				SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)str);
			}
			SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)"�����:");
			for(i=0;i<MAX_OPWORDA;i++)
			{
				wsprintf(str,"[%-2d]%c",i,opatxt[i]);
				SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)str);
			}
			for(i=0;i<MAX_OPWORDB;i++)
			{
				wsprintf(str,"[%-2d]%s",MAX_OPWORDA+i,opbtxt[i]);
				SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)str);
			}
			SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)"���:");
			for(i=0;i<MAX_ENDWORD;i++)
			{
				wsprintf(str,"[%-2d]%c",i,eoptxt[i]);
				SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)str);
			}
			SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_RESETCONTENT,0,0);
			SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_ADDSTRING,0,(DWORD)"������Ϣ:");
			for(i=1;i<MAX_ERROR;i++)
			{
				wsprintf(str,"[%-2d]%s",i,errtxt[i]);
				SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_ADDSTRING,0,(DWORD)str);
			}
			break;
		case ID_START:
			SetCursor(LoadCursor(NULL,IDC_WAIT));
			SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_RESETCONTENT,0,0);
			SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_RESETCONTENT,0,0);
			GetDlgItemText(hdlg,IDC_INPUT,in,65535);
			if(getsyminfo(in,&s))
				MessageBox(hdlg,"�������ش���!","����",MB_ICONERROR);
			for(i=0,j=0;i<s.num;i++)
			{
				if(s.sym[i].type==TYPE_ERROR)
				{
					j++;
					wsprintf(str,"%-2d(ERROR%d)[line:%d]",i,s.sym[i].id,s.sym[i].line);
					SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)str);
					wsprintf(str,"No.%d ERROR%d[line:%d]:%s:\"%s\"",i,s.sym[i].id,s.sym[i].line,errtxt[s.sym[i].id],s.sym[i].name);
					SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_ADDSTRING,0,(DWORD)str);
				}
				else
				{
					wsprintf(str,"%-2d(%d,%d)%s",i,s.sym[i].type,s.sym[i].id,s.sym[i].name);
					SendDlgItemMessage(hdlg,IDC_OUTPUT,LB_ADDSTRING,0,(DWORD)str);
				}
			}
			wsprintf(str,"%d Symbol(s) Found.",s.num-j);
			SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_ADDSTRING,0,(DWORD)str);
			wsprintf(str,"%d Error(s) Found.",j);
			SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_ADDSTRING,0,(DWORD)str);
			SetCursor(LoadCursor(NULL,IDC_ARROW));
			break;
		case ID_OPEN:
			ofn.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
			ofn.lpstrTitle="��Դ�����ļ�...";
			str[0]=0;				//�޳�ʼ�ļ���
			if(!GetOpenFileName(&ofn)) break;
			str[255]=0;				//��ֹ���
			fp=fopen(ofn.lpstrFile,"rb");
			if(!fp)
				MessageBox(hdlg,str,"�޷����ļ�!",MB_ICONERROR);
			else
			{
				fseek(fp,0,SEEK_END);
				i=ftell(fp);			//ȡ�ļ�����
				fseek(fp,0,SEEK_SET);
				if(i>65535)
					MessageBox(hdlg,"�ļ�̫��(>=64K)!","����",MB_ICONERROR);
				else
				{
					fread(in,1,i,fp);
					in[i]=0;			//��ֹ���
					SetDlgItemText(hdlg,IDC_INPUT,in);
				}
				fclose(fp);
			}
			break;
		case ID_SAVE:
			ofn.Flags=OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY;
			ofn.lpstrTitle="���������ļ�...";
			str[0]=0;
			if(!GetSaveFileName(&ofn)) break;
			str[255]=0;
			fp=fopen(ofn.lpstrFile,"wb");
			if(!fp)
				MessageBox(hdlg,str,"�޷����ļ�!",MB_ICONERROR);
			else
			{
				SetDlgItemText(hdlg,IDC_INPUT,in);
				for(i=0,j=0;i<s.num;i++)
				{
					if(s.sym[i].type==TYPE_ERROR)
					{
						fprintf(fp,"%-2d(ERROR%d)[line:%d]:%s:\"%s\"\r\n",i,s.sym[i].id,s.sym[i].line,errtxt[s.sym[i].id],s.sym[i].name);
						j++;
					}
					else
						fprintf(fp,"%-2d(%d,%d)%s\r\n",i,s.sym[i].type,s.sym[i].id,s.sym[i].name);
				}
				fprintf(fp,"\r\n%d Symbol(s) Found.",s.num-j);
				fprintf(fp,"\r\n%d Error(s) Found.\r\n",j);
				fclose(fp);
				SendDlgItemMessage(hdlg,IDC_ERRPUT,LB_ADDSTRING,0,(DWORD)"File Saved.");
			}
			break;
		case ID_ABOUT:
			MessageBox(hdlg,"�ʷ�������\n����:����","����",NULL);
			break;
		}
		return 1;
	case WM_CLOSE:
		EndDialog(hdlg,0);
	}
	return 0;
}
