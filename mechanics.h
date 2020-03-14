#pragma once
#include <string>
#include <mysql.h>
using namespace std;

static int qstate;
static MYSQL* conn;
static MYSQL_ROW row;
static MYSQL_RES* res;
static string query;
const static char* q;


static int student_count;

class mechanics
{
public:
	

	static int count_students();
};