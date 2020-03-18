#include "attendance.h"

string attendance::date, attendance::att_status, attendance::tmp_student_name, attendance::module_code, attendance::student_id;
vector<string> attendance::vs_student_name, attendance::vs_student_id, vs_date, vs_att_status, vs_module_code;
vector<int> attendance::vi_student_id;
int attendance::count_it{}, attendance::count_internal{};

int attendance::qstate;
MYSQL* attendance::conn;
MYSQL_ROW attendance::row;
MYSQL_RES* attendance::res;
string attendance::query;
const char* attendance::q;

void attendance::take_att()
{

	string att_status, present, tmp_student_name, module_code, student_id;
	vector<string> vs_student_name, vs_student_id;
	vector<int> vi_student_id;
	int count_it, count_internal;

	count_it = 0;
	count_internal = 0;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	puts("Date (dd/mm/yyyy): ");
	cin.ignore();
	getline(cin, date);

	puts("Module Code: ");
	//cin.ignore();
	getline(cin, module_code);

	query = "SELECT * FROM student_modules WHERE module_code = '" + module_code + "'";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);

	while (row = mysql_fetch_row(res))
	{
		vs_student_id.push_back(row[1]);
		//student_name.push_back(row[1]);
		count_internal++;
		//cout << vs_student_id[count_internal - 1];
		//system("pause");
	}
	mysql_free_result(res);

	for (int i = 0; i < count_internal; i++)
	{
		query = "SELECT student_name FROM student WHERE student_number = " + vs_student_id[i] + "";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			tmp_student_name = row[0];
		}

		cout << tmp_student_name << ": ";
		//system("pause");
		getline(cin, att_status);

		if (att_status == "a" || att_status == "A" || att_status == "h" || att_status == "H")
		{
			//cout << date << endl << vs_student_id[i] << endl << module_code << endl << present;
			//system("pause");
			query = "INSERT INTO attendance (date, student_number, module_code, att_status) VALUES ('" + date + "', '" + vs_student_id[i] + "', '" + module_code + "', '" + att_status + "')";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			count_it++;
		}
		else if (att_status != "a" || att_status != "A" || att_status != "h" || att_status != "H")
		{
			puts("Please enter a valid character!");
			take_att_err(count_it, count_internal);
			return;
		}
	}

}

void attendance::take_att_err(int x, int y)
{
	for (static int i = x; i < y; i++)
	{
		//cout << i << endl << vs_student_id[i];
		//system("pause");
		mysql_free_result(res);

		query = "SELECT student_name FROM student WHERE student_number = " + vs_student_id[i] + "";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			tmp_student_name = row[0];
		}

		cout << tmp_student_name << ": ";
		//system("pause");
		getline(cin, att_status);

		//cout << i << endl;
		//system("pause");

		if (att_status == "a" || att_status == "A" || att_status == "h" || att_status == "H")
		{
			query = "INSERT INTO attendance (date, student_number, module_code, att_status) VALUES ('" + date + "', '" + vs_student_id[i] + "', " + module_code + ", '" + att_status + "')";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			count_it++;
		}
		else if (att_status != "a" || att_status != "A" || att_status != "h" || att_status != "H")
		{
			puts("Please enter a valid character!");
			take_att_err(count_it, count_internal);
		}
	}
	mysql_free_result(res);
}

void attendance::export_att()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	query = "SELECT * FROM attendance";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);

	while (row = mysql_fetch_row(res))
	{
		vs_date.push_back(row[1]);
		vs_student_id.push_back(row[2]);
		vs_module_code.push_back(row[3]);
		vs_att_status.push_back(row[4]);
	}

	ofstream output;
	output.open("C:/Dev/attendance.txt");

	for(int i = 0; i < vs_date.size(); i++)
	{
		output << vs_date[i] << "," << vs_student_id[i] << "," << vs_module_code[i] << "," << vs_att_status[i] << endl;
	}
	output.close();
	mysql_free_result(res);
}