#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <deque>

using namespace std;

const int max_params_n = 100000;

void read_input(int &layers_n, int* d) {
	printf("Please enter the number of layers:\n");
	scanf("%d", &layers_n);

	for (int i = 0; i < layers_n; i++) {
		printf("Please enter the number of parameters in the %d-th layer:\n", i);
		scanf("%d", &d[i]);
	}

	return;
}

int main() {
	int layers_n;
	int d[max_params_n];

	read_input(layers_n, d);

/*	for (int i = 0; i < layers_n; i++)
		printf("%d\n", d[i]);
*/
	int M[max_params_n];
	M[layers_n - 1] = d[layers_n - 1];
	deque<pair<int, int> > Q;
	int U = d[layers_n - 1] + d[layers_n - 1]; // The value of U(layer_n - 1, layer_n - 1)
	int j = layers_n - 1;
	deque<pair<int, int> > max_dk;
	max_dk.push_front(make_pair(layers_n - 1, d[layers_n - 1]));

	// The elements in both deques are in increasing order. 
	for (int i = layers_n - 2; i >= 0; i--) {
		// Update Q
		if (!Q.empty()) {
			while (Q.front().second > M[i + 1])
				Q.pop_front();
		}
		Q.push_front(make_pair(i + 1, M[i + 1]));

		// Update U(i + 1, j) to U(i, j)
		U += d[i + 1];
		int current_max_dk = max_dk.back().second;
		if (current_max_dk < d[i])
			U += d[i] - current_max_dk;
		while (max_dk.empty() == false && max_dk.front().second < d[i])
			max_dk.pop_front();
		max_dk.push_front(make_pair(i, d[i]));

		// Calculate M(i)
		M[i] = d[i];
		int old_maximum, new_maximum;
		do{
			// Find the next M(j)
			int j_next = Q.back().first;
			// Find the next U
			int U_next = U;
			//     Update /sum d_k
			for (int j_interval = j - 1; j_interval > j_next; j_interval--)
				U_next -= d[j_interval];
			//     Update /max d_k
			deque<pair<int, int> > max_dk_next;
			for (int k = 0; k < max_dk.size(); k++)
				max_dk_next.push_back(max_dk[k]);
			while (max_dk_next.empty() == false && max_dk_next.back().first > j_next - 1)
				max_dk_next.pop_back();
			U_next = U_next - max_dk.back().second + max_dk.back().second;
			//     Update d_j
			U_next = U_next - d[j] + d[j_next];
			// Check if we need to update the j
			old_maximum = (M[j] > U)? M[j]:U;
			new_maximum = (M[j_next] > U_next)? M[j_next]:U;
			if (new_maximum < old_maximum) {
				j = j_next;
				Q.pop_back();
				while (max_dk.empty() == false && max_dk.end()->first >= j)
					max_dk.pop_back();
			}
		} while (new_maximum < old_maximum);
		M[i] += old_maximum;
	}
	printf("The minimum usage of memory is %d.", M[0]);
	return 0;
}
