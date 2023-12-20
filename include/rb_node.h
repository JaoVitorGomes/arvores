#ifndef RB_NODE_H__
#define RB_NODE_H__


#include <iostream>
#include <string>
using namespace std;

template <typename T>
class RedBlackTree;

template <typename T>
class RedBlackNode
{
    friend class RedBlackTree<T>;
    public:
    
        RedBlackNode(T key);
        RedBlackNode(T key, RedBlackNode<T> *left, RedBlackNode<T> *right);
        RedBlackNode<T>* getLeft();
        RedBlackNode<T>* getRight();
        RedBlackNode<T>* getParent();
        string    getColor();
        T    getKey();
        void setKey(T key);
        void setLeft(RedBlackNode<T> *left);
        void setRight(RedBlackNode<T> *right);
        void setParent(RedBlackNode<T> *parent);
        void setColor(string color);
        
  private:
    T          key;
    RedBlackNode *left;
    RedBlackNode *right;
    RedBlackNode *parent;
    string color;
};

template <typename T>
RedBlackNode<T>::RedBlackNode(T key): key(key), left(nullptr), right(nullptr), parent(nullptr), color("")
{ }

template <typename T>
RedBlackNode<T>::RedBlackNode(T key, RedBlackNode<T> *left, RedBlackNode<T> *right): key(key), left(left), right(right), parent(nullptr), color("")
{ }

template <typename T>
T RedBlackNode<T>::getKey()
{
    return key;
}

template <typename T>
RedBlackNode<T>* RedBlackNode<T>::getLeft()
{
    return left;
}

template <typename T>
RedBlackNode<T>* RedBlackNode<T>::getRight()
{
    return right;
}

template <typename T>
RedBlackNode<T>* RedBlackNode<T>::getParent()
{
    return parent;
}

template <typename T>
string RedBlackNode<T>::getColor()
{
    return color;
}

template <typename T>
void RedBlackNode<T>::setLeft(RedBlackNode<T> *left)
{
    this->left = left;
}
template <typename T>
void RedBlackNode<T>::setRight(RedBlackNode<T> *right)
{
    this->right = right;
}

template <typename T>
void RedBlackNode<T>::setParent(RedBlackNode<T> *parent)
{
    this->parent = parent;
}

template <typename T>
void RedBlackNode<T>::setColor(string color)
{
    this->color = color;
}

template <typename T>
void RedBlackNode<T>::setKey(T key)
{
    this->key = key;
}

#endif 
