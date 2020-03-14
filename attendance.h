#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include <vector>
using namespace std;

/*
static int qstate;
static MYSQL* conn;
static MYSQL_ROW row;
static MYSQL_RES* res;
*/
static string date, /*query,*/ att_status, present, module_code, student_id;
static vector<string> student_name, vs_student_id;
static vector<int> vi_student_id;
static int count_it;

class attendance
{
public:
	

	static void take_att();
	static void take_att_err(int x, int y);
	//static void export_att();
};