#include "attendance.h"
#include "mechanics.h"

void attendance::take_att()
{
	count_it = 0;
	count_internal = 0;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	puts("Date (dd/mm/yyyy): ");
	cin.ignore();
	getline(cin, date);

	puts("Module Code: ");
	//cin.ignore();
	getline(cin,module_code);

	query = "SELECT * FROM student_modules WHERE module_code = " + module_code + "";
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

	

	
	for(int i = 0; i < count_internal; i++)
	{
		query = "SELECT student_name FROM student WHERE student_number = " + vs_student_id[i] + "";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			s_student_name = row[0];
		}

		cout <<s_student_name<<": ";
		//system("pause");
		getline(cin, present);

		if (present == "a" || present == "A" || present == "h" || present == "H")
		{
			//cout << date << endl << vs_student_id[i] << endl << module_code << endl << present;
			//system("pause");
			query = "INSERT INTO attendance (date, student_number, module_code, att_status) VALUES ('" + date + "', '" + vs_student_id[i] + "', " + module_code + ", '" + present + "')";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			count_it++;
		}
		else if (present != "a" || present != "A" || present != "h" || present != "H")
		{
			puts("Please enter a valid character!");
			take_att_err(count_it,count_internal);
			return;
		}
	}


}

void attendance::take_att_err(int x, int y)
{
	
	for (static int i = x; i < y ; i++)
	{
		cout << i << endl << vs_student_id[i];
		system("pause");
		mysql_free_result(res);

		query = "SELECT student_name FROM student WHERE student_number = " + vs_student_id[i] + "";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			s_student_name = row[0];
		}

		cout << s_student_name << ": ";
		//system("pause");
		getline(cin, present);

		//cout << i << endl;
		//system("pause");

		if (present == "a" || present == "A" || present == "h" || present == "H")
		{
			query = "INSERT INTO attendance (date, student_number, module_code, att_status) VALUES ('" + date + "', '" + vs_student_id[i] + "', " + module_code + ", '" + present + "')";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			count_it++;
		}
		else if (present != "a" || present != "A" || present != "h" || present != "H")
		{
			puts("Please enter a valid character!");
			take_att_err(count_it, count_internal);
		}
	}
	mysql_free_result(res);
}