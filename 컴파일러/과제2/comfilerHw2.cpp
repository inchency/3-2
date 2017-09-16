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
		cout << "input.txt를 열 수 없습니다." << endl;
		return -1;
	}
	string terminals, nonterminals, finalStates, temp; // temp는 vector road에 넣을때 한줄씩 저장해주는 임시변수
	vector<string> road;
	int states, symbols; // 각각은 states의 갯수, symbols의 갯수
	getline(instream, terminals); // = 다음 index가 10부터
	symbols = terminals.length() - 10; // 가로의 길이
	getline(instream, nonterminals); // = 다음 index가 13부터
	states = nonterminals.length() - 13; // 세로의 길이
	getline(instream, finalStates); // 13부터~ 끝까지
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
	cout << "input.txt에서 받은 기존의 배열" << endl;

	for (int i = 0; i < states; i++) {
		for (int j = 0; j < symbols * 2 + 1; j++) {
			cout << road[i][j];
		}
		cout << endl;
	}

	int **arr; // 2차원 배열 동적 할당
	arr = (int**)malloc(sizeof(int*) * states);
	for (int i = 0; i < states; i++) {
		arr[i] = (int*)malloc(sizeof(int) * symbols - 1);
	}

	for (int i = 0; i < states; i++) {
		for (int j = 2; j < symbols * 2 + 1; j += 2) {
			for (int k = 13; k < nonterminals.length(); k++) { // 문자를 숫자로 맵핑
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
	cout << "문자형태를 숫자로 맵핑 시킨 후\n";
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

	// 여기서부터 교수님이 제공해주신 소스 수정
	/*
	Simple DFA recognition program.
	*/
		int ch;   /* input symbol */
		int cur_state = 0;   /* start state */

		put_table(arr, states, symbols);

	
		vector<char>fs; // finalStates만을 저장해줄 벡터
		for (int i = 13; i < finalStates.length(); i++) {
			for (int j = 13; j < nonterminals.length(); j++) {
				if (finalStates[i] == nonterminals[j])
					fs.push_back(j - 13);
			}
		}
		cout << "경로를 입력하세요 (0~" << symbols-1 << " 사이의 수를 띄어쓰기 없이)\n";
		ch = getchar(); // 입력 받음
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
