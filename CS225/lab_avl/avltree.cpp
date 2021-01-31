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
    // your code here
    Node * newHead = t->right;
    Node * newHeadLeft = newHead->left;
    
    newHead->left = t;
    t->right = newHeadLeft;

    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    newHead->height = std::max(heightOrNeg1(newHead->left), heightOrNeg1(newHead->right)) + 1;

    t = newHead;
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
    Node * newHead = t->left;
    Node * newHeadRight = newHead->right;
    
    newHead->right = t;
    t->left = newHeadRight;

    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    newHead->height = std::max(heightOrNeg1(newHead->left), heightOrNeg1(newHead->right)) + 1;

    t = newHead;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here

    if (subtree == NULL)
    {
        return;
    }
    
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance >= 2)
    {
        int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (r_balance == 1)
        {
            rotateLeft(subtree);
        }else if (r_balance == -1)
        {
            rotateRightLeft(subtree);
        }
    }
    if (balance <= -2)
    {
        int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (l_balance == -1)
        {
            rotateRight(subtree);
        }else if (l_balance == 1)
        {
            rotateLeftRight(subtree);
        }
    }

    // update height
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL)
    {
        subtree = new Node(key, value);
    }
    else if (key > subtree->key)
    {
        insert(subtree->right, key, value);
    }
    else if (key < subtree->key)
    {
        insert(subtree->left, key, value);
    }
    
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
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
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * tmp = subtree->left;

            // find most right
            while (tmp->right != NULL)
            {
                tmp = tmp->right;
            }
            
            swap(subtree, tmp);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node * subLeft = subtree->left;
            Node * subRight = subtree->right;

            if (subLeft != NULL)
            {
                Node * tmp = subtree;
                subtree = subLeft;
                delete tmp;
                tmp = NULL;
            }
            if (subRight != NULL)
            {
                Node * tmp = subtree;
                subtree =subRight;
                delete tmp;
                tmp = NULL;
            }
        }
        // your code here
    }
    rebalance(subtree);
}
