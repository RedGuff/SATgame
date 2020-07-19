#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm> // https://bakura.developpez.com/tutoriel/cpp/tri/
using namespace std;
// https://www.youtube.com/watch?v=AgtOCNCejQ8

int maxCandidate = 42;

void displayMatrix(vector < vector < int > >& Matrix) {
    for(int a = 0; a < Matrix.size(); a++) {
        for(int b = 0; b < Matrix[a].size(); b++) {
            cout << Matrix[a][b] << "\t" ;
            }
        cout << endl;
        }
    }

int value() {
    return ((2 * (rand() % 2)  - 1) * (rand() % maxCandidate + 1));
    }

int SortByAbs(const int& a, const int& b) { // https://www.codingame.com/playgrounds/15869/c-runnable-snippets/sorting-a-vector
    return abs(a) == abs(b) ? a < b : (abs(a) < abs(b));
    }

void generateMatrix(vector < vector < int > >& Matrix) {
    for(int a = 0; a < Matrix.size(); a++) {
        int choices = rand() % 5 + 1;
        Matrix[a][0] = value();
        for(int b = 0; b < choices; b++) {
            Matrix[a].push_back(value());
            }
        sort(Matrix[a].begin(), Matrix[a].end(), SortByAbs); // https://www.codingame.com/playgrounds/15869/c-runnable-snippets/sorting-a-vector
        }
    }

bool testMatrix(vector < int >&MatrixProposed, vector < vector < int > >& MatrixMatrix) {
    clog << "TODO!" << endl;
    return true;
    }


int main() {
    srand(time(NULL));       // No need for better init.
    // int hardToSolve = 0; // ?
    int   members =     rand() % 5 + 1;
    int choices =      1;
    vector < vector < int > > Matrix(members, vector< int >(choices, 0));
    generateMatrix(Matrix);
    displayMatrix(Matrix);
    cout << "Your proposition? (1 number at a time, a true letter to close.)" << endl;
    vector<int> MatrixProposed(0, 0);
    int input = 0;
    while(cin >> input) { //enter any non-integer to end the loop!
        MatrixProposed.push_back(input);
        }
    if(testMatrix(MatrixProposed, Matrix)) {
        cout << "You win!" << endl;
        }
    else {
        cout << "You lose! (I don't know if it's possible to win, I'm stupid.)" << endl;
        }
    return 0;
    }
