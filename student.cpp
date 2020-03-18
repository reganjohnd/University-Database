#include "student.h"

string student::tmp_name, student::student_id, student::tmp_modules;
int student::tmp_num_modules;
vector<string> student::v_modules;

int student::qstate;
MYSQL* student::conn;
MYSQL_ROW student::row;
MYSQL_RES* student::res;
string student::query;
const char* student::q;

void student::add_student()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	puts("Student Name: ");
	getline(cin, tmp_name);
	puts("Student Number: ");
	getline(cin, student_id);

	puts("Number of modules to load: ");
	cin >> tmp_num_modules;
	cin.ignore();

	for (int i = 0; i < tmp_num_modules; i++)
	{
		cout << "Module " << i + 1 << ":";
		getline(cin, tmp_modules);
		v_modules.push_back(tmp_modules);
		cout << v_modules[i];
		system("pause");
	}

	query = "INSERT INTO student (student_number, student_name) VALUES(" + student_id + ", '" + tmp_name + "')";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	mysql_free_result(res);

	for (int i = 0; i < v_modules.size(); i++)
	{
		query = "INSERT INTO student_modules (student_number, module_code) VALUES (" + student_id + ", '" + v_modules[i] + "')";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		res = mysql_store_result(conn);
	}
	mysql_free_result(res);
}

void student::delete_student()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	puts("Student ID: ");
	getline(cin, student_id);
	
	string s_query = "SELECT student_name FROM student WHERE student_number = " + student_id + "";
	const char* s_q = s_query.c_str();
	int s_qstate = mysql_query(conn, s_q);
	MYSQL_RES* s_res = mysql_store_result(conn);
	while(row = mysql_fetch_row(s_res))
		tmp_name = row[0];

	query = "DELETE FROM student_modules WHERE student_number = " + student_id + "";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	mysql_free_result(res);

	query = "DELETE FROM attendance WHERE student_number = " + student_id + "";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	mysql_free_result(res);

	query = "DELETE FROM student WHERE student_number = " + student_id + "";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	
	if (!qstate)
	{
		cout << tmp_name << " was successfully removed from the database!" << endl;
		system("pause");
	}
		
	mysql_free_result(res);
}

void student::view_student()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	puts("Student ID: ");
	getline(cin, student_id);

	query = "SELECT * FROM student WHERE student_number = " + student_id + "";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	while(row = mysql_fetch_row(res))
		tmp_name = row[1];
	cout << tmp_name;
	system("pause");
	mysql_free_result(res);

	query = "SELECT * FROM student_modules WHERE student_number = " + student_id + "";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res))
	{
		v_modules.push_back(row[2]);
	}

	cout << "Name: " << tmp_name << endl << endl;

	for (int i = 0; i < v_modules.size(); i++)
	{
		cout <<"Module "<< i + 1 << ": " << v_modules[i] << endl;
	}
	mysql_free_result(res);
}

void student::update_student()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	puts("student ID: ");
	getline(cin, student_id);
	puts("New name: ");
	getline(cin, tmp_name);

	query = "UPDATE student SET student_name = '"+tmp_name+"' WHERE student_number = "+student_id+"";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
}