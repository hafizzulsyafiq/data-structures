#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

#define MAX_NUM_ITEMS 50

using namespace std;

class ShoppingList{
    private:
        string item_name[MAX_NUM_ITEMS];
        int front_counter;
        int back_counter;
        int q_item_counter;
        int first_element = 0;
        int last_element = MAX_NUM_ITEMS - 1;
        string file_path = "shopping_list.txt";
    public:
        ShoppingList();
        void readFile(ifstream&);
        void enqueue(string newItem);
        void dequeue();
        void AddItem();
        void ViewList();
        void SortItems(int, int);
        void ArrayMerge(int, int, int);
        void SearchForItems();
        void EditList();
        void DeleteItems();
        void WriteToFile();
};
#endif // SHOPPINGLIST_H
