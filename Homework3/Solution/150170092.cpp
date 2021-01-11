/*  
    @author: Barış İncesu
    @ID: 150170092
    @date :11.01.2021

    ///////////////////////////

    Compile:
    g++ -std=c++11 150170092.cpp -o 150170092
    Run:
    ./150170092 euroleague.csv
*/

#include <iostream> // basic library for cout
using namespace std;

#include <string>  // string operation
#include <fstream> // file operation
#include <sstream> // string stream operaiton

bool superPosition = false; // same name state
class player
{
private:
    /* data */
public:
    string Name;
    int Rebound;
    int Assist;
    int Point;
    string color; // "RED" , "BLACK"
    player *left, *right, *parent;
    player(string, int, int, int); // Constructor
    ~player();                     //Deconstructor
};

player::player(string newName, int newRebound, int newAssist, int newPoint)
{
    this->Name = newName;
    this->Rebound = newRebound;
    this->Assist = newAssist;
    this->Point = newPoint;
    left = right = parent = NULL; // nulling arrows
    this->color = "RED";          // new PLayer always starts with RED
}

player::~player() {}
// Class to represent Red-Black Tree
class RBTree
{
private:
    player *root;
    player *maxList[3]; // keeps max statistics player *

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
    player **max(player *); // return maxList
    player *getRoot() { return root; }
};

// A recursive function to do print tree in preorder traversal
void preorder(player *root, int dashCounter)
{
    if (root == NULL)
        return;
    for (int i = 0; i < dashCounter; i++)
    {
        cout << "-";
    }

    cout << "(" << root->color << ") " << root->Name << endl;
    dashCounter++;
    preorder(root->left, dashCounter);
    preorder(root->right, dashCounter);
}

player **RBTree::max(player *root) // max statics
{
    if (*maxList == NULL)
    {
        maxList[0] = root; // keeps maxRebound
        maxList[1] = root; // keeps maxAssist
        maxList[2] = root; // keeps maxPoint
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
    // recursive operation
    max(root->left);
    max(root->right);

    return maxList;
}

/* A utility function to insert a new node with given key in BST */
player *BSTInsert(player *root, player *pt)
{
    // If the tree is empty
    if (root == NULL)
        return pt;

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
    else if (pt->Name == root->Name) // update situation
    {
        root->Rebound = root->Rebound + pt->Rebound;
        root->Assist = root->Assist + pt->Assist;
        root->Point = root->Point + pt->Point;

        pt = root;
        superPosition = true;
    }

    // return root
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

// function fixes violations caused by insertion
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

            /* Case : A1 The uncle of pt is also red Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == "RED")
            {
                grand_parent_pt->color = "RED";
                parent_pt->color = "BLACK";
                uncle_pt->color = "BLACK";
                pt = grand_parent_pt;
            }

            else
            {
                /* Case : A2-1 pt is right child of its parent Left-rotation required */
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : A2 pt is left child of its parent Right-rotation required */
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        /* Case : B Parent of pt is right child of Grand-parent of pt */
        else
        {
            player *uncle_pt = grand_parent_pt->left;

            /* Case : B1 The uncle of pt is also red Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == "RED"))
            {
                grand_parent_pt->color = "RED";
                parent_pt->color = "BLACK";
                uncle_pt->color = "BLACK";
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : B2-1 pt is left child of its parent Right-rotation required */
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : B2 pt is right child of its parent Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = "BLACK"; // always root be "BLACK"
}

// Function to insert a new node with given data
void RBTree::insert(const string &Name, const int &Rebound, const int &Assist, const int &Point)
{
    player *pt = new player(Name, Rebound, Assist, Point);

    // Do a normal BST insert
    root = BSTInsert(root, pt);
    // fix Red Black Tree violations
    if (!superPosition) // if there isnt update, there is insertion
    {
        fixViolation(root, pt);
    }
    superPosition = false; //superPositon reset for new Player
}

int main(int argc, char const *argv[])
{
    string file_name = argv[1];
    ifstream file;
    file.open(file_name);

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    getline(file, line); // header line
    //Season , Name , Team , Rebound , Assist , Point
    RBTree tree;                               // tree created.
    string oldSeason = "", Season, Name, Team; // input fields
    int Rebound = 0, Assist = 0, Point = 0, i = 0;
    // i for just write first season tree model

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

        if (oldSeason != Season || file.eof()) // when season changes detected
        {
            if (i >= 1) // display statistics
            {
                player **x = tree.max(tree.getRoot());
                cout << "End of the " << oldSeason << " Season" << endl;
                cout << "Max Points:  " << x[2]->Point << " - Player Name: " << x[2]->Name << endl;
                cout << "Max Assists:  " << x[1]->Assist << " - Player Name: " << x[1]->Name << endl;
                cout << "Max Rebs:  " << x[0]->Rebound << " - Player Name: " << x[0]->Name << endl;
            }
            if (i == 1) // first season tree printed
            {
                preorder(tree.getRoot(), 0);
            }

            i++;
        }
        oldSeason = Season;                        // oldSeason and Season compare for season changes detection
        tree.insert(Name, Rebound, Assist, Point); // insert new PLayer to RBTree
    }

    return 0;
}
