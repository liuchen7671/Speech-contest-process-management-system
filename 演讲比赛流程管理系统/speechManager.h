#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include"speaker.h"
#include<map>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<fstream>

//设计演讲比赛管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//菜单界面
	void show_Menu();

	//比赛选手 容器   12人
	vector<int>v1;

	//第一轮晋级容器  6人
	vector<int>v2;

	//胜利前三名容器  3人
	vector<int>vVictory;

	//存放编号 以及对应的 具体选手
	map<int, Speaker>m_speaker;

	//记录比赛轮数
	int index;

	//创建选手
	void creatSpeaker();

	//开始比赛 主控制程序
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//文件为空标志
	bool fileIsEmpty;

	//往届记录
	map<int, vector<string>>m_Record;

	//显示往届得分
	void showRecord();

	//清空记录
	void clearRecord();

	//初始化属性
	void initSpeech();

	//退出功能
	void exitSystem();

	//析构函数
	~SpeechManager();
};