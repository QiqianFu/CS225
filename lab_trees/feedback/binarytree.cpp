/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
    cout<<endl;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::mirror(Node* root){
    if (root == NULL){
        return NULL;
    }
    Node* left, *right;
    left = mirror(root->right);
    right = mirror(root->left);
    root->left = left;
    root->right = right;
    return root;
} 

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    vector<T> list;
    isOrdered(root,list);
    for(long unsigned int i = 1; i < list.size() ; i++){
        if (list[i-1] >= list[i]){
            return false;
        }

    }
    return true;
}

template <typename T>
void BinaryTree<T>::isOrdered(Node* root, vector<T> &list) const
{
    if(root->left==NULL && root->right==NULL){
        list.push_back(root->elem);
    }else if(root->right == NULL){
        isOrdered(root->left , list);
        list.push_back(root->elem);
    }else if(root->left == NULL){
        list.push_back(root->elem);  
        isOrdered(root->right , list);
    }else{
        isOrdered(root->left , list);
        list.push_back(root->elem);  
        isOrdered(root->right , list);  
    }

    

}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    vector<T> new_vector;
    paths.push_back(new_vector);
    printPaths(paths, root);

}
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths, Node* root) const
{
    if (root->left==NULL && root->right==NULL){
        paths[paths.size()-1].push_back(root->elem);
        return;
    }
    else if (root->left ==NULL){
        paths[paths.size()-1].push_back(root->elem);
        printPaths(paths, root->right);
        return;
    }
    else if (root->right == NULL){
        paths[paths.size()-1].push_back(root->elem);
        printPaths(paths, root->left);
        return;
    }else{
        paths[paths.size()-1].push_back(root->elem);  
        vector<T> new_vector(paths.back());
        printPaths(paths, root->left);
        paths.push_back(new_vector);
        printPaths(paths, root->right);
        return;
    }


    
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    int now = -1;
    return sumDistances(root, now);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node* root, int now) const{
    if(root==NULL){
        return 0;
    }
    now++;
    return now + sumDistances(root->left, now) + sumDistances(root->right, now);
}
