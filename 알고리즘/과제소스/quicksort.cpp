#include <iostream>
#include <fstream>

using namespace std;

int partition(int *a, int low, int high);
void qqsort(int *v, int low, int high);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt�� �� �� �����ϴ�." << endl;
		return -1;
	}
	int cases;
	instream >> cases;
	for (int i = 0; i < cases; i++) {
		int num;
		instream >> num;
		int *ary = new int[num];
		for (int j = 0; j < num; j++)
			instream >> ary[j];
		qqsort(ary, 0, num - 1);
		for (int j = 0; j < num; j++)
			cout << ary[j] << " ";
		cout << endl;
		delete[] ary;
	}
	return 0;
}
// pivot�� ���� �� ù��, �߰���, �����߿� �߰��� ũ���� ũ�⸦ pivot���� ��´�.
int partition(int *a, int low, int high) {
	int i, j, temp, index;
	int pivot, pivotPos, tmp;
	int first, middle, last, max, min, middleValue; // middleValue�� �� �߿����� �߰���
	if (high - low > 1) { // ���� ���� ���� �̻� �� ��
		first = a[low];  middle = a[(low + high) / 2]; last = a[high]; // pivot�� ������� ù��, �߰���, ������ ��´�.
		max = first >= middle ? (first >= last ? first : last) : (middle >= last ? middle : last); // �ִ밪 ã��
		min = first <= middle ? (first <= last ? first : last) : (middle <= last ? middle : last); // �ּҰ� ã��
																								   // ���� �߰��� �� ã��
		if (first != max && first != min) {
			middleValue = first;
			index = low;
		}
		else if (middle != max && middle != min) {
			middleValue = middle;
			index = (low + high) / 2;
		}
		else if (last != max && last != min) {
			middleValue = last;
			index = high;
		}
		else // �ߺ��Ǵ� ���� ���� ���
			index = low; // �׳� index�� low������ ���ش�.
		temp = a[low]; a[low] = a[index]; a[index] = temp; // ã�� middleValue���� �� ������ ������ ���� ���� ������
	}
	// ���� ���� ���� ���� �̸��̶�� �����ϴ� ���� ���� �׳� pivot�� ù�� ° ������ ���Ѵ�.
	pivot = a[low]; // pivot �Ҵ�
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (a[i] < pivot) {
			j++;
			tmp = a[i]; a[i] = a[j]; a[j] = tmp;
		}
	}
	pivotPos = j;
	tmp = a[low]; a[low] = a[pivotPos]; a[pivotPos] = tmp;
	return pivotPos;
}
void qqsort(int *v, int low, int high) {
	int pivotPos;
	if (high > low) {
		pivotPos = partition(v, low, high);
		qqsort(v, low, pivotPos - 1);
		qqsort(v, pivotPos + 1, high);
	}
}