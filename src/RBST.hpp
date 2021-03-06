#ifndef RBST_HPP_
#define RBST_HPP_

#include <iostream>
#include <assert.h>
#include <vector>
#include <math.h>
#include "Key.hpp"
#include "DataStructure.hpp"

using namespace std;

class RBSTNode;
class RBSTNode: public Key {
public:
  RBSTNode(const Key& key):Key(key),m_left(NULL),m_right(NULL) { size = 1; }
    virtual ~RBSTNode() {}

    string getKey() {
        return *this;
    }
 
    string setKey(const Key& key) {
        assign(key);
        return Key(key);
    }

    RBSTNode* left() {
        return m_left;
    }
    RBSTNode* right() {
        return m_right;
    }

    RBSTNode* setLeft (RBSTNode* left) {
        m_left = left;
        recalculate_size(); 
        return this;
    }
    RBSTNode* setRight (RBSTNode* right) {
        m_right =right;
        recalculate_size(); 
        return this;
    }

  /* Calculate the size of the node, called everytime one of the
     child of the node changes, e.g. when setLeft and setRight is
     called.  */
  void recalculate_size () {
    int left_size = m_left == NULL ? 0 : m_left->size;
    int right_size = m_right == NULL ? 0 : m_right->size; 
    size = 1 + left_size + right_size;
  }
  int getSize () {
    return size; 
  }
  
private:
    RBSTNode() {}
    RBSTNode* m_left;
    RBSTNode* m_right;
    unsigned int size; //The number of elements that extends the
		       //current node 
};


class RBST : public DataStructure {
public:
    RBST():m_head(NULL),m_size(0){};
    virtual ~RBST() {};

    //ADD FUNCTIONS
    int add(const Key& key, bool verbose=false);
    
    //FIND FUNCTIONS
    int find(const Key& key, bool verbose = false);

    //DEL FUNCTIONS
    int del(const Key& key, bool verbose=false);

    //DUMP FUNCTIONS
    int dump(char sep = ' ');
    int dump(RBSTNode* target, char sep);

private:
  RBSTNode* randomAdd(RBSTNode* target, const Key& key);
  RBSTNode* addRoot(RBSTNode* target, const Key& key);
  RBSTNode*  rightRotate(RBSTNode* target);
  RBSTNode*  leftRotate(RBSTNode* target);
  RBSTNode* deleteNode(RBSTNode* target);
  RBSTNode* findLeftMost(RBSTNode* node);
  RBSTNode* deleteLeftMost(RBSTNode* node);
  RBSTNode* del(RBSTNode* target, const Key& key);
  RBSTNode* find(RBSTNode* target, const Key& key);
  
  RBSTNode* m_head;
  unsigned int m_size;
};

#endif /*RBST_HPP_*/
