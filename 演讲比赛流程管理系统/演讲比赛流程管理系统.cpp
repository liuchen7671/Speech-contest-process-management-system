#include"speechManager.h"
#include<ctime>

int main() {
	//���������
	srand((unsigned)time(NULL));

	//�������������
	SpeechManager sm;
	//�����û�ѡ��
	int choice = 0;

	//����12��ѡ�ִ���
	//for (map<int, Speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first << " ѡ��������" << it->second.name << " ѡ�ַ�����" << it->second.score[0] << endl;
	//}
	

	while (true)
	{
		//�˵�����
		sm.show_Menu(); 

		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");//����
			break;
		}

	}

	system("pause");

	return 0;
}