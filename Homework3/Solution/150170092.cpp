/** C++ implementation for Red-Black Tree Insertion 
This code is adopted from the code provided by Dinesh Khandelwal in comments **/
#include <bits/stdc++.h>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>

bool superPosition = false;
class player
{
private:
    /* data */
public:
    string Name;
    int Rebound;
    int Assist;
    int Point;
    string color;
    player *left, *right, *parent;
    player(string, int, int, int);
    ~player();
};

player::player(string newName, int newRebound, int newAssist, int newPoint)
{
    this->Name = newName;
    this->Rebound = newRebound;
    this->Assist = newAssist;
    this->Point = newPoint;
    left = right = parent = NULL;
    this->color = "RED";
}

player::~player() {}
// Class to represent Red-Black Tree
class RBTree
{
private:
    player *root;
    player *maxList[3];

protected:
    void rotateLeft(player *&, player *&);
    void rotateRight(player *&, player *&);
    void fixViolation(player *&, player *&);

public:
    // Constructor
    RBTree()
    {
        root = NULL;
        *maxList = NULL;
    }
    void insert(const string &, const int &, const int &, const int &);
    player **max(player *);
    player *getRoot() { return root; }
};

// A recursive function to do preorder traversal
void preorderHelper(player *root, int dashCounter)
{
    if (root == NULL)
        return;
    for (int i = 0; i < dashCounter; i++)
    {
        cout << "-";
    }

    cout << "(" << root->color << ") " << root->Name << endl;
    dashCounter++;
    preorderHelper(root->left, dashCounter);
    preorderHelper(root->right, dashCounter);
}

player **RBTree::max(player *root)
{
    if (*maxList == NULL)
    {
        maxList[0] = root;
        maxList[1] = root;
        maxList[2] = root;
    }
    if (!root)
    {
        return maxList;
    }

    if (root->Rebound > maxList[0]->Rebound)
    {
        maxList[0] = root;
    }
    if (root->Assist > maxList[1]->Assist)
    {
        maxList[1] = root;
    }
    if (root->Point > maxList[2]->Point)
    {
        maxList[2] = root;
    }

    max(root->left);
    max(root->right);

    return maxList;
}

/* A utility function to insert a new node with given key in BST */
player *BSTInsert(player *root, player *pt)
{
    /* If the tree is empty, return a new node */
    if (root == NULL)
        return pt;

    /* Otherwise, recur down the tree */
    if (pt->Name < root->Name)
    {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->Name > root->Name)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }
    else if (pt->Name == root->Name)
    {
        root->Rebound = root->Rebound + pt->Rebound;
        root->Assist = root->Assist + pt->Assist;
        root->Point = root->Point + pt->Point;

        pt = root;
        superPosition = true;
    }

    /* return the (unchanged) node pointer */
    return root;
}

void RBTree::rotateLeft(player *&root, player *&pt)
{
    player *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBTree::rotateRight(player *&root, player *&pt)
{
    player *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// This function fixes violations caused by BST insertion
void RBTree::fixViolation(player *&root, player *&pt)
{
    player *parent_pt = NULL;
    player *grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != "BLACK") && (pt->parent->color == "RED"))
    {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /* Case : A Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left)
        {

            player *uncle_pt = grand_parent_pt->right;

            /* Case : 1 The uncle of pt is also red Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == "RED")
            {
                grand_parent_pt->color = "RED";
                parent_pt->color = "BLACK";
                uncle_pt->color = "BLACK";
                pt = grand_parent_pt;
            }

            else
            {
                /* Case : 2 pt is right child of its parent Left-rotation required */
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3 pt is left child of its parent Right-rotation required */
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        /* Case : B 
		Parent of pt is right child 
		of Grand-parent of pt */
        else
        {
            player *uncle_pt = grand_parent_pt->left;

            /* Case : 1 The uncle of pt is also red Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == "RED"))
            {
                grand_parent_pt->color = "RED";
                parent_pt->color = "BLACK";
                uncle_pt->color = "BLACK";
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2 pt is left child of its parent Right-rotation required */
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3 
				pt is right child of its parent Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = "BLACK";
}

// Function to insert a new node with given data
void RBTree::insert(const string &Name, const int &Rebound, const int &Assist, const int &Point)
{
    player *pt = new player(Name, Rebound, Assist, Point);

    // Do a normal BST insert
    root = BSTInsert(root, pt);
    // fix Red Black Tree violations
    if (!superPosition)
    {
        fixViolation(root, pt);
    }
    superPosition = false;
}

// Function to do preorder traversal
/*void RBTree::preorder() { preorderHelper(root); }*/

// Driver Code
int main()
{
    ifstream file;
    file.open("deneme.csv");

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    getline(file, line); // header line
    //Season , Name , Team , Rebound , Assist , Point
    RBTree tree;
    string oldSeason = "", Season, Name, Team;
    int Rebound = 0, Assist = 0, Point = 0, i = 0;

    while (!file.eof())
    {
        getline(file, Season, ',');
        getline(file, Name, ',');
        getline(file, Team, ',');
        getline(file, Team, ',');
        Rebound = stoi(Team);
        getline(file, Team, ',');
        Assist = stoi(Team);
        getline(file, Team, '\n');
        Point = stoi(Team);
        //getline(file, line, '\n'); // this is for reading the \n character into dummy variable.

        if (oldSeason != Season || file.eof())
        {
            if (i >= 1)
            {
                player **x = tree.max(tree.getRoot());
                cout << "End of the " << oldSeason << " Season" << endl;
                cout << "Max Points:  " << x[2]->Point << " - Player Name: " << x[2]->Name << endl;
                cout << "Max Assists:  " << x[1]->Assist << " - Player Name: " << x[1]->Name << endl;
                cout << "Max Rebs:  " << x[0]->Rebound << " - Player Name: " << x[0]->Name << endl;
            }
            if (i == 1)
            {
                preorderHelper(tree.getRoot(), 0);
            }

            i++;
        }
        oldSeason = Season;
        tree.insert(Name, Rebound, Assist, Point);
    }

    return 0;
}
