#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "mechanics.h"
#include "mysql_rj.h"
#include "mysql.h"
using namespace std;


class student
{
public:

	static string tmp_name, student_id, tmp_modules;
	static int tmp_num_modules;
	static vector<string> v_modules;

	static int qstate;
	static MYSQL* conn;
	static MYSQL_ROW row;
	static MYSQL_RES* res;
	static string query;
	const static char* q;

	static void add_student();
	static void delete_student();
	static void update_student();
	static void view_student();
	//static void view_all_students();
};