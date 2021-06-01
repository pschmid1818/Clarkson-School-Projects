#include <iostream>
#include <string>
#include <cstdlib>
#include "avl.h"

using namespace std;

float randomGPA(){
        //Generate a random GPA between 2 and 4.
        return rand() / (float)RAND_MAX * 2 + 2;
}

int main(){
        AVL records;
        int i;

        //Insert 100 records
        for(i = 1; i <= 100; i++){
                int id = i;
                string name = "Student" + to_string(i);
                float gpa = randomGPA();
                
                records.insert(student(id, name, gpa));
        }

        //Print all records sorted by student ID, so we do an in-order traversal of the tree
        records.printAll();

        cout << "The max GPA is: " << records.maxGPA() << endl;

        int id;
        cout << "Please enter a student ID: " << endl;
        cin >> id;
        cout << "The student has GPA: " << records.GPA(id) << endl;

        //Show the height of the current AVL tree, the output should be 6.
        cout << "The height of the current tree: " << endl;
        records.showHeight();

        //Delete 50 records
        for(i = 30; i <= 79; i++){
                //Delete a student record, which has ID "i"
                records.deleteID(i);
        }

        cout << "After deleting 50 records, we now have: " << endl;

        //Print all records sorted by student ID, so we do an in-order traversal of the tree
        records.printAll();

        //Show the height of the current AVL tree, the output should be 5.
        cout << "The height of the current tree: " << endl;
        records.showHeight();
}

