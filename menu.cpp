#include "menu.h"
#include "attendance.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <mysql.h>

using namespace std;

void menu::mainmenu()
{
	

	while(1)
	{
		system("cls");

		static MYSQL* conn;
		int select;
		vector<string> modes{ {"ATTENDANCE"}, { "STUDENTS" }, { "MODULES" } };

		gotoxy(30, 10);
		puts("*******************************************************"); //55
		gotoxy(45, 8);
		puts("STUDENT DATABASE SYSTEM");
		gotoxy(44, 6);
		puts("UNIVERSITY OF DANIELS TOWN");

		for (int i = 0; i < modes.size(); i++)
		{
			gotoxy(50, (12 + i));
			cout << i + 1 << " -> " << modes[i];
		}

		cin >> select;
		switch (select)
		{
		case 1:
			//conn = mysql_init(0);
			//conn = mysql_real_connect(conn, "localhost", "root", "ReganjohnD1", "student_database", 3306, NULL, 0);
			attendance::take_att();
			break;

		case 2:

			break;

		case 3:

			break;
		}
	}
}