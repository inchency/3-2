#include "dbconnect.h"
#include "bevereages.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>//setw

using namespace std;

void menu();
void insert();
void run();
void print_db(int fields);
void clear_db(char query[]);
void exit();
void default();
int loading(int loadingTimeStart, int loadingTimeEnd, int plus); // �ε� �뷱�� �˰��� �����ֱ� �� �ε��ϴ� ��� ��� �Լ� (recursive �ϰ� ����)

int main() {
	db_con();
	menu();
	return 0;
}
void menu() {
	system("cls");
	cout << "-- MENU --" << endl;
	cout << "1. �����ֹ��ϱ�" << endl << "2. �ε� �뷱�� �˰��� ������ ����" << endl << "3. �ֹ�Ȯ��" << endl << "4. �ֹ� �ʱ�ȭ" << endl << "5. ���α׷� ����" << endl;
	cout << "�޴��� �ش��ϴ� ���ڸ� �Է��ϼ���." << endl;
	char menu;
	cin >> menu;
	switch (menu) {
	case '1': insert(); break;
	case '2': run(); break;
	case '3': print_db(0); break;
	case '4': char query[255]; clear_db(query); break;
	case '5': exit(); break;
	default: default();
	}
}
void insert() {
	char name[20];
	char query[255];
	int sel = 0, count = 0, time = 0, ordertime = 0, fields = 0;
	int no = 1;
	count_Instance(&no);
	system("cls");
	int cafeKindNum = 10; // <- ī�信�� �Ĵ� ���� ���� ���� (���Ҽ�����)
	int spaceSize = 50; // ��Ģ������ ��� ���� �����ϱ� ����
	char *kindOfDrink[10] = { "espresso", "americano", "cafelatte", "cappuccino", "cafemocha", "caramelmacchiato", "hotchoco", "greentealatte", "sweetpotatolatte", "herbtea" };
	int kindOfDrinkTime[10] = { 3,3,4,5,6,6,7,7,7,10 };
	cout << "---------------------------------------------- �ֹ�ǥ----------------------------------------------" << endl;
	cout << " ��  ����� ";
	for (int i = 0; i < spaceSize - 15; i++)
		cout << " ";
	cout << "�����µ� �ɸ��½ð�              ��" << endl;
	for (int i = 0; i < cafeKindNum; i++) {
		spaceSize = 50;
		cout << setw(2) << i + 1 << ". ";
		cout << kindOfDrink[i];
		int len = strlen(kindOfDrink[i]);
		for (int j = 0; j < len; j++)
			spaceSize--;
		for (int j = 0; j < spaceSize; j++)
			cout << " ";
		cout << kindOfDrinkTime[i];
		spaceSize = 50;
		if (kindOfDrinkTime[i] / 1000 >= 1)
			spaceSize -= 10;
		else if (kindOfDrinkTime[i] / 100 >= 1)
			spaceSize -= 9;
		else if (kindOfDrinkTime[i] / 10 >= 1)
			spaceSize -= 8;
		else
			spaceSize -= 7;
		for (int j = 0; j < spaceSize; j++)
			cout << " ";
		if (i % 2 == 0)
			cout << "�� ";
		else
			cout << "�� ";
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------" << endl;

	insert_db(name, query, &no, count, time, ordertime);
	menu();
}

void run() {
	system("cls");
	cout << "�й�Ǵ� ������ �ǽð����� �����帱���?\nN�� �����ø� �ֹ���Ͼ翡 ����� �ε� �ð��� ��ģ �� �ѹ��� ��� ��µ˴ϴ�. (Y/N)" << endl;
	char realTime;
	cin >> realTime;
	bool selecting;
	if (realTime == 'Y' || realTime == 'y')
		selecting = true;
	else
		selecting = false;

	/*******************Loading**************************/
	if (!selecting) {
		int count = 0;
		MYSQL_RES * cnt = select_db(); // id, name, time, orderTime
		while (row = mysql_fetch_row(cnt))
			count++;
		int loadingTime = 300;
		loadingTime += (count / 10) * 100; // 10���� 1������
		cout << loadingTime;
		// fields�� ������ŭ loadingTime�� �����
		// fields �� ��� ���ڸ� ������ ���� �ε��ð� ���� (100, 1000, 100) ������ 1000ms �ɸ�
		loading(100, loadingTime, 100); // (a,b,c) �� ���� �� loadingTime = (b / a)ms, a = c ���� ��
	}
	/*******************Loading**************************/

	int numOfBar = 3;
	baristar *bar = new baristar[numOfBar]; // �� �ٸ���Ÿ ��ü

	for (int i = 0; i < numOfBar; i++) // �ٸ���Ÿ�� �ɷ��� ����(1�̶�� ���� �ϱ����� �ɸ��� �ð�)
		bar[i].setEff(i + 1);
	MYSQL_RES * res = select_db(); // id, name, time, orderTime
	int fields = mysql_num_fields(res);
	while (row = mysql_fetch_row(res))
	{
		if (selecting)
			Sleep(200);
		beverage *coff = new beverage;
		for (int i = 0; i < fields; i++)
			coff->setItems(atoi(row[0]), row[1], atoi(row[2]), atoi(row[3])); // DB���� �ϳ��� �޾ƿͼ� ������ ��ü

		int min = 9999;// ����ª�� �ð�
		int minWorkBar = 0;

		for (int i = 0; i < numOfBar; i++) { // ���� �ɸ��� �ð��� ª�� �ٸ���Ÿ ã��
			int barNeedTime = coff->getTime() * (bar[i].getEff());
			int barAccumTime = bar[i].getEndOfWork();
			int nowTime = barAccumTime - coff->getOrderTime();
			if (nowTime < 0) nowTime = 0;
			minWorkBar = (min <= (nowTime + barNeedTime) ? minWorkBar : i);
			min = (min <= (nowTime + barNeedTime)) ? min : (nowTime + barNeedTime);
		}
		int accum = bar[minWorkBar].getEndOfWork() + coff->getTime() * (bar[minWorkBar].getEff());
		coff->setStartTime(bar[minWorkBar].getEndOfWork());
		bar[minWorkBar].setEndOfWork(accum);
		coff->setEndTime(accum);
		bar[minWorkBar].MkBever(coff);
		if (selecting) {
			system("cls");
			for (int i = 0; i < 138; i++)
				cout << "-";
			cout << endl;
			for (int i = 0; i < numOfBar; i++) {
				cout << "|";
				for (int j = 0; j < 64; j++)
					cout << " ";
				cout << (char)(i + 'A') << " Baristar (�ɷ� : 1/" << bar[i].getEff() << ")";
				for (int j = 0; j < 49; j++)
					cout << " ";
				cout << "|" << endl;
				bar[i].printBever();
			}
		}
	}
	if (!selecting) {
		system("cls");
		for (int i = 0; i < 138; i++)
			cout << "-";
		cout << endl;
		for (int i = 0; i < numOfBar; i++) {
			cout << "|";
			for (int j = 0; j < 64; j++)
				cout << " ";
			cout << (char)(i + 'A') << " Baristar (�ɷ� : 1/" << bar[i].getEff() << ")";
			for (int j = 0; j < 49; j++)
				cout << " ";
			cout << "|" << endl;
			bar[i].printBever();
		}
	}
	mysql_free_result(res);

	cout << "�ٽ� --MENU--�� ���ư��ðڽ��ϱ�? (Y/N)" << endl;
	char backPage;
	cin >> backPage;
	if (backPage == 'Y' || backPage == 'y') {
		cout << "��� �� --MENU--�� ���ư��ڽ��ϴ�." << endl;
		Sleep(700);
		menu();
	}
	else {
		cout << "�ε� �뷱�� ������ �ٽ� �����帮�ڽ��ϴ�." << endl;
		Sleep(700);
		run();
	}
	menu();
}

void exit() {
	system("cls");
	cout << "������ ���α׷��� �����Ͻðڽ��ϱ�? (Y/N)" << endl;
	char finish;
	cin >> finish;
	if (finish == 'Y' || finish == 'y') {
		cout << "���α׷��� �����մϴ�." << endl;
		exit(1);
	}
	else {
		cout << "�ٽ� �޴��� �����帳�ϴ�." << endl;
		Sleep(700);
		system("cls");
		menu();
	}
}

void default() {
	cout << "MENU�� �ִ� �˸��� ���� ����� �Է��ϼ���." << endl;
	Sleep(1000);
	system("cls");
	menu();
}

int loading(int loadingTimeStart, int loadingTimeEnd, int plus) {
	if (loadingTimeStart == loadingTimeEnd) {
		system("cls");
		cout << "��� �� �ε� �뷱�� �˰����� �̿��Ͽ� �ٸ���Ÿ���� ���� �й�Ǵ� ������ �����帮�ڽ��ϴ�." << endl << endl;
		cout << "��ø� ��ٷ� �ּ���. �ε����Դϴ�. �ֹ���Ͼ翡 ����� �ε� �ð��� �ɸ��ϴ�." << endl;
		for (int i = 0; i < loadingTimeEnd; i += plus)
			cout << "��";
		cout << endl << "COMPLETE!!!" << endl;
		Sleep(700);
		system("cls");
		return 0;
	}
	system("cls");
	cout << "��� �� �ε� �뷱�� �˰����� �̿��Ͽ� �ٸ���Ÿ���� ���� �й�Ǵ� ������ �����帮�ڽ��ϴ�." << endl << endl;
	cout << "��ø� ��ٷ� �ּ���. �ε����Դϴ�. �ֹ���Ͼ翡 ����� �ε� �ð��� �ɸ��ϴ�." << endl;
	for (int i = 0; i < loadingTimeStart; i += plus)
		cout << "��";
	for (int i = loadingTimeStart; i < loadingTimeEnd; i += plus)
		cout << "��";
	Sleep(100);
	return loading(loadingTimeStart + plus, loadingTimeEnd, plus);
}

void clear_db(char query[]) {
	system("cls");
	cout << "SQL�� \'";
	sprintf(query, "delete from cafe;"); // table �� �ٲ�� �ٲ������
	mysql_query(&mysql, query);
	printf("%s", query);
	cout << "\'�� �����մϴ�." << endl;
	Sleep(500);
	cout << endl << "��� �ֹ������� �����Ǿ����ϴ�." << endl;
	cout << "+------+----------+------+------------+" << endl;
	cout << "| ID   | NAME     | TIME | ORDER_TIME |" << endl;
	cout << "+------+----------+------+------------+" << endl;
	cout << "|      |          |      |            |" << endl;
	cout << "+------+----------+------+------------+" << endl;
	Sleep(500);
	cout << "��� �� --MENU--�� ���ư��ڽ��ϴ�." << endl;
	Sleep(1500);
	menu();
}

void print_db(int fields)
{
	system("cls");
	mysql_query(&mysql, "select * from cafe");
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);
	cout << "�ֹ� ���� ����� �����帮�ڽ��ϴ�." << endl;
	Sleep(300);
	cout << "------------------------�ֹ����----------------------------" << endl;
	cout << "ID    |        NAME             |�ɸ��½ð�|  �ֹ��ð�" << endl;
	cout << "------------------------------------------------------------" << endl;
	while (row = mysql_fetch_row(res))
	{
		for (int i = 0; i < fields; i++) {
			if (i == 0)
				cout << " ";
			int spaceSize; // ��Ģ������ ��� ���� �����ϱ� ����
			int rowLen = strlen(row[i]);
			printf("%s", row[i]);
			if (i == 0) {
				spaceSize = 10;
				spaceSize -= rowLen;
			}
			else if (i == 1) {
				spaceSize = 25;
				spaceSize -= rowLen;
			}
			else if (i == 2) {
				spaceSize = 10;
				spaceSize -= rowLen;
			}
			else
				break;
			for (int j = 0; j < spaceSize - 5; j++)
				cout << " ";
			cout << "|";
			for (int j = spaceSize - 5; j < spaceSize; j++)
				cout << " ";
		}
		printf("\n");
	}
	mysql_free_result(res);
	cout << "------------------------------------------------------------" << endl;
	Sleep(500);
	cout << "�ٽ� --MENU--�� ���ư��ðڽ��ϱ�? (Y/N)" << endl;
	char backPage;
	cin >> backPage;
	if (backPage == 'Y' || backPage == 'y') {
		cout << "��� �� --MENU--�� ���ư��ڽ��ϴ�." << endl;
		Sleep(700);
		menu();
	}
	else {
		cout << "�ֹ������ �ٽ� �����帮�ڽ��ϴ�." << endl;
		Sleep(700);
		print_db(0);
	}
	menu();
}