/** C++ implementation for Red-Black Tree Insertion 
This code is adopted from the code provided by Dinesh Khandelwal in comments **/
#include <bits/stdc++.h>
using namespace std;

enum Color
{
    RED,
    BLACK
};

class player
{
private:
    /* data */
public:
    string Name;
    int Rebound;
    int Assist;
    int Point;
    bool color;
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
    this->color = RED;
}

player::~player()
{
}
// Class to represent Red-Black Tree
class RBTree
{
private:
    player *root;

protected:
    void rotateLeft(player *&, player *&);
    void rotateRight(player *&, player *&);
    void fixViolation(player *&, player *&);

public:
    // Constructor
    RBTree() { root = NULL; }
    void insert(const string &, const int &, const int &, const int &);
    void preorder();
};

// A recursive function to do preorder traversal
void preorderHelper(player *root)
{
    if (root == NULL)
        return;
    cout << root->Name << " " << root->Rebound << " " << root->Assist << " " << root->Point << endl;
    preorderHelper(root->left);
    preorderHelper(root->right);
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

    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
    {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /* Case : A Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left)
        {

            player *uncle_pt = grand_parent_pt->right;

            /* Case : 1 The uncle of pt is also red Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color ==
                                        RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
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
            if ((uncle_pt != NULL) && (uncle_pt->color == RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
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

    root->color = BLACK;
}

// Function to insert a new node with given data
void RBTree::insert(const string &Name, const int &Rebound, const int &Assist, const int &Point)
{
    player *pt = new player(Name, Rebound, Assist, Point);

    // Do a normal BST insert
    root = BSTInsert(root, pt);

    // fix Red Black Tree violations
    fixViolation(root, pt);
}

// Function to do preorder traversal
void RBTree::preorder() { preorderHelper(root); }

// Driver Code
int main()
{
    RBTree tree;

    tree.insert("Ali Muhammed", 93, 106, 386);
    tree.insert("Ekpe Udoh", 241, 68, 376);
    tree.insert("Jan Vesely", 154, 49, 328);
    tree.insert("Bogdan Bogdanovic", 84, 80, 321);
    tree.insert("Gigi Datome", 122, 35, 303);
    tree.insert("Kostas Sloukas", 62, 130, 268);
    tree.insert("Nikola Kalinic", 101, 51, 249);
    tree.insert("James Nunnally", 67, 58, 192);
    tree.insert("Pero Antic", 75, 19, 130);
    tree.insert("Melih Mahmutoglu", 10, 11, 79);
    tree.insert("Ahmet Duverioglu", 12, 1, 30);
    tree.insert("Anthony Bennett", 9, 2, 12);
    tree.insert("Baris Hersek", 0, 0, 4);
    tree.insert("Berk Ugurlu", 1, 2, 2);
    tree.insert("Egehan Arna", 0, 0, 0);
    tree.insert("Yordan Minchev", 2, 0, 0);
    //tree.insert("Jan Vesely", 174, 53, 424);
    //tree.insert("Brad Wanamaker", 97, 138, 408);
    //tree.insert("Kostas S l o u k a s", 87, 188, 351);
    //tree.insert("G i g i Datome", 117, 38, 336);
    //tree.insert("Nico l o M e l l i", 179, 62, 320);
    //tree.insert("James Nunnally", 59, 39, 269);
    //tree.insert("Marko Guduric", 56, 69, 241);
    //tree.insert("Jason Thompson", 140, 30, 180);
    //tree.insert("A l i Muhammed", 23, 25, 146);
    //tree.insert("N i k o l a K a l i n i c", 30, 23, 104);
    //tree.insert("Ahmet D u v e r i o g l u", 48, 14, 90);
    //tree.insert("Melih Mahmutoglu", 10, 5, 35);
    //tree.insert("Sinan Guler", 9, 7, 23);
    //tree.insert("Egehan Arna", 0, 1, 2);
    //tree.insert("B a r i s Hersek", 0, 0, 0);
    cout << "Inoder Traversal of Created Tree\n";
    tree.preorder();

    return 0;
}
