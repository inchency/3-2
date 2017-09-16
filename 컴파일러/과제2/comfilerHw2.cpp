#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

void put_table(int **arr, int m, int n);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	string terminals, nonterminals, finalStates, temp; // temp�� vector road�� ������ ���پ� �������ִ� �ӽú���
	vector<string> road;
	int states, symbols; // ������ states�� ����, symbols�� ����
	getline(instream, terminals); // = ���� index�� 10����
	symbols = terminals.length() - 10; // ������ ����
	getline(instream, nonterminals); // = ���� index�� 13����
	states = nonterminals.length() - 13; // ������ ����
	getline(instream, finalStates); // 13����~ ������
	for (int i = 0; i < states; i++) {
		getline(instream, temp);
		road.push_back(temp);
	}
	instream.close();
	cout << "Terminals = ";
	for (int i = 10; i < terminals.length(); i++)
		cout << terminals[i] << " ";
	cout << endl;
	cout << "Nonterminals = ";
	for (int i = 13; i < nonterminals.length(); i++)
		cout << nonterminals[i] << " ";
	cout << endl;
	cout << "Final states = ";
	for (int i = 13; i < finalStates.length(); i++)
		cout << finalStates[i] << " ";
	cout << endl;
	cout << "input.txt���� ���� ������ �迭" << endl;

	for (int i = 0; i < states; i++) {
		for (int j = 0; j < symbols * 2 + 1; j++) {
			cout << road[i][j];
		}
		cout << endl;
	}

	int **arr; // 2���� �迭 ���� �Ҵ�
	arr = (int**)malloc(sizeof(int*) * states);
	for (int i = 0; i < states; i++) {
		arr[i] = (int*)malloc(sizeof(int) * symbols - 1);
	}

	for (int i = 0; i < states; i++) {
		for (int j = 2; j < symbols * 2 + 1; j += 2) {
			for (int k = 13; k < nonterminals.length(); k++) { // ���ڸ� ���ڷ� ����
				if (road[i][j] == '_') {
					arr[i][(j - 1) / 2] = -1;
					break;
				}
				else if (road[i][j] == nonterminals[k]) {
					arr[i][(j - 1) / 2] = k - 13;
					break;
				}
			}
		}
	}
	cout << "�������¸� ���ڷ� ���� ��Ų ��\n";
	for (int i = 0; i < states; i++) {
		for (int j = 0; j < symbols; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	ofstream outstream("st_tab.h");
	outstream << "#define STATES " << states << "\n";
	outstream << "#define SYMBOLS " << symbols;
	outstream << "\n\n" << "int ST_TAB[STATES][SYMBOLS] = {\n";
	for (int i = 0; i < states; i++) {
		outstream << "{ ";
		for (int j = 0; j < symbols; j++) {
			if (j != symbols - 1)
				outstream << arr[i][j] << ", ";
			else {
				if (i != states - 1)
					outstream << arr[i][j] << " },";
				else
					outstream << arr[i][j] << " }";
			}
		}
		outstream << "\n";
	}
	outstream << "};";
	outstream.close();

	// ���⼭���� �������� �������ֽ� �ҽ� ����
	/*
	Simple DFA recognition program.
	*/
		int ch;   /* input symbol */
		int cur_state = 0;   /* start state */

		put_table(arr, states, symbols);

	
		vector<char>fs; // finalStates���� �������� ����
		for (int i = 13; i < finalStates.length(); i++) {
			for (int j = 13; j < nonterminals.length(); j++) {
				if (finalStates[i] == nonterminals[j])
					fs.push_back(j - 13);
			}
		}
		cout << "��θ� �Է��ϼ��� (0~" << symbols-1 << " ������ ���� ���� ����)\n";
		ch = getchar(); // �Է� ����
		while (ch != '\n') {
			cur_state = arr[cur_state][ch - '0'];
			if (cur_state == -1) { puts("FAIL"); return 0; }
			ch = getchar();
		}
		bool flag = false;
		for (int i = 0; i < fs.size(); i++) {
			if (cur_state == fs[i]) 
				flag = true;	/* final states is ok*/					
		}
		if(flag)
			puts("OK");
		else
			puts("FAIL");
	

	return 0;
}
void put_table(int **tab, int m, int n)
{
	int i;

	puts("State Transition Table");
	for (int i = 0; i < n; i++)
		cout << "\t" << i;
	cout << endl;
	for (i = 0; i < m; i++) {
		printf("%c\t", 'A' + i);
		for (int j = 0; j < n; j++) {
			if ('A' + tab[i][j] == '@')
				printf("_\t");
			else
				printf("%c\t", 'A' + tab[i][j]);
		}
		cout << endl;
	}
}
