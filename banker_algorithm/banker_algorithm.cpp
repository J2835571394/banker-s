#include<iostream>
#include<vector>
int maxx[4][3];
int allocate[4][3];
int need[4][3];
int request[3];
int current[3];
int safesequence[4];
int p = 4;
int r = 3;

using namespace std;
void input() {//input the information

	for (int i = 0; i < p; i++)
	{
		cout << "plz input the max vertex:"<<endl;
		for (int j = 0; j < r; j++) {
			cin >> maxx[i][j];
		}
		cout << "plz input the allocate vertex:" << endl;
		for (int j = 0; j < r; j++) {
			cin >> allocate[i][j];
		}
		for (int j = 0; j < r; j++) {
			need[i][j]=maxx[i][j]-allocate[i][j];
		}
	}
	cout << "plz input the current avaliable vertex:" << endl;
	for (int j = 0; j < r; j++) {
		cin >> current[j];
	}
}

int compare(int m[], int n[]) {
	for (int i = 0; i < r; i++) {
		if (m[i] < n[i]) {
			return 0;
		}
	}
	return 1;
}

int ifsafe() {
	int m = 0;
	int finish[4];//if process is finished.
	int work[3];//to sign the avaliable resource in each time
	for (int i = 0; i < p; i++) {
		finish[i] = 0;
	}
	for (int i = 0; i < r; i++) {
		work[i] = current[i];
	}
	for (int k = 0; k < p; k++) {
		for (int i = 0; i < p; i++) {
			if (finish[i] == 0) {
				if (compare(work, need[i])) {
					finish[i] = 1;
					safesequence[k] = i + 1;
					for (int j = 0; j < r; j++) {
						work[j] = work[j] + allocate[i][j];
					}
					break;
				}
			}
			else { continue; }
		}
	}
	for (int i = 0; i < p; i++) {
		if (finish[i] == 0) {
			return 1;
		}
	}
	return 0;
}

void requestest(int n) {
	cout << "plz input the requirement!" << endl;
	for (int i = 0; i < r; i++) {
		cin >> request[i];
	}
	if (compare(request, current)&&compare(request,need[n-1])) {
		for (int i = 0; i < r; i++) {
			current[i] = current[i] - request[i];
			need[n - 1][i] = need[n - 1][i] - request[i];
			allocate[n - 1][i] = allocate[n - 1][i] + request[i];
		}
		if (ifsafe() == 0) {
			cout << "execute the request successfully." << endl;
		}
		else {
			cout << "failed! Reject the request." << endl;
			for (int i = 0; i < r; i++) {
				current[i] = current[i] + request[i];
				need[n - 1][i] = need[n - 1][i] + request[i];
				allocate[n - 1][i] = allocate[n - 1][i] - request[i];
			}
		}
	}
	else {
		cout << "error!" << endl;
	}
}

int main() {
	int n;
	input();
	if (ifsafe() == 0) {
		cout << "successfully create." << endl;
		cout << "the safe sequence is:";
		for (int i = 0; i < p; i++) {
			cout << "p" << safesequence[i]<<" ";
		}
		cout << endl;
		while (1) {
			cout << "plz enter the process number that want to send the request:"<<endl;
			cout << "input the integer 0 to quit to send the request." << endl;
			cin >> n;
			if (n == 0) { break; }
			requestest(n);
		}
	}
	else {
		cout << "the state is unsafe! plz modify the value." << endl;
	}
	return 0;
}
