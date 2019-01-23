#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "ShoppingList.h"

using namespace std;

ShoppingList sl;

ShoppingList::ShoppingList(){
    front_counter = 0;
    back_counter = MAX_NUM_ITEMS - 1;
    q_item_counter = 0;
    for (unsigned i = 0; i < MAX_NUM_ITEMS; i++){
        item_name[i] = "~";
    }
}

void ShoppingList::readFile(ifstream &input_file){
	string itemName;
    input_file.open(file_path.c_str()); //Opens file
    int i = 0;
	while(  (getline(input_file, itemName))
             ){
		item_name[i] = itemName;
		i++;
    }

	input_file.close(); //Close the input file
}

void ShoppingList::enqueue(string newItem){
    if (q_item_counter == MAX_NUM_ITEMS)
        cout << "enqueue: Queue is full!" << endl;
    else {
        back_counter = (back_counter + 1) % MAX_NUM_ITEMS;
        item_name[back_counter] = newItem;
        q_item_counter++;
    }
}

void ShoppingList::dequeue(){
    if (front_counter == back_counter)
        cout << "dequeue: Queue is empty" << endl;
    else{
        item_name[front_counter] = "~";
        front_counter = (front_counter + 1) % MAX_NUM_ITEMS;
        q_item_counter--;
    }
}

void ShoppingList::AddItem(){
    unsigned item_amount;
    string itemName;
    cout << "\nHow many items do you want to add: ";
	cin >> item_amount;

	for (unsigned i = 0; i < item_amount; i++){
        fflush(stdin);
        cout <<"\nAdding items..." << endl;
		cout <<"\nItem name : " ;
		getline(cin, itemName);
		sl.enqueue(itemName);
    }
}

void ShoppingList::ViewList(){
    cout << "List of items in list: " << endl;
    sl.SortItems(first_element, last_element);
    for (unsigned i = 0; i < MAX_NUM_ITEMS; i++){
        cout << " " << i+1 << ".  " << item_name[i] << endl;
    }
}

/*
void ShoppingList::SortItems(){
    int startScan, minIndex;
    string minValue;

    for (startScan = 0; startScan < MAX_NUM_ITEMS; startScan++)
    {
        minIndex = startScan;
        minValue = item_name[startScan];

        for(unsigned index = startScan + 1; index < MAX_NUM_ITEMS; index++)
        {
            //if (item_name[index] == "") break;
            if (item_name[index] < minValue)
            {
                minValue = item_name[index];
                minIndex = index;
            }
        }
        item_name[minIndex] = item_name[startScan];
        item_name[startScan] = minValue;
    }
}
*/

void ShoppingList::SearchForItems(){
    int first = 0,             // First array element
        last = MAX_NUM_ITEMS - 1,       // Last array element
        middle,                // Mid point of search
        position = -1;         // Position of search value
    bool found = false;        // Flag
    string value;

    sl.SortItems(first_element, last_element);

    fflush(stdin);
    cout << "Please enter an item's name: ";
    getline(cin, value);

    while (!found && first <= last) {
        middle = (first + last) / 2;     // Calculate mid point
        if (item_name[middle] == value)      // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if (item_name[middle] > value)  // If value is in lower half
            last = middle - 1;
        else
            first = middle + 1;           // If value is in upper half
    }

    if (position == -1)
        cout << "That name does not exist in the array.\n";
    else
    {
        cout << value << " is found at element " << position;
        cout << " in the array.\n";
    }
}

void ShoppingList::EditList(){
    unsigned item_position;
    string newItemName;
    sl.ViewList();
    cout << "Which item in the list you want to edit: ";
    cin >> item_position;
    cin.clear();
    cin.ignore(100,'\n');
    item_position = item_position - 1;
    for(;;){
        if (item_position >= MAX_NUM_ITEMS){
            cout << "That item does not exist!" << endl;
        }
        else{
            fflush(stdin);
            cout << "Enter the new item name: ";
            cin >> newItemName;
            item_name[item_position] = newItemName;
            break;
        }
    }
}

void ShoppingList::DeleteItems(){
    cout << "Dequeue-ing the latest item added...";
    sl.dequeue();
}

void ShoppingList::WriteToFile(){
    ofstream write_info;
    write_info.open("shopping_list.txt");
    for (int i =0; i < MAX_NUM_ITEMS; i++){
        write_info << item_name[i] << endl;
    }

    cout << "The shopping list is successfully written!" << endl;
}

void ShoppingList::SortItems(int first_element, int last_element){
    if (first_element < last_element) {
        int mid_element = (first_element + last_element)/2;
        sl.SortItems(first_element, mid_element);
        sl.SortItems(mid_element + 1, last_element);
        sl.ArrayMerge(first_element, mid_element, last_element);
    }
}


void ShoppingList::ArrayMerge(int first_element, int mid_element, int last_element){
    string item_temp[MAX_NUM_ITEMS];

    int first_temp1 = first_element;
    int last_temp1 = mid_element;
    int first_temp2 = mid_element + 1;
    int last_temp2 = last_element;
    int i;

    for (i = first_element; (first_temp1 <= last_temp1) && (first_temp2<= last_temp2); ++i){
        if(item_name[first_temp1] < item_name[first_temp2]){
            item_temp[i] = item_name[first_temp1];
            ++first_temp1;
        }
        else{
            item_temp[i] = item_name[first_temp2];
            ++first_temp2;
        }
    }

    while (first_temp1 <= last_temp1){
        item_temp[i] = item_name[first_temp1];
        ++first_temp1;
        ++i;
    }

    while (first_temp2 <= last_temp2){
        item_temp[i] = item_name[first_temp2];
        ++first_temp2;
        ++i;
    }

    for (i = first_element; i <= last_element; ++i){
        item_name[i] = item_temp[i];
    }
}
