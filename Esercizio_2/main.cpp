#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> // for std::sort (for comparison)

using namespace std;
using namespace std::chrono;

// BubbleSort algorithm
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// MergeSort algorithm
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Function to generate vectors of different types
vector<int> generateVector(int size, string type) {
    vector<int> vec(size);
    if (type == "random") {
        srand(time(nullptr));
        for (int i = 0; i < size; ++i)
            vec[i] = rand() % 1000;
    } else if (type == "sorted") {
        for (int i = 0; i < size; ++i)
            vec[i] = i;
    } else if (type == "reverse_sorted") {
        for (int i = size - 1, j = 0; i >= 0; --i, ++j)
            vec[j] = i;
    }
    return vec;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./sort_comparison <vector_size> <random|sorted|reverse_sorted> <number_of_trials>\n";
        return 1;
    }

    int size = stoi(argv[1]);
    string type = argv[2];
    int trials = stoi(argv[3]);

    vector<int> vec;

    for (int i = 0; i < trials; ++i) {
        vec = generateVector(size, type);

        // Measure time for BubbleSort
        auto start_bubble = high_resolution_clock::now();
        bubbleSort(vec);
        auto stop_bubble = high_resolution_clock::now();
        auto duration_bubble = duration_cast<microseconds>(stop_bubble - start_bubble);

        // Measure time for MergeSort
        vec = generateVector(size, type); // Reset vec
        auto start_merge = high_resolution_clock::now();
        mergeSort(vec, 0, vec.size() - 1);
        auto stop_merge = high_resolution_clock::now();
        auto duration_merge = duration_cast<microseconds>(stop_merge - start_merge);

        cout << "Trial " << i + 1 << ":\n";
        cout << "BubbleSort Time: " << duration_bubble.count() << " microseconds\n";
        cout << "MergeSort Time: " << duration_merge.count() << " microseconds\n";
    }

    return 0;
}

