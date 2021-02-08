// C++ program for B-Tree insertion
#include <iostream>
using namespace std;

class box
{
private:
    /* data */
public:
    int x;
    int y;
    char z;
    box(){};
    box(int nx, int ny, char nz)
    {
        x = nx;
        y = ny;
        z = nz;
    };
    ~box(){};
};

// A BTree node
class BTreeNode
{
    box *keys;     // An array ofstring keys
    int t;         // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;         // Current number of keys
    bool leaf;     // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf); // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(const box &k);
    void insertNonFullx(const box &k);
    void insertNonFully(const box &k);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[]. The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);

    // A function to traverse all nodes in a subtree rooted with this node
    //void traverse();

    // A function to search a key in the subtree rooted with this node.
    BTreeNode *search(box &k);  // returns NULL if k is not present.
    BTreeNode *searchx(box &k); // returns NULL if k is not present.
    BTreeNode *searchy(box &k); // returns NULL if k is not present.

    // Make BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;           // Minimum degree
public:
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    BTreeNode *getRoot()
    {
        return root;
    }
    // function to traverse the tree
    /*void traverse()
    {
        if (root != NULL)
            root->traverse();
    }*/
    void prefixorder(BTreeNode *);

    // function to search a key in this tree
    BTreeNode *search(box &k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }
    BTreeNode *searchx(box &k)
    {
        return (root == NULL) ? NULL : root->searchx(k);
    }
    BTreeNode *searchy(box &k)
    {
        return (root == NULL) ? NULL : root->searchy(k);
    }

    // The main function that inserts a new key in this B-Tree
    void insert(const box &k);
    void insertx(const box &k);
    void inserty(const box &k);
};

void BTree::prefixorder(BTreeNode *r)
{
    if (!r)
    {
        return;
    }
    for (int i = 0; i < r->n; i++)
    {
        cout << "(" << r->keys[i].x << "," << r->keys[i].y << "," << r->keys[i].z << ")";
    }
    cout << endl;

    int i = 0;
    prefixorder(r->C[i]);

    for (int x = 0; x < 6; x++)
    {
        prefixorder(r->C[++i]);
    }
}

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new box[2 * t - 1];
    C = new BTreeNode *[2 * t];

    // Initialize the number of keys as 0
    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
/*void BTreeNode::traverse()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}*/

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(box &k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k.z > keys[i].z)
        i++;

    // If the found key is equal to k, return this node
    if (keys[i].z == k.z)
        return this;

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;

    // Go to the appropriate child
    return C[i]->search(k);
}

BTreeNode *BTreeNode::searchx(box &k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k.x > keys[i].x)
        i++;

    // If the found key is equal to k, return this node
    if (keys[i].x == k.x)
        return this;

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;

    // Go to the appropriate child
    return C[i]->search(k);
}

BTreeNode *BTreeNode::searchy(box &k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k.y > keys[i].y)
        i++;

    // If the found key is equal to k, return this node
    if (keys[i].y == k.y)
        return this;

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;

    // Go to the appropriate child
    return C[i]->search(k);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(const box &k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k; // Insert key
        root->n = 1;       // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now. Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0].z < k.z)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        }
        else // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}

void BTree::insertx(const box &k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k; // Insert key
        root->n = 1;       // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now. Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0].x < k.x)
                i++;
            s->C[i]->insertNonFullx(k);

            // Change root
            root = s;
        }
        else // If root is not full, call insertNonFull for root
            root->insertNonFullx(k);
    }
}

void BTree::inserty(const box &k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k; // Insert key
        root->n = 1;       // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now. Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0].y < k.y)
                i++;
            s->C[i]->insertNonFully(k);

            // Change root
            root = s;
        }
        else // If root is not full, call insertNonFull for root
            root->insertNonFully(k);
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(const box &k)
{
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i].z > k.z)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i].z > k.z)
            i--;

        // See if the found child is full
        if (C[i + 1]->n == 2 * t - 1)
        {
            // If the child is full, then split it
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two. See which of the two
            // is going to have the new key
            if (keys[i + 1].z < k.z)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::insertNonFullx(const box &k)
{
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i].x > k.x)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i].x > k.x)
            i--;

        // See if the found child is full
        if (C[i + 1]->n == 2 * t - 1)
        {
            // If the child is full, then split it
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two. See which of the two
            // is going to have the new key
            if (keys[i + 1].x < k.x)
                i++;
        }
        C[i + 1]->insertNonFullx(k);
    }
}

void BTreeNode::insertNonFully(const box &k)
{
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i].y > k.y)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i].y > k.y)
            i--;

        // See if the found child is full
        if (C[i + 1]->n == 2 * t - 1)
        {
            // If the child is full, then split it
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two. See which of the two
            // is going to have the new key
            if (keys[i + 1].y < k.y)
                i++;
        }
        C[i + 1]->insertNonFully(k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // Link the new child to this node
    C[i + 1] = z;

    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];

    // Increment count of keys in this node
    n = n + 1;
}

// Driver program to test above functions
int main()
{
    int loop;
    int degree;
    char state;

    cin >> loop;
    cin >> degree;
    cin >> state;

    BTree t(degree); // A B-Tree with minium degree 3
    if (state == 'z')
    {
        for (int i = 0; i < loop; i++)
        {
            int x;
            int y;
            char z;
            cin >> x;
            cin >> y;
            cin >> z;
            box *newbox;
            newbox = new box(x, y, z);
            t.insert(*newbox);
        }
    }
    else if (state == 'x')
    {
        for (int i = 0; i < loop; i++)
        {
            int x;
            int y;
            char z;
            cin >> x;
            cin >> y;
            cin >> z;
            box *newbox;
            newbox = new box(x, y, z);
            t.insertx(*newbox);
        }
    }
    else if (state == 'y')
    {
        for (int i = 0; i < loop; i++)
        {
            int x;
            int y;
            char z;
            cin >> x;
            cin >> y;
            cin >> z;
            box *newbox;
            newbox = new box(x, y, z);
            t.inserty(*newbox);
        }
    }

    /*
    box box1 = box(56, 34, 'G');
    box box2 = box(71, 6, 'M');
    box box3 = box(68, 0, 'P');
    box box4 = box(123, -666, 'T');
    box box5 = box(999, 4, 'X');
    box box6 = box(41, 33, 'A');
    box box7 = box(-66, 8, 'B');
    box box8 = box(748, 54, 'C');
    box box9 = box(99, 978, 'D');
    box box10 = box(400, 23, 'E');
    box box11 = box(98, 66, 'J');
    box box12 = box(0, 43, 'K');
    box box13 = box(66, 12, 'N');
    box box14 = box(45, 1, 'O');
    box box15 = box(11, -34, 'Q');
    box box16 = box(67, -36, 'R');
    box box17 = box(40, 7, 'S');
    box box18 = box(85, 3, 'U');
    box box19 = box(8, 2, 'V');
    box box20 = box(62, 9, 'Y');
    box box21 = box(9, 5, 'Z');
    */
    //t.insert(*newbox);
    //t.insert(box(56, 21, 'g'));
    /*
    t.insert(box1);
    t.insert(box2);
    t.insert(box3);
    t.insert(box4);
    t.insert(box5);
    t.insert(box6);
    t.insert(box7);
    t.insert(box8);
    t.insert(box9);
    t.insert(box10);
    t.insert(box11);
    t.insert(box12);
    t.insert(box13);
    t.insert(box14);
    t.insert(box15);
    t.insert(box16);
    t.insert(box17);
    t.insert(box18);
    t.insert(box19);
    t.insert(box20);
    t.insert(box21);
    */
    //cout << "Traversal of the constucted tree is ";
    t.prefixorder(t.getRoot());

    /*int k = 6;
    (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    k = 15;
    (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";*/

    return 0;
}