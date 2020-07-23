#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm> // https://bakura.developpez.com/tutoriel/cpp/tri/
using namespace std;
// https://www.youtube.com/watch?v=AgtOCNCejQ8

int maxCandidate() { return 14;} // Max 14 for windows 10, to avoid bad presentation.
int minCandidate() { return 2;}
int membersCalc() {
    return rand() % 50 + 1;
    }
string configurationLanguage() {
    return "en";
    }

void intro(int maxCandidate, string lgg = "en") {
    cout << "The members of a private club wants to recrute some friends.\nSome candidats are here, with a number, from 1 to " << maxCandidate << "."  << endl;
    cout << "Each member can have a friend (shown with his or her number) or a foe (shown with his or her -number), in the list, each line by member." << endl;
    cout << "If it possible, make a good list: each member must have at least one choice garanted: a friend in or a foe out." << endl;
    cout << "I don't know if it's possible to win, because I'm stupid, but I avoid some stupid problems." << endl;
    }
void prop(string lgg = "en") {
    cout << "Your proposition? (1 positive number at a time, negative numbers are ignored to help you, a true letter to close.)" << endl;
    }

int choicesCalc() {
    return rand() % (maxCandidate() - minCandidate() + 1) + minCandidate();
    }

void displayMatrix(vector < vector < int > >& Matrix) { // Ok.
    for(int a = 0; a < Matrix.size(); a++) {
        int column = 0;
        for(int b = 0; b < Matrix[a].size(); b++) {
            while(abs(Matrix[a][b]) != column) {
                column++;
                cout << "\t" ;
                }
            cout << Matrix[a][b];
            }
        cout << endl;
        }
    }

int value() {
    return ((2 * (rand() % 2)  - 1) * (rand() % maxCandidate() + 1)); // + or -, no 0.
    }

int SortByAbs(const int& a, const int& b) { // https://www.codingame.com/playgrounds/15869/c-runnable-snippets/sorting-a-vector
    return abs(a) == abs(b) ? a < b : (abs(a) < abs(b));
    }

void generateMatrix(vector < vector < int > >& Matrix) { // Ok.
    for(int a = 0; a < Matrix.size(); a++) {
        int choices = choicesCalc();
        Matrix[a][0] = value();
        for(int b = 0; b < choices; b++) {
            Matrix[a].push_back(value());
            }
// Candidates are better presented in order:
        sort(Matrix[a].begin(), Matrix[a].end(), SortByAbs); // https://www.codingame.com/playgrounds/15869/c-runnable-snippets/sorting-a-vector
// Delete double advices:
restartForCleanDoubleAdvices_generateMatrix: // Sorry!
        for(int b = 0; b < Matrix[a].size() - 1; b++) {
            if(abs(Matrix[a][b]) == abs(Matrix[a][b + 1])) {
                Matrix[a].erase(Matrix[a].begin() + b - 1); // Remove usually "accept", biaised for "refuse". Random can be added, but slow.
                goto restartForCleanDoubleAdvices_generateMatrix; // Sorry!
                }
            }
        }
    }

bool isIntInVector1D(int a, vector < int > & vector1D) { // Ok.
    for(int curseur = 0; curseur < vector1D.size(); curseur++) {
        if(a == vector1D[curseur]) {
            return true;
            }
        }
    return false;
    }

bool testMember(vector < int >& MatrixProposed, vector < int > & MatrixMember) {
    // For this member, is there a wanted candidate?
    for(int candidat = 0; candidat < MatrixProposed.size(); candidat++) {
        if(isIntInVector1D(MatrixProposed[candidat], MatrixMember) == true) {
            return true;
            }
        }
    // No wanted candidate here for this member.
    // For this member, is there a refuse? If no: return false.
    bool refuse = false;
    for(int demande = 0; demande < MatrixMember.size(); demande++) {
        if(MatrixMember[demande] < 0) {
            refuse = true;
            }
        }
    if(refuse == false) {
        return false;
        }
// Now, there is one refuse or more for this member, but:
// For this member, is all refused candidates? If no: return true.
// Pex :   MatrixMember = {1, -2, -3, -4, 5}
// Pex : MatrixProposed = {2, 13, 4}
    for(int demande = 0; demande < MatrixMember.size(); demande++) {
        if(MatrixMember[demande] > 0) { // Positives cases tested before.
            continue;
            }
        if(isIntInVector1D(-MatrixMember[demande], MatrixProposed) == false) {
            return true;
            }
        }
    return false;
    }

bool testMatrix(vector < int >&MatrixProposed, vector < vector < int > >& Matrix) {
    for(int membre = 0; membre < Matrix.size(); membre++) {
        if(testMember(MatrixProposed, Matrix[membre]) == false) {
            return false;
            }
        }
    return true;
    }

bool validation(vector < vector < int > >& Matrix) {  // Try to remove SOME stupid impossible matrix. Some impossible matrix will stay.
    vector<int> forced;//(0,0);
    for(int members = 0; members < Matrix.size(); members++) {
        if(Matrix[members].size() == 1) {
            forced.push_back(Matrix[members][0]);
            }
        }
    for(int a = 0; a < forced.size(); a++) {
        for(int b = a; b < forced.size(); b++) {
            if(forced[a] == -forced[b]) {
                return false;
                }
            }
        }
    return true;
    }

int main() {
    srand(time(NULL));       // No need for better init.
    string lgg = configurationLanguage();
    intro(maxCandidate(), lgg);
    // int hardToSolve = 0; // ?
    int members =  membersCalc();
    int choices = 1;
    vector < vector < int > > Matrix(members, vector< int >(choices, 0));
    do {
        generateMatrix(Matrix);
        }
    while(validation(Matrix) == false);
    displayMatrix(Matrix);
    prop(lgg);
    vector<int> MatrixProposed(0, 0);
    int input = 0;
    while(cin >> input) { // Enter any letter to end the loop!
        if(input > 0) { // You can add negative number for hint.
            MatrixProposed.push_back(input);
            }
        }
    if(testMatrix(MatrixProposed, Matrix)) {
        cout << ":-)" << endl;
        }
    else {
        cout << ":-(" << endl;
        }
    return 0;
    }
