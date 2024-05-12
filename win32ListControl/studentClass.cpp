#pragma once
#include <iostream>
#include <list>

using namespace std;

struct STUDENT_INFO
{
	char sNumber[9];
	char ssName[20];
	char sAddress[200];
	char sPhoneNumber[15];
	char sEmailAddress[30];

	int nScore[2][2];
};

class CStudent
{
	list<STUDENT_INFO> m_StudentList;

public:
	bool Load();
	bool Save();
	int Find(char* pNumber, STUDENT_INFO* pStudentInfo);
	int Find(char* pNumber);
	bool SetScore(int nIndex, int nGrade, int nTerm, int nScore);
	bool AddStudent(STUDENT_INFO sStudentInfo);
	bool DeleteStudent(int nIndex);
	bool SetStudentInfo(int nIndex, STUDENT_INFO sStudentInfo);
	void SetScoreClear(int nIndex);
public:
	CStudent(void);
	~CStudent(void);

};

int CStudent::Find(char* pNumber)
{
	int nIndex;
	STUDENT_INFO sStudentInfo;
	list<STUDENT_INFO>::iterator;
	for (pos = m_StudentList.begin;)
	{
		if (strcmp(pNumber, po))
	}
}
bool CStudent::Load()
{
	FILE* fp;
	STUDENT_INFO sStudentInfo;

	fp = fopen("student.dat", "rb");
	if (fp != NULL)
	{
		m_StudentList.clear();
		while (!feof(fp))
		{
			fread(&sStudentInfo, sizeof(STUDENT_INFO));
			m_StudentList.push_back(sStudentInfo);
		}
		fclose(fp);
	}
	else { return false; }
}
bool CStudent::Save()
{
	FILE* fp;
	STUDENT_INFO sStudentInfo;
	list<STUDENT_INFO>::iterator;
	fp = fopen("student.dat", "wb");

	for (iter pos = m_StudentList.begin; pos < m_StudentList.end; pos++)
	{
		sStudentInfo = *pos;
		fwrite(&sStudentInfo, sizeof(STUDENT_INFO));
	}
	fclose(fp);
	return true;
}

int CStudent::Find(char* pNumber)
{
	int nIndex;
	STUDENT_INFO sStudentInfo;
	list<STUDENT_INFO>::iterator;
	for (pos = m_StudentList.begin; pos < m_StudentList.end; pos++)
	{
		if (strcmp(pNumber, pos->sNumber))
		{
			sStudentInfo = *pos;
			memcpy(pStudentInfo, &sStudentInfo);
			return nIndex;
		}
	}
}
bool CStudent::SetScore(int nIndex, int nGrade, int nTerm, int nScore)
{

}