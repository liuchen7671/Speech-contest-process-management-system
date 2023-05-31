#include"speechManager.h"



//构造函数
SpeechManager::SpeechManager()
{
	//初始化属性
	this->initSpeech();

	//创建12名选手
	this->creatSpeaker();

	//加载往届记录
	this->loadRecord();
}


//菜单界面
void SpeechManager::show_Menu()
{
	cout << "----------------------------" << endl;
	cout << "----- 欢迎参加演讲比赛 -----" << endl;
	cout << "----- 1、开始演讲比赛 ------" << endl;
	cout << "----- 2、查看往届记录 ------" << endl;
	cout << "----- 3、清空比赛记录 ------" << endl;
	cout << "----- 0、退出比赛程序 ------" << endl;
	cout << "----------------------------" << endl;

}

//初始化属性
void SpeechManager::initSpeech()
{
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	//初始化比赛轮数
	this->index = 1;
	//初始化记录容器
	this->m_Record.clear();

}

//创建选手
void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0.0;//初始化数组
		}

		//12名选手编号
		this->v1.push_back(i + 10001);

		//选手编号 以及对应的选手 存放的map容器中
		this->m_speaker.insert(make_pair(i + 10001, sp));

	}

}

//开始比赛
void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	this->speechDraw();

	//2、比赛
	speechContest();

	//3、显示晋级结果
	this->showScore();

	//第二轮比赛
	this->index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数到文件中
	this->saveRecord();

	//重置比赛，获取记录
		//初始化属性
	this->initSpeech();

	//创建12名选手
	this->creatSpeaker();

	//加载往届记录
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");

}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第 << " << this->index << "轮 >> 选手正在抽签" << endl;
	cout << "----------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else
	{
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
	}
	cout << endl;
	cout << "----------------------------" << endl;
	system("pause");
}

//比赛
void SpeechManager::speechContest()
{
	cout << "------第" << this->index << "轮比赛正式开始------" << endl;

	//准备临时容器存放小组成绩
	multimap<double, int, greater<double>>groupScore;

	int num = 0;//记录人员个数 6人一组

	vector<int>v_Src;//比赛选手的容器
	if (this->index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  //600~1000
			//cout << score << "\t";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front();//去除最高分
		d.pop_back();//去除最低分

		double sum = accumulate(d.begin(), d.end(), 0);//总分

		double avg = sum / (double)d.size();//强转成小数 //平均分

		//打印平均分
		//cout << "编号：" << *it << " 姓名：" << this->m_speaker[*it].name << "获取平均分: " << avg << endl;

		//将平均分放入map容器里
		//it里存放的是编号，之前map容器里key值就是编号，用编号访问每个人的分数
		this->m_speaker[*it].score[this->index - 1] = avg;

		//将打分数据放入到临时小组容器中
		groupScore.insert(pair<double, int>(avg, *it));//key是得分，value是选手的编、
		//每六人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组的比赛名次如下:" << endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end();it++)
			{
				cout << "编号: " << it->second << " 姓名:" << this->m_speaker[it->second].name << " 平均分：" << this->m_speaker[it->second].score[this->index - 1] << endl;
			}

			//获取前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
			}

			groupScore.clear();//小组容器清空
			cout << endl;
		}


	}


	cout << "------第" << this->index << "轮比赛完毕！------" << endl;
	system("pause");

}

//显示比赛结果
void SpeechManager::showScore()
{
	cout << "------第" << this->index << "轮晋级选手如下: ------" << endl;

	vector<int>v;
	if (this->index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名：" << this->m_speaker[*it].name << " 得分：" << this->m_speaker[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();

}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用追加的方式写文件 ---写文件

	//将每个人数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_speaker[*it].score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已保存" << endl;

	//有记录了，文件不为空
	this->fileIsEmpty = false;

}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//输入流对象 读取文件

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在! " << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空! " << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);//读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs>>data)
	{
		//10002,86.375,10009,81,10010,78,
		
		vector<string>v;//存放6个string字符串

		int pos = -1;//查到","位置的变量
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//没有找到情况
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;

		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	//for (map<int,vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	//{
	//	cout << "第" << it->first + 1 << "届冠军编号：" << it->second[0] << " 分数:" << it->second[1] << endl;
	//}

}

//显示往届得分
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或记录为空" << endl;
	}
	for (int i = 0; i < m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届" <<
			"冠军编号: " << this->m_Record[i][0] << " 得分: " << this->m_Record[i][1] << " "
			"亚军编号: " << this->m_Record[i][2] << " 得分: " << this->m_Record[i][3] << " "
			"季军编号: " << this->m_Record[i][4] << " 得分: " << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");

}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空?" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.clear();

		//初始化属性
		this->initSpeech();

		//创建12名选手
		this->creatSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功" << endl;

		system("pause");
		system("cls");
	}

	system("pause");
	system("cls");
}

//退出功能
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);

}


//析构函数
SpeechManager::~SpeechManager()
{

}