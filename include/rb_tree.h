#ifndef RB_TREE_H
#define RB_TREE_H

#include "config.h"
#include "perf.h"
#include <vector>

#include "siga.h"
#include "rb_node.h"

using namespace Perf;

// TODO: Implementar a árvore rubro-negra aqui e classes auxiliares (se necessário)
namespace RBTree 
{
template <typename T>
class RedBlackTree
{   

    public:
        RedBlackTree();
        void           insert(T key);
        void           insertFix(RedBlackNode<T> *node);
        void           remove(T key);
        void           removeFix(RedBlackNode<T> *node);
        RedBlackNode<T>*  search(T key);
        RedBlackNode<T>*  searchNode(RedBlackNode<T> *node, T key);

        //~RedBlackTree();
    private:

        void rotateLeft(RedBlackNode<T> *node);
        void rotateRight(RedBlackNode<T> *node);

        RedBlackNode<T> *root;
};

template <typename T>
RedBlackTree<T>::RedBlackTree(): root(nullptr)
{ }

template <typename T>
void RedBlackTree<T>::rotateLeft(RedBlackNode<T> *x)
{
    RedBlackNode<T> *y = x->getRight();
    if(y == nullptr)
        return;
    x->setRight(y->getLeft());
    if (y->getLeft() != nullptr)
        y->getLeft()->setParent(x);
    y->setParent(x->getParent());
    if (x->getParent() == nullptr)
        root = y;
    else if (x == x->getParent()->getLeft())
        x->getParent()->setLeft(y);
    else
        x->getParent()->setRight(y);
    y->setLeft(x);
    x->setParent(y);   
   
}

template <typename T>
void RedBlackTree<T>::rotateRight(RedBlackNode<T> *y)
{

    RedBlackNode<T> *x = y->getLeft();
    if(x == nullptr)
        return;
    y->setLeft(x->getRight());
    if (x->getRight() != nullptr)
        x->getRight()->setParent(y);
    x->setParent(y->getParent());
    if (y->getParent() == nullptr)
        root = x;
    else if (y == y->getParent()->getLeft())
        y->getParent()->setLeft(x);
    else
        y->getParent()->setRight(x);
    x->setRight(y);
    y->setParent(x);

}

template <typename T>
RedBlackNode<T>* RedBlackTree<T>::searchNode(RedBlackNode<T> *node, T key)
{
    if (node == nullptr || node->getKey() == key) {
        return node;
    }

    if (node->getKey() < key) {
        return searchNode(node->getRight(), key);
    }

    return searchNode(node->getLeft(), key);
}

template <typename T>
RedBlackNode<T>* RedBlackTree<T>::search(T key)
{
    RedBlackNode<T> *node = root;
    RedBlackNode<T> *parent = nullptr;

    return searchNode(node, key);
}

template <typename T>
void RedBlackTree<T>::insert(T key)
{ 
   
    RedBlackNode<T> *node = new RedBlackNode<T>(key);
    RedBlackNode<T> *x    = root;
    RedBlackNode<T> *y    = nullptr;
	while( x != nullptr ) {
		y = x;
		if (x->getKey() > key) {
			x = x->getLeft();
		} else {
			x = x->getRight();
		}
	}
	if( root == nullptr) {
		root = node;
	} else if (y->getKey() > key) {
		y->setLeft(node);
	} else {
		y->setRight(node);
	}
	node->setColor( "V");
	node->setParent(y);
	node->setLeft(nullptr);
	node->setRight(nullptr);
	insertFix(node);

}

template <typename T>
void RedBlackTree<T>::insertFix(RedBlackNode<T> *node)
{
  while ( node->getParent()->getColor() == "V" ) {
    if( node->getParent() == node->getParent()->getParent()->getLeft() ) {
      RedBlackNode<T> *y = node->getParent()->getParent()->getRight();
      if( y->getColor() == "V" ) {
        node->getParent()->setColor( "P");
        node->setColor( "P");
        node->getParent()->getParent()->setColor("V");
        node = node->getParent()->getParent();
      } else {
        if ( node == node->getParent()->getRight() ) {
          node = node->getParent();
          rotateLeft(node);
        }
        node->getParent()->setColor("P");
        node->getParent()->getParent()->setColor( "V");
        rotateRight(node->getParent()->getParent());
      }
    } else if( node->getParent() == node->getParent()->getParent()->getRight() ) {
        RedBlackNode<T> *y = node->getParent()->getParent()->getLeft();
        if( y->getColor() == "V" ) {
            node->getParent()->setColor( "P");
            node->setColor( "P");
            node->getParent()->getParent()->setColor( "V");
            node = node->getParent()->getParent();
        } else {
            if ( node == node->getParent()->getLeft() ) {
                node = node->getParent();
                rotateRight(node);
            }
            node->getParent()->setColor( "P");
            node->getParent()->getParent()->setColor( "V") ;
            rotateLeft(node->getParent()->getParent());
      }
    }
  }
  root->setColor( "P");
}

template <typename T>
void RedBlackTree<T>::removeFix(RedBlackNode<T> *node)
{
    RedBlackNode<T> y;
    while (node != root && node->getColor() == "P") {
      if (node == node->getParent()->getLeft()) {
        y = node->getParent()->getRight();
        if (y->getColor() == "V") {
          y->setColor("P");
          node->getParent()->setColor("V");
          rotateLeft(node->getParent());
          y = node->getParent()->getRight();
        }

        if (y->getLeft()->getColor() == "P" && y->getRight()->getColor() == "P") {
          y->setColor("V");
          node = node->getParent();
        } else {
          if (y->getRight()->getColor() == "P") {
            y->getLeft()->setColor("P");
            y->setColor("V");
            rotateRight(y);
            y = node->getParent->getRight();
          }

          y->setColor(node->getParent()->getColor());
          node->getParent()->setColor("P");
          y->getRight()->setColor("P");
          rotateLeft(node->getParent());
          node = root;
        }
      } else {
        y = node->getParent()->getLeft();
        if (y->getColor() == "V") {
          y->setColor("P");
          node->getParent()->getColor("V");
          rotateRight(node->getParent());
          y = node->getParent()->getLeft();
        }

        if (y->getRight()->getColor() == "P" && y->getRight()->getColor() == "P") {
          y->setColor("V");
          node = node->getParent();
        } else {
          if (y->getLeft()->getColor() == "P") {
            y->getRight()->setColor("P");
            y->setColor("V");
            rotateLeft(y);
            y = node->getParent()->getLeft();
          }

          y->setColor(node->getParent()->getColor());
          node->getParent()->setColor("P");
          y->getLeft()->setColor("P");
          rotateRight(node->getParent());
          node = root;
        }
      }
    }
    node->setColor("P");
  }

template <typename T>
void RedBlackTree<T>::remove(T key)
{    
    RedBlackNode<T> *node = search(key);
    RedBlackNode<T> *x    = nullptr;
    RedBlackNode<T> *y    = nullptr;

    string cor_no = node->getColor();
    if (node->getLeft() == nullptr) {
      x = node->getRight();
      if (node->getParent() == nullptr) {
        root = node->getRight();
      } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(node->getRight());
      } else {
        node->getParent()->setRight(node->getRight());
      }
        node->getRight()->setParent(node->getParent());
    } else if (node->getRight() == nullptr) {
      x = node->getLeft();

      if (node->getParent() == nullptr) {
        root = node->getRight();
      } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(node->getLeft());
      } else {
        node->getParent()->setRight(node->getLeft());
      }
        node->getLeft()->setParent(node->getParent());
    } else {
      y = node->getRight();
      while (y->getLeft() != nullptr) {
        y = y->getLeft();
      }
      cor_no = node->getColor();
      x = y->getRight();
      if (y->getParent() == node) {
        x->setParent(y);
      } else {
        
        if (y->getParent() == nullptr) {
          root = y->getRight();
        } else if (y == y->getParent()->getLeft()) {
          y->getParent()->setLeft(y->getRight());
        } else {
          y->getParent()->setRight(y->getRight());
        }
          y->getRight()->setParent(y->getParent());
        y->setRight(node->getRight);
        y->getRight()->setParent(y);
      }

      if (node->getParent() == nullptr) {
        root = y;
      } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(y);
      } else {
        node->getParent()->setRight(y);
      }
        y->setParent(node->getParent());

      y->setLeft(node->getLeft());
      y->getLeft()->setParent(y);
      y->setColor(node->getColor());
    }
    delete node;
    if (cor_no == "P") {
      deleteFix(x);
    }
  }

}






#endif /* RB_TREE_H */
