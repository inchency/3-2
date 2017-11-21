#include <iostream>
#include <fstream>

using namespace std;

int partition(int *a, int low, int high);
void qqsort(int *v, int low, int high);

int main() {
	ifstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "input.txt를 열 수 없습니다." << endl;
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
// pivot을 잡을 때 첫값, 중간값, 끝값중에 중간값 크기의 크기를 pivot으로 잡는다.
int partition(int *a, int low, int high) {
	int i, j, temp, index;
	int pivot, pivotPos, tmp;
	int first, middle, last, max, min, middleValue; // middleValue는 세 중에서의 중간값
	if (high - low > 1) { // 비교할 수가 세개 이상 일 때
		first = a[low];  middle = a[(low + high) / 2]; last = a[high]; // pivot을 잡기위해 첫값, 중간값, 끝값을 잡는다.
		max = first >= middle ? (first >= last ? first : last) : (middle >= last ? middle : last); // 최대값 찾기
		min = first <= middle ? (first <= last ? first : last) : (middle <= last ? middle : last); // 최소값 찾기
																								   // 값이 중간인 값 찾기
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
		else // 중복되는 수가 있을 경우
			index = low; // 그냥 index는 low값으로 해준다.
		temp = a[low]; a[low] = a[index]; a[index] = temp; // 찾은 middleValue값을 맨 앞으로 보내서 서로 값을 스왑함
	}
	// 만약 비교할 수가 세개 미만이라면 스왑하는 과정 없이 그냥 pivot은 첫번 째 값으로 정한다.
	pivot = a[low]; // pivot 할당
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