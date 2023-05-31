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

//����ݽ�����������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//�˵�����
	void show_Menu();

	//����ѡ�� ����   12��
	vector<int>v1;

	//��һ�ֽ�������  6��
	vector<int>v2;

	//ʤ��ǰ��������  3��
	vector<int>vVictory;

	//��ű�� �Լ���Ӧ�� ����ѡ��
	map<int, Speaker>m_speaker;

	//��¼��������
	int index;

	//����ѡ��
	void creatSpeaker();

	//��ʼ���� �����Ƴ���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//�ļ�Ϊ�ձ�־
	bool fileIsEmpty;

	//�����¼
	map<int, vector<string>>m_Record;

	//��ʾ����÷�
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//��ʼ������
	void initSpeech();

	//�˳�����
	void exitSystem();

	//��������
	~SpeechManager();
};