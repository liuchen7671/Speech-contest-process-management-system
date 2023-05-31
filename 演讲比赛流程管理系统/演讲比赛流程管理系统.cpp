#include"speechManager.h"
#include<ctime>

int main() {
	//随机数种子
	srand((unsigned)time(NULL));

	//创建管理类对象
	SpeechManager sm;
	//保存用户选择
	int choice = 0;

	//测试12名选手创建
	//for (map<int, Speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first << " 选手姓名：" << it->second.name << " 选手分数：" << it->second.score[0] << endl;
	//}
	

	while (true)
	{
		//菜单界面
		sm.show_Menu(); 

		cout << "请输入您的选择" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3://清空记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}

	}

	system("pause");

	return 0;
}