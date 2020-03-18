#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mysql.h>
#include <vector>
#include "stdio.h"

#include "mysql_rj.h"
#include "mechanics.h"

using namespace std;


class attendance
{
private:
	static string date, att_status, present, tmp_student_name, module_code, student_id;
	static vector<string> vs_student_name, vs_student_id;
	static vector<int> vi_student_id;
	static int count_it, count_internal;

	static int qstate;
	static MYSQL* conn;
	static MYSQL_ROW row;
	static MYSQL_RES* res;
	static string query;
	const static char* q;

public:
	static void take_att();

	static void take_att_err(int x, int y);

	static void export_att();
};