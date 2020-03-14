#include "attendance.h"
#include "mechanics.h"

void attendance::take_att()
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	const char* q = "SELECT * FROM student";
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);

	while (row = mysql_fetch_row(res))
	{
		vs_student_id.push_back(row[0]);
		student_name.push_back(row[1]);
	}
	mysql_free_result(res);

	puts("Date (dd/mm/yyyy): ");
	cin.ignore();
	getline(cin, date);

	puts("Module Code: ");
	//cin.ignore();
	getline(cin,module_code);

	count_it = 0;
	for(int i = 0; i < mechanics::count_students(); i++)
	{
		cout << student_name[i]<<": ";
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
			take_att_err(count_it,mechanics::count_students());
			return;
		}
	}


}

void attendance::take_att_err(int x, int y)
{
	for (static int i = x; i < y ; i++)
	{
		cout << i << endl;
		system("pause");
		cout << student_name[i] << ": ";
		getline(cin, present);

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
			take_att_err(count_it, mechanics::count_students());
		}
	}
	mysql_free_result(res);
}