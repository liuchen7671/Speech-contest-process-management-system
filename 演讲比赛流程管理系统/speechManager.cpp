#include"speechManager.h"



//���캯��
SpeechManager::SpeechManager()
{
	//��ʼ������
	this->initSpeech();

	//����12��ѡ��
	this->creatSpeaker();

	//���������¼
	this->loadRecord();
}


//�˵�����
void SpeechManager::show_Menu()
{
	cout << "----------------------------" << endl;
	cout << "----- ��ӭ�μ��ݽ����� -----" << endl;
	cout << "----- 1����ʼ�ݽ����� ------" << endl;
	cout << "----- 2���鿴�����¼ ------" << endl;
	cout << "----- 3����ձ�����¼ ------" << endl;
	cout << "----- 0���˳��������� ------" << endl;
	cout << "----------------------------" << endl;

}

//��ʼ������
void SpeechManager::initSpeech()
{
	//������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	//��ʼ����������
	this->index = 1;
	//��ʼ����¼����
	this->m_Record.clear();

}

//����ѡ��
void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0.0;//��ʼ������
		}

		//12��ѡ�ֱ��
		this->v1.push_back(i + 10001);

		//ѡ�ֱ�� �Լ���Ӧ��ѡ�� ��ŵ�map������
		this->m_speaker.insert(make_pair(i + 10001, sp));

	}

}

//��ʼ����
void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();

	//2������
	speechContest();

	//3����ʾ�������
	this->showScore();

	//�ڶ��ֱ���
	this->index++;
	//1����ǩ
	this->speechDraw();
	//2������
	speechContest();
	//3����ʾ���ս��
	this->showScore();
	//4������������ļ���
	this->saveRecord();

	//���ñ�������ȡ��¼
		//��ʼ������
	this->initSpeech();

	//����12��ѡ��
	this->creatSpeaker();

	//���������¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");

}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "�� << " << this->index << "�� >> ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->index == 1)
	{
		//��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else
	{
		//�ڶ��ֱ���
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

//����
void SpeechManager::speechContest()
{
	cout << "------��" << this->index << "�ֱ�����ʽ��ʼ------" << endl;

	//׼����ʱ�������С��ɼ�
	multimap<double, int, greater<double>>groupScore;

	int num = 0;//��¼��Ա���� 6��һ��

	vector<int>v_Src;//����ѡ�ֵ�����
	if (this->index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  //600~1000
			//cout << score << "\t";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0);//�ܷ�

		double avg = sum / (double)d.size();//ǿת��С�� //ƽ����

		//��ӡƽ����
		//cout << "��ţ�" << *it << " ������" << this->m_speaker[*it].name << "��ȡƽ����: " << avg << endl;

		//��ƽ���ַ���map������
		//it���ŵ��Ǳ�ţ�֮ǰmap������keyֵ���Ǳ�ţ��ñ�ŷ���ÿ���˵ķ���
		this->m_speaker[*it].score[this->index - 1] = avg;

		//��������ݷ��뵽��ʱС��������
		groupScore.insert(pair<double, int>(avg, *it));//key�ǵ÷֣�value��ѡ�ֵıࡢ
		//ÿ����ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��ı�����������:" << endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end();it++)
			{
				cout << "���: " << it->second << " ����:" << this->m_speaker[it->second].name << " ƽ���֣�" << this->m_speaker[it->second].score[this->index - 1] << endl;
			}

			//��ȡǰ����
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

			groupScore.clear();//С���������
			cout << endl;
		}


	}


	cout << "------��" << this->index << "�ֱ�����ϣ�------" << endl;
	system("pause");

}

//��ʾ�������
void SpeechManager::showScore()
{
	cout << "------��" << this->index << "�ֽ���ѡ������: ------" << endl;

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
		cout << "ѡ�ֱ�ţ�" << *it << " ������" << this->m_speaker[*it].name << " �÷֣�" << this->m_speaker[*it].score[this->index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();

}

//�����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӵķ�ʽд�ļ� ---д�ļ�

	//��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_speaker[*it].score[1] << ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();

	cout << "��¼�ѱ���" << endl;

	//�м�¼�ˣ��ļ���Ϊ��
	this->fileIsEmpty = false;

}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//���������� ��ȡ�ļ�

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������! " << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��! " << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch);//��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs>>data)
	{
		//10002,86.375,10009,81,10010,78,
		
		vector<string>v;//���6��string�ַ���

		int pos = -1;//�鵽","λ�õı���
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//û���ҵ����
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
	//	cout << "��" << it->first + 1 << "��ھ���ţ�" << it->second[0] << " ����:" << it->second[1] << endl;
	//}

}

//��ʾ����÷�
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ��" << endl;
	}
	for (int i = 0; i < m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "��" <<
			"�ھ����: " << this->m_Record[i][0] << " �÷�: " << this->m_Record[i][1] << " "
			"�Ǿ����: " << this->m_Record[i][2] << " �÷�: " << this->m_Record[i][3] << " "
			"�������: " << this->m_Record[i][4] << " �÷�: " << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");

}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ�����?" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//��ģʽios::trunc �������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.clear();

		//��ʼ������
		this->initSpeech();

		//����12��ѡ��
		this->creatSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ�" << endl;

		system("pause");
		system("cls");
	}

	system("pause");
	system("cls");
}

//�˳�����
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);

}


//��������
SpeechManager::~SpeechManager()
{

}