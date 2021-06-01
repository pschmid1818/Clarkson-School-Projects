#include <string>

using namespace std;

/**********************************************************************
 *
 *      You can add things to this file, if necessary.
 *
 * ********************************************************************/

struct student{
    int id;                 //student ID
    string name;            //student name
    float gpa;              //student GPA
    
    student(){};
    student(int i, string n, float g)
    {id = i; name = n; gpa = g;}

};

struct node{
    student s;              //student record
    int height;             //stores the nodes height
    int bf;                 //stores the nodes balance factor
    node *left_child;       //a pointer to the left child
    node *right_child;      //a poitner to the right child

    node(student s1, int h, int f, node *l, node *r)
    {s = s1; height = h, bf = f, left_child = l, right_child= r;}
};

class AVL{
private:
    node *root;             //the root node of the tree
public:
    AVL();

    void insert(student s);
    //insert a student record into the tree

    void deleteID(int id);
    //delete a student record from the tree based on ID

    void showHeight();
    //print the height of the current AVL tree

    void printAll();
    //print all records, sorted by student ID. This is essentially an in-order traversal of the tree.

	float GPA(int id);
    //return a student's GPA based on his/her ID

    float maxGPA();
    //return the max GPA of all the students

};

