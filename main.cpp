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
        // cin >> name;
        name = "charan";
        cout << "ENTER THE AGE: " << endl;
        // cin >> age;
        age = 21;
        cout << "ENTER THE MARKS: " << endl;
        // cin >> marks;
        marks = 99;

        string recordName = "Records/";
        recordName += to_string(id) + ".txt";
        FILE *filePtr = fopen(recordName.c_str(), "w");
        string data = name + " " + to_string(age) + " " + to_string(marks) + "\n";
        fprintf(filePtr, data.c_str());

        Key newKey(id, filePtr);
        Tree->insert(newKey);

        fclose(filePtr);
        cout << filePtr << endl;
        cout << "SUCCESSFULLY INSERTED" << endl;
        cout << endl;
    }
    void searchRecord()
    {
        int id;
        cout << "ENTER THE ID: " << endl;
        cin >> id;
        FILE *filePtr = Tree->search(id);
        if (filePtr == nullptr)
        {
            cout << "No record found" << endl;
        }
        else
        {
            cout << "The indexing was pointing to the memory location: " << filePtr << endl;
        }
    }
    void displayKeys()
    {
        cout << "Displaying the Tree" << endl;
        Tree->display();
    }
};
int main()
{
    system("cls");
    cout << "WELCOME" << endl;
    cout << endl;
    int option;
    StorageEngine se;
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
            se.insertRecord();
            break;
        case 2:
            break;
        case 3:
            se.searchRecord();
            break;
        case 4:
            se.displayKeys();
            break;
        case 5:
            exit(0);
            break;
        default:
            cout << "ENTER A VALID OPTION" << endl;
            break;
        }
    }
}