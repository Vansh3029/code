#include <iostream>
using namespace std;

const int P = 5;  // Number of processes
const int R = 3;  // Number of resources

int available[R] = {3, 3, 2};

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int maxNeed[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int need[P][R];

void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
}

void printNeed() {
    cout << "\nNeed Matrix:\n";
    cout << "    A B C\n";

    for (int i = 0; i < P; i++) {
        cout << "P" << i << "  ";
        for (int j = 0; j < R; j++) {
            cout << need[i][j] << " ";
        }
        cout << "\n";
    }
}

// Safety Algorithm
bool is_safe() {
    int work[R];

    for (int j = 0; j < R; j++)
        work[j] = available[j];

    bool finish[P] = {false};
    int safeSeq[P];
    int count = 0;

    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (finish[i])
                continue;

            bool canFinish = true;

            for (int j = 0; j < R; j++) {
                if (need[i][j] > work[j]) {
                    canFinish = false;
                    break;
                }
            }

            if (canFinish) {
                for (int j = 0; j < R; j++)
                    work[j] += allocation[i][j];

                finish[i] = true;
                safeSeq[count++] = i;
                found = true;
            }
        }

        if (!found)
            break;
    }

    if (count == P) {
        cout << "System is in a SAFE state.\n";
        cout << "Safe Sequence: ";

        for (int i = 0; i < P; i++) {
            cout << "P" << safeSeq[i];
            if (i != P - 1)
                cout << " -> ";
        }

        cout << "\n";
        return true;
    }

    return false;
}

// Resource Request Algorithm
void request(int p, int req[]) {
    cout << "\nRequest by P" << p << ": ("
         << req[0] << ", " << req[1] << ", "
         << req[2] << ")\n";

    // Check maximum claim
    for (int j = 0; j < R; j++) {
        if (req[j] > need[p][j]) {
            cout << "Error: Process exceeded its maximum claim.\n";
            return;
        }
    }

    // Check resource availability
    for (int j = 0; j < R; j++) {
        if (req[j] > available[j]) {
            cout << "Resources not available. P"
                 << p << " must WAIT.\n";
            return;
        }
    }

    // Temporarily allocate resources
    for (int j = 0; j < R; j++) {
        available[j] -= req[j];
        allocation[p][j] += req[j];
        need[p][j] -= req[j];
    }

    // Grant only if the new state is safe
    if (is_safe()) {
        cout << "Request GRANTED.\n";
    } else {
        // Rollback all changes
        for (int j = 0; j < R; j++) {
            available[j] += req[j];
            allocation[p][j] -= req[j];
            need[p][j] += req[j];
        }

        cout << "Request would lead to an UNSAFE state. "
             << "Request DENIED (rolled back).\n";
    }
}

int main() {
    calculateNeed();
    printNeed();

    cout << "\nInitial State:\n";
    is_safe();

    int req1[R] = {1, 0, 2};
    request(1, req1);

    int req2[R] = {3, 3, 0};
    request(4, req2);

    int req3[R] = {0, 2, 0};
    request(0, req3);

    return 0;
}