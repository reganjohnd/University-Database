#include "mechanics.h"

int mechanics::count_students()
{
	student_count = 0;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);

	query = "SELECT * FROM student";
	q = query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);

	while (row = mysql_fetch_row(res))
	{
		student_count++;
	}
	return student_count;
}