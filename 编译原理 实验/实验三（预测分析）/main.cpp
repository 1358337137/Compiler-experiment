#include "initialForm.h"

int main()
{
	initialMap();
	cout << "��������Ҫ�������ַ��������س���ʼ������" << endl;
	cin >> input;//���봮����input��
	input[input.length()] = '$';//�����봮β����Ϊ'$'
	Stack.push('$');//��ʼ��ջ
	Stack.push('E');
	X = Stack.top();//��ջ��Ԫ�ظ�ֵ��X
	while (X != '$') {
		a = input[index];//a�ǵ�ǰinput��ָ��ָ���Ԫ��
		x = notTerSym[X];//x��Ӧ��Ԥ����ʽ��һά����
		y = terSym[a];//a��Ӧ��Ԥ����ʽ�Ķ�ά����
		if (X == a) {//X����input��ָ��ָ���Ԫ��
			Stack.pop();
			index++;
		}
		else if (isTerSym(X)) {//X��һ���ս��
			cout <<"ջ���ַ�"<<X<<"�����봮��"<<index+1<< "���ַ�'"<<a<<"'��ƥ��" << endl;
			break;
		}
		else if (form[x][y].empty()) {//Ԥ���������ƥ�䵽һ��error��
			cout <<"ƥ�����봮�е�"<<index+1<<"���ַ�'"<<a<<"'ʱ��������" << endl;
			break;
		}
		else {//��Ԥ����������ҵ���ƥ��Ĳ���ʽ
			cout << "ƥ�� " << X << "->" << form[x][y] << endl;
			Stack.pop();
			
			if (form[x][y] == "#") {//�������ʽ��X->#
				//����Ҫѹ��ջStack
			}
			else {
				for (int i = form[x][y].length()-1; i >= 0; i--) {//������ʽ�Ҳ�����ѹ��ջ
					Stack.push(form[x][y][i]);
				}
			}
		}
		X = Stack.top();//X���¸�ֵΪջ��Ԫ��
	}
	if (index == input.length()) cout << "�����ɹ����˱��ʽ��ȷ" << endl;
	else cout << "����ʧ�ܣ��˱��ʽ����" << endl;
	cout << "\n���س��˳�....." << endl;
	cin.get();
	cin.get();
	return 0;
}