#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "ShoppingList.h"
#include "ShoppingList.cpp"

using namespace std;

int main(){
    ifstream i_file; //Input file
    sl.readFile(i_file);
    char choice;
    char resp;
    while (true){
    cout << "---------------------------------------------------------" << endl;
    cout << "           My Shopping List                              " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "   1. Add items to shopping list"      << endl;
    cout << "   2. View all items in shopping list" << endl;
    cout << "   3. Edit shopping lists"             << endl;
    cout << "   4. Search inside shopping list"     << endl;
    cout << "   5. Delete an item inside list"      << endl;
    cout << "   6. Exit program"                    << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Enter your choice: "                   ;
    cin >> choice;
    system("CLS");

    if (choice == '1')
        sl.AddItem();
    else if (choice == '2')
        sl.ViewList();
    else if (choice == '3')
        sl.EditList();
    else if (choice == '4')
        sl.SearchForItems();
    else if (choice == '5')
        sl.DeleteItems();
    else if (choice == '6')
        break;
    else
        cout << "Input Invalid!" << endl;

    cout << "\n\nDo you want to continue (y) for Yes, (n) for No: ";
    cin >> resp;
    if ((resp == 'y') || (resp == 'Y')){
        system("CLS");
        continue;
    }
    else if ((resp == 'n') || (resp == 'N'))
        break;
    else
        cout << "\nInput Invalid!" << endl;
    }
    system("CLS");
    sl.WriteToFile();
    system("PAUSE");
    return 0;
}
