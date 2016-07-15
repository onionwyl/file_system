#include"header.h"
extern vector<cataLog> catalog;
extern vector<int> path;
extern vector<User> user;
extern int username_id;

bool compare_arry(vector<int> a, vector<int> b);


void l(){

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout.setf(ios::left);
	cout << setw(15) << "name" << setw(10) << "type" << setw(25) << "edit time" << setw(10) << "user" << setw(10) << "size" << endl;
	HANDLE hCON = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCON, (7 % 16) | (0 % 16 * 16));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	for (unsigned int i = 1; i < catalog.size(); i++){
		if (compare_arry(catalog[i].info.path, path)){
			if (catalog[i].info.share == 1 || catalog[i].info.user == username_id || username_id == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				if (catalog[i].info.type == 1){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				}
				cout.setf(ios::left);
				cout << setw(15) << catalog[i].info.name << setw(10) << catalog[i].info.ftype << setw(25) << catalog[i].info.last_edit_time << setw(10) << user[catalog[i].info.user].username << setw(10) << catalog[i].info.size << endl;
			}
		}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		}

	}

	void info(){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		cout.setf(ios::left);
		cout << setw(15) << "name" << setw(10) << "type" << setw(10) << "user" << setw(10) << "size" << setw(25) << "create time" << endl;
		cout << setw(15) << "  " << setw(10) << "share" << setw(10) << "writeable" << setw(10) << "readable" << setw(25) << "edit time" << endl;
		HANDLE hCON = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hCON, (7 % 16) | (0 % 16 * 16));
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		for (unsigned int i = 1; i < catalog.size(); i++){
			if (compare_arry(catalog[i].info.path, path)){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				if (catalog[i].info.type == 1){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				}
				cout.setf(ios::left);
				cout << setw(15) << catalog[i].info.name << setw(10) << catalog[i].info.ftype << setw(10) << user[catalog[i].info.user].username << setw(10) << catalog[i].info.size << setw(25) << catalog[i].info.create_time << endl;
				cout << setw(15) << "  " << setw(10) << catalog[i].info.share << setw(10) << catalog[i].info.writeable << setw(10) << catalog[i].info.readable << setw(25) << catalog[i].info.last_edit_time << endl;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		}

	}



