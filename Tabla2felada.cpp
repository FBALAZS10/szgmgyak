#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>

static const size_t npos = -1;

using namespace std;

int column = 2;
int row = 2;
int rowFlag = 2;
int columnFlag = 2;

int b;
int sz;

char abc[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

int space[26] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
int width = 0;

string s(1, abc[column - 2]);

void menu() {
    cout << "\nA hasznalhato parancsok listaja:\n" << endl;
    cout << "*edit XY string* \t\t\t Irja be a megadott stringet az XY koordinataju cellaba(pl.A2)\n\t\t\t\t\t a stringben lehetnek szokozok, de sortores nem\n" << endl;
    cout << "*add N rows/cols* \t\t\t Adjon hozza N db uj, ures cellakbol allo sort/oszlopot a tablazat vegehez\n" << endl;
    cout << "*delete X/Y* \t\t\t\t Torolje az X oszlopot vagy Y sort (ha betu, akkor oszlop, ha szam, akkor sor)\n" << endl;
    cout << "*insert N rows/cols before/after X/Y*    mint az add, csak megadott pozicioba szurjon be\n" << endl;
    cout << "*exit \t\t\t\t\t Kilepes a programbol\n" << endl;
    cout << endl << endl << endl;
}

//-----------------------------------------------	//Megnézi az oszlopszélességeket

void spaceCounter(vector< vector <string> >& matrix, const char& specificCol, const bool& onlyThat) {

    int location = 0;
    for (int o = 0; o < 26; o++) {
        if (abc[o] == specificCol) {
            location = o;
        }
    }

    width = 0;
    if (onlyThat == true) {
        width = 0;
        for (int j = 0; j < row; j++) {
            if (matrix[j][location].length() > width) {
                width = matrix[j][location].length();
            }
        }
        space[location] = width;
    }
    else {

        for (int i = location ; i < column; i++) {
            width = 0;
            for (int j = 0; j < row; j++) {
                if (matrix[j][i].length() > width) {
                    width = matrix[j][i].length();
                }
            }
            space[i] = width;
        }
    }

}

void spaceCounter(vector< vector <string> >& matrix) {
    spaceCounter(matrix, 'A', false);
}

//-----------------------------------------------	//Kiirja a matrixot

void print(vector< vector <string> >& matrix) {
    cout << endl;
    width = 0;
    for (int k = 0; k < column; k++) {
        width += space[k];
        //cout << space[k] << endl;
    }
    width += column;
    //cout << column << endl;


    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {

            string str = matrix[i][j];
            if (matrix[i][j].length() < space[j]) {
                int dif = space[j] - matrix[i][j].length();
                for (int l = 0; l < dif; l++) {
                    str += " ";
                }
                cout << str + "|";
            }
            else {
                cout << str + "|";
            }

        }
        cout << endl;
        //cout << "\n";
        for (int p = 0; p < width; p++) {
            cout << "-";
        }
        cout << endl;

    }
}

//-----------------------------------------------	//adott pozicioba elem beszurasa

void mtxSetElement(vector < vector <string>>& matrix, int& settingRow, char& settingCol, string& setAct) {

    int settingCols = settingCol - 'A' + 1;

    if (row > settingRow && column > settingCols && settingRow != 0) {
        matrix[settingRow][settingCols] = setAct;
        spaceCounter(matrix, settingCols, true);
    }
    else {
        cout << "\nHibás bemeneti paramétert adott meg12!\n\n";
    }

}

//-----------------------------------------------  // N db Sor hozzaadas

void mtxAddRow(vector < vector <string>>& matrix, int& row, int& column, int& rowFlag, const int& sizeOfAddRow) {

    for (int j = 0; j < sizeOfAddRow; j++) {
        row++;
        matrix.resize(row);
        for (int i = 0; i < row; i++) {
            matrix[i].resize(column, " ");
            if (i != 0) {
                string y = to_string(i);
                matrix[i][0] = y;
            }

        }
    }
    spaceCounter(matrix);
}

//----------------------------------------------- 	// N db oszlop hozzaadas

void mtxAddColumn(vector < vector <string>>& matrix, int& row, int& column, int& columnFlag, const int& sizeOfAddCol) {

    for (int j = 0; j < sizeOfAddCol; j++) {
        column++;
        matrix.resize(row);
        for (int i = 0; i < row; i++) {
            matrix[i].resize(column, " ");
        }
        for (int k = 0; k < column; k++) {
            if (k != 0) {
                string x(1, abc[k - 1]);
                matrix[0][k] = x;
            }
        }
        columnFlag++;
    }
    spaceCounter(matrix);
}

//----------------------------------------------- // Valaszthato sor torlese

void mtxDelRow(vector < vector <string>>& matrix, int& row, int& column, int& deleteFlagRow, vector<vector<string>>::iterator& it1) {

    if (deleteFlagRow < row && deleteFlagRow > 0) {
        matrix.erase(it1 + deleteFlagRow);
        row -= 1;
        for (int i = 0; i < row; i++) {
            if (i != 0) {
                string y = to_string(i);
                matrix[i][0] = y;
            }
        }
        spaceCounter(matrix);
    }
    else {
        cout << "\nHibás bemeneti paramétert adtál meg!\n\n";
    }
}

//----------------------------------------------- // Valaszthato oszlop torlese

void mtxDelColumn(vector < vector <string>>& matrix, int& column, char& deleteFlagColumn) {

    int location = deleteFlagColumn - 'A';

    if (location < column - 1) {
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].erase(matrix[i].begin() + location + 1);// remove that column entry
        }
        column -= 1;
        for (int k = 0; k < column; k++) {
            if (k != 0) {
                string x(1, abc[k - 1]);
                matrix[0][k] = x;
            }
        }
        spaceCounter(matrix, deleteFlagColumn, false);
    }
    else {
        cout << "\nHibás bemeneti paramétert adtál meg!\n\n";
    }
}

//----------------------------------------------- // Insertálás ide-oda

void mtxInsertRowBefore(vector < vector <string>>& matrix, int& sizeOfInsertRow, int& placeOfInsertRow, int& column, int& row) {

    vector<string> segedvektor;
    for (int j = 0; j < column; j++) {
        segedvektor.push_back(" ");
    }
    matrix.insert(matrix.begin() + placeOfInsertRow, sizeOfInsertRow, segedvektor);
    row += sizeOfInsertRow;
    for (int i = 1; i < row; i++) {
        string iToString = to_string(i);
        matrix[i][0] = iToString;
    }
}

void mtxInsertRowAfter(vector < vector <string>>& matrix, int& sizeOfInsertRow, int& placeOfInsertRow, int& column, int& row) {
    vector<string> segedvektor;
    for (int j = 0; j < column; j++) {
        segedvektor.push_back(" ");
    }
    matrix.insert(matrix.begin() + (placeOfInsertRow + 1), sizeOfInsertRow, segedvektor);
    row += sizeOfInsertRow;
    for (int i = 1; i < row; i++) {
        string iToString = to_string(i);
        matrix[i][0] = iToString;
    }
}

void mtxInsertColBefore(vector < vector <string>>& matrix, int& sizeOfInsertCol, char& placeOfInsertCol, int& column, int& row) {

    int location = placeOfInsertCol - 'A';

    for (int i = 0; i < row; i++) {
        matrix[i].insert(matrix[i].begin() + location + 1, sizeOfInsertCol, " ");
    }
    column += sizeOfInsertCol;
    for (int k = 0; k < column; k++) {
        if (k != 0) {
            string x(1, abc[k - 1]);
            matrix[0][k] = x;
        }
    }
}

void mtxInsertColAfter(vector < vector <string>>& matrix, int& sizeOfInsertCol, char& placeOfInsertCol, int& column, int& row) {

    int location = placeOfInsertCol - 'A';

    for (int i = 0; i < row; i++) {
        matrix[i].insert(matrix[i].begin() + (location + 2), sizeOfInsertCol, " ");
    }
    column += sizeOfInsertCol;
    for (int k = 0; k < column; k++) {
        if (k != 0) {
            string x(1, abc[k - 1]);
            matrix[0][k] = x;
        }
    }
}

//-----------------------------------------------


int main() {


    string input;
    string command[5] = { "0","0","0","0","0" };
    int ci = 0, ii = 0, n = 0;
    string delimiter = " ";
    vector< vector <string> > matrix;
    matrix.push_back({ " ", s });
    matrix.push_back({ to_string(row - 1), " " });

    print(matrix);
    cout << "\n";

    menu();

    do {

        command[0] = "0"; command[1] = "0"; command[2] = "0"; command[3] = "0"; command[4] = "0";
        ci = 0;
        getline(cin, input);

        size_t pos = 0;
        string token;

        do {
            pos = input.find(delimiter);
            if (command[0] == "edit" && ci == 2) {
                token = input.substr(0);
                command[ci] = token;
                break;
            }
            token = input.substr(0, pos);
            command[ci] = token;
            ci++;
            input.erase(0, pos + delimiter.length());
        } while (pos != string::npos);


        /*for (int i=0; i < 5; i++) {
          cout  << command[i];
            }*/

        cout << "\n";

        if (command[0] != "0") {
            if (command[0] == "edit") {//-------------------------------

                b = isalpha(command[1][0]);
                sz = isdigit(command[1][1]);

                if (b != 0 && sz != 0) {
                    char character = command[1][0];
                    int number = stoi(command[1].substr(1));
                    mtxSetElement(matrix, number, character, command[2]);
                    spaceCounter(matrix);
                    print(matrix);
                }
                else {
                    cout << "\nHibás edit komandot adtál meg!\n";
                }

                //cout << "\nedit parancsot adtál meg!\n";

            }
            else if (command[0] == "add") { //-------------------------------

                sz = isdigit(command[1][0]);

                if (sz != 0) {
                    n = stoi(command[1]);

                    if (command[2] == "rows") {
                        mtxAddRow(matrix, row, column, rowFlag, n);
                    }
                    else if (command[2] == "cols") {
                        mtxAddColumn(matrix, row, column, columnFlag, n);
                    }
                    else {
                        cout << "\nHibás add komandot adtál meg!\n";
                    }
                    print(matrix);
                }
                else {
                    cout << "\nHibás bemeneti paramétert adtál meg!\n";
                }
                //cout << "\nadd parancsot adtál meg!\n";

            }
            else if (command[0] == "delete") {//-------------------------------

                int b = isalpha(command[1][0]);
                int sz = isdigit(command[1][0]);

                if (b != 0) {
                    if (column > 2) {
                        mtxDelColumn(matrix, column, command[1][0]);
                        print(matrix);
                    }
                    else {
                        cout << "Nem törölheted az egyetlen oszlopot!" << endl;
                    }
                }
                else if (sz != 0) {
                    if (row > 2) {
                        vector<vector<string> >::iterator it1 = matrix.begin();
                        int number = stoi(command[1]);
                        mtxDelRow(matrix, row, column, number, it1);
                        spaceCounter(matrix);
                        print(matrix);
                    }
                    else {
                        cout << "Nem törölheted az egyetlen sort!" << endl;
                    }
                }
                else {
                    cout << "\nHibás delete komandot adtál meg!\n";
                }
                //cout << "\ndelete parancsot adtál meg!\n";

            }
            else if (command[0] == "insert") {//------------------------------- beszúrás itt járok
                sz = isdigit(command[1][0]);
                if (sz != 0) {
                    int number = stoi(command[1]);

                    if (command[2] == "rows") {
                        if (command[3] == "before") {

                            b = isdigit(command[4][0]);

                            if (b != 0) {
                                int place = stoi(command[4]);
                                mtxInsertRowBefore(matrix, number, place, column, row);
                                print(matrix);
                            }
                            else {
                                cout << "Hibás insert komandot adtál meg!";
                            }

                        }
                        else if (command[3] == "after") {

                            b = isdigit(command[4][0]);

                            if (b != 0) {
                                int place = stoi(command[4]);
                                mtxInsertRowAfter(matrix, number, place, column, row);
                                print(matrix);
                            }
                            else {
                                cout << "Hibás insert komandot adtál meg!";
                            }
                        }
                        else {
                            cout << "\nHibás insert komandot adtál meg!\n";
                        }
                    }
                    else if (command[2] == "cols") {
                        if (command[3] == "before") {

                            b = isalpha(command[4][0]);

                            if (b != 0) {
                                mtxInsertColBefore(matrix, number, command[4][0], column, row);
                                spaceCounter(matrix);
                                print(matrix);
                            }
                            else {
                                cout << "Hibás insert komandot adtál meg!";
                            }
                        }
                        else if (command[3] == "after") {

                            b = isalpha(command[4][0]);

                            if (b != 0) {
                                mtxInsertColAfter(matrix, number, command[4][0], column, row);
                                spaceCounter(matrix);
                                print(matrix);
                            }
                            else {
                                cout << "Hibás insert komandot adtál meg!";
                            }
                        }
                        else {
                            cout << "\nHibás insert komandot adtál meg!\n";
                        }
                    }
                    else {
                        cout << "\nHibás insert komandot adtál meg!\n";
                    }
                }
                else {
                    cout << "\nHibás bemeneti paramétert adtál meg!8\n";
                }
                // cout << "\ninsert parancsot adtál meg!\n";

            }
            else if (command[0] == "/prog") {//------------------------------- betöltés

                if (column == 2 && row == 2) {
                    string inTakeByLines[26] = { "","","","","","","","","","","","","","","","","","","","","","","","","","" };

                    ifstream fin; //input fajl
                    fin.open(command[1]);

                    string sor = "";
                    char sep = ';';
                    int numOfRows = 0;
                    ii = 0;

                    if (command[2] == "-sep") {
                        sep = command[3][0];
                        while (!fin.eof())
                        {
                            numOfRows++;
                            if (numOfRows > 1) {
                                mtxAddRow(matrix, row, column, rowFlag, 1);
                            }
                            getline(fin, sor);

                            do {
                                pos = sor.find(sep);
                                token = sor.substr(0, pos);
                                //cout << token << endl;
                                inTakeByLines[ii] = token;
                                ii++;
                                sor.erase(0, pos + 1);
                            } while (pos != string::npos);

                            for (int m = 0; m < 26; m++) {
                                if (inTakeByLines[m] != "") {
                                    if (m + 1 == column) {
                                        mtxAddColumn(matrix, row, column, columnFlag, 1);
                                        mtxSetElement(matrix, numOfRows, abc[m], inTakeByLines[m]);
                                    }
                                    mtxSetElement(matrix, numOfRows, abc[m], inTakeByLines[m]);
                                    //cout<<inTakeByLines[m];
                                }
                                else {
                                    //cout<<endl;
                                    break;
                                }
                            }
                            ii = 0;
                            for (int ez = 0; ez < 26; ez++) {
                                inTakeByLines[ez] = "";
                            }
                        }
                    }
                    else {
                        while (!fin.eof())
                        {
                            numOfRows++;
                            if (numOfRows > 1) {
                                mtxAddRow(matrix, row, column, rowFlag, 1);
                            }
                            getline(fin, sor);

                            do {
                                pos = sor.find(sep);
                                token = sor.substr(0, pos);
                                //cout << token << endl;
                                inTakeByLines[ii] = token;
                                ii++;
                                sor.erase(0, pos + 1);
                            } while (pos != string::npos);

                            for (int m = 0; m < 26; m++) {
                                if (inTakeByLines[m] != "") {
                                    if (m + 1 == column) {
                                        mtxAddColumn(matrix, row, column, columnFlag, 1);
                                        mtxSetElement(matrix, numOfRows, abc[m], inTakeByLines[m]);
                                    }
                                    mtxSetElement(matrix, numOfRows, abc[m], inTakeByLines[m]);
                                    //cout<<inTakeByLines[m];
                                }
                                else {
                                    //cout<<endl;
                                    break;
                                }
                            }
                            ii = 0;
                            for (int ez = 0; ez < 26; ez++) {
                                inTakeByLines[ez] = "";
                            }
                        }
                    }

                    fin.close();
                    spaceCounter(matrix);
                    print(matrix);
                    cout << "" << endl;

                }
                else {
                    cout << "Csak 1 cellás táblázatba lehet betölteni csv-fájlt!" << endl;
                }

            }
            else if (command[0] == "save") {//------------------------------- mentés

                char sep = ';';
                string str = "";
                ofstream OutFile;

                if (command[2] == "-sep") {

                    sep = command[3][0];

                    if ((pos = command[1].find('.')) != string::npos) {
                        ofstream OutFile(command[1]);
                        for (int i = 1; i < matrix.size(); i++) {
                            for (int j = 1; j < matrix[i].size(); j++) {
                                if (j == 1) {
                                    str += matrix[i][j];
                                }
                                else {
                                    str += sep + matrix[i][j];
                                }
                            }
                            //cout << str << endl;
                            if (i == matrix.size()) {
                                OutFile << str;
                            }
                            else {
                                OutFile << str << "\n";
                            }

                            str = "";
                        }

                    }
                    else {
                        ofstream OutFile(command[1] + ".csv");
                        for (int i = 1; i < matrix.size(); i++) {
                            for (int j = 1; j < matrix[i].size(); j++) {
                                if (j == 1) {
                                    str += matrix[i][j];
                                }
                                else {
                                    str += sep + matrix[i][j];
                                }
                            }
                            //cout << str << endl;
                            if (i == matrix.size()) {
                                OutFile << str;
                            }
                            else {
                                OutFile << str << "\n";
                            }

                            str = "";
                        }
                    }

                }
                else {

                    if ((pos = command[1].find('.')) != string::npos) {
                        ofstream OutFile(command[1]);
                        for (int i = 1; i < matrix.size(); i++) {
                            for (int j = 1; j < matrix[i].size(); j++) {
                                if (j == 1) {
                                    str += matrix[i][j];
                                }
                                else {
                                    str += ";" + matrix[i][j];
                                }
                            }
                            //cout << str << endl;
                            if (i == matrix.size()) {
                                OutFile << str;
                            }
                            else {
                                OutFile << str << "\n";
                            }

                            str = "";
                        }
                    }
                    else {
                        ofstream OutFile(command[1] + ".csv");
                        for (int i = 1; i < matrix.size(); i++) {
                            for (int j = 1; j < matrix[i].size(); j++) {
                                if (j == 1) {
                                    str += matrix[i][j];
                                }
                                else {
                                    str += ";" + matrix[i][j];
                                }
                            }
                            cout << str << endl;
                            OutFile << str << "\n";
                            str = "";
                        }
                    }

                }

                cout << "Save completed!" << endl;
                //cout<<"itt lessz a mentés ha eljutok idáig :)";
            }
            else if (command[0] == "exit") {//-------------------------------
                break;
            }
            else {//-------------------------------
                cout << "\nHibás parancsot adtál meg!\n";
            }
        }

        menu();
    } while (input != "exit");
    cout << "Goodbye! (。・∀・)ノ";

    return 0;
    //std::cout << "Hello World!\n";
}