/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node *temp = t;
    t = temp->right;
    temp->right = t->left;
    t->left  = temp;
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *temp = t;
    t = temp->left;
    temp->left = t->right;
    t->right = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{

    if (subtree == NULL){
        return;
    }
    update_height(subtree);
    int factor = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    if(factor>1){
        int factor2 = heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right);
        if(factor2 == 1){
            rotateRight(subtree);
        }else{
            rotateLeftRight(subtree);
        }
    }else if(factor<-1){
        int factor2 = heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right);
        if(factor2 == -1){
            rotateLeft(subtree);
        }else{
            rotateRightLeft(subtree);
        }
    }

    // your code here
}


template <class K, class V>
int AVLTree<K, V>::help_function(Node*& subtree){
    if(subtree == NULL){
        return -1;
    }
    if(subtree->left == NULL && subtree->right == NULL){
        return 0;
    }else{
        if(subtree->left == NULL){
            return 1 + help_function(subtree->right);
        }else if(subtree->right == NULL){
            return 1 + help_function(subtree->left);
        }else{
            int a = help_function(subtree->left) > help_function(subtree->right)? help_function(subtree->left) : help_function(subtree->right);
            return 1 + a;   
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::update_height(Node*& subtree){
    if(subtree == NULL){
        return;
    }
    subtree->height = help_function(subtree);
    update_height(subtree->left);
    update_height(subtree->right);
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if(subtree==NULL){
        Node* newnode = new Node(key, value);
        subtree = newnode;
    }
    if(subtree->key < key){
        if(subtree->right == NULL){
            subtree->right = new Node(key,value);
        }else{
            insert(subtree->right, key, value);
        }
    }else if(subtree->key > key){
        if(subtree->left == NULL){
            subtree->left = new Node(key,value);
        }else{
            insert(subtree->left, key, value);
        }
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}
template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node * max_point = find_max(subtree->left);
            swap(max_point, subtree);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            if(subtree->left == NULL){
                swap(subtree,subtree->right);
                remove(subtree->right, key);
            }else{
                swap(subtree->left,subtree);
                remove(subtree->left, key);
            }
        }
        // your code here
    }
    rebalance(subtree);
}



template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::find_max(Node*& subtree){
    if(subtree->right ==NULL){
        return subtree;
    }else{
        return find_max(subtree->right);
    }
}