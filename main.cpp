#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "B_Tree.h"
using namespace std;
class StorageEngine
{
private:
    BTree *Tree;

public:
    StorageEngine()
    {
        Tree = new BTree;
    }
    void insertRecord()
    {
        int id;
        string name;
        int age;
        int marks;

        cout << "ENTER THE ID: " << endl;
        cin >> id;
        cout << "ENTER THE NAME: " << endl;
        cin >> name;
        cout << "ENTER THE AGE: " << endl;
        cin >> age;
        cout << "ENTER THE MARKS: " << endl;
        cin >> marks;

        string recordName = "Records/";
        recordName += to_string(id) + ".txt";
        FILE *filePtr = fopen(recordName.c_str(), "w");
        string data = name + " " + to_string(age) + " " + to_string(marks) + "\n";
        fprintf(filePtr, data.c_str());

        Key newKey(id, filePtr);
        Tree->insert(newKey);

        cout << "SUCCESSFULLY INSERTED" << endl;
        fclose(filePtr);
    }
    void searchRecord()
    {
        int id;
        cout << "ENTER THE ID: " << endl;
        cin >> id;
        Tree->search(id);
    }
};
int main()
{
    system("cls");
    cout << "WELCOME" << endl;
    cout << endl;
    int option;
    while (true)
    {
        cout << "SELECT ONE OF THE OPTIONS" << endl;
        cout << "1.INSERT" << endl;
        cout << "2.DELETE" << endl;
        cout << "3.SEARCH" << endl;
        cout << "4.DISPLAY" << endl;
        cout << "5.EXIT" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            cout << "ENTER A VALID OPTION" << endl;
            break;
        }
    }
}