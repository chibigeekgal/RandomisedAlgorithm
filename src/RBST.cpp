#include "RBST.hpp"
#include <time.h>
#include <stdlib.h>
/***********************************************************/
/******************* PROVIDED FUNCTIONS ********************/
/***********************************************************/

int RBST::add(const Key& key, bool verbose) {
    unsigned int oldSize = m_size;
    m_head = randomAdd(m_head, key);
    if (m_size > oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is added into the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is already in the tree."<<endl;
        }
        return 0;
    }
    if (verbose) cout<<endl;
};

int RBST::del(const Key& key, bool verbose) {
    unsigned oldSize= m_size;
    m_head = del(m_head, key);
    if (m_size < oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is deleted from the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    }
};

int RBST::find(const Key& key, bool verbose) {
    RBSTNode* ret = find(m_head, key);
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is in the tree."<<endl;
        }
        return 1;
    }
};

int RBST::dump(char sep) {
    int ret = dump(m_head, sep);
    cout<<"SIZE: " <<ret<<endl;
    return ret;
};

int RBST::dump(RBSTNode* target, char sep) {
    if (target == NULL) {
        return 0;
    }
    int ret = dump(target->left(), sep);
    cout<< *target<<sep;
    ret ++;
    ret += dump(target->right(), sep);
    return ret;
};



/***********************************************************/
/****************  FUNCTIONS TO BE COMPLETED  ***************/
/***********************************************************/


/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

/* Set the current node's right child to be left child of the current
   node's left child, set the current node to be the right child of
   current node's left child.  */
RBSTNode*  RBST::rightRotate(RBSTNode* target) {
  ////////////// Write your code below  ////////////////////////
  RBSTNode *left = target -> left();
  target->setLeft(left->right());
  left->setRight(target);
  return left;
};

/* Set the current node's left child to be the right child of the
   current node's right child, set the current node to be left child
   of the current node's left child.  */
RBSTNode*  RBST::leftRotate(RBSTNode* target) {
  ////////////// Write your code below  ////////////////////////
  RBSTNode *right = target -> right();
  target->setRight(right->left());
  right->setLeft(target);
  return right;
};

/* Insert the key at target by recursively going down the tree until
   the child of a leaf. E.g. NULL, then a new node containing key is
   returned. */
RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key) {
  countAdd++;
  ////////////// Write your code below  ////////////////////////
  if (target == NULL) {
    m_size++;
    return new RBSTNode(key);
  }

  if (key < target->getKey()) {
    target->setLeft(addRoot(target->left(), key));
    return rightRotate(target);
  } else {
    target->setRight(addRoot(target->right(), key));
    return leftRotate(target);
  }
};

/* Choose a random position from target and its extended subtrees to
   insert from. If the target is chosen, then the key is inserted at
   target, otherwise compare the value of target and the
   key. If key is bigger than target then the whole process is
   repeated on the left node, if it's smaller, then the whole process
   is repeated on the right node.  */
RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
    if (target == NULL) {
      m_size++;
      return new RBSTNode(key);
    }
    int r = rand() % (target->getSize()) + 1;
    if (r == 1) {
      return addRoot(target, key);
    } 

    if (target->getKey() < key) {
      return target->setRight(randomAdd(target->right(), key));
    } else {
      return target->setLeft(randomAdd(target->left(), key));
    }
};

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////

/* If target's key is equal to the key, then the target is
   returned. If target's key is small than the key then the process
   is done on the right child of the target, otherwise the process is
   done on the left child of th target. If the target is NULL then
   the element does not exist in the tree, NULL is returned. */
RBSTNode* RBST::find(RBSTNode* target, const Key& key) {
  countFind++;
  ////////////// Write your code below  ////////////////////////
 
  if (target == NULL) {
    return NULL;
  }
  if(*target == key ){
    return target;
  }
  
  if(*target < key) {
    return find (target -> right(), key);
  } else {
    return find (target -> left(), key);
  }
  
};


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

/* If target is NULL then the key does not exist in the tree, so NULL
   is returned. Otherwise, if target is smaller than the key, then
   the process is repeated on the right child of target, if target is
   bigger than the key, then the process is repeated on the left
   child of target. If target is equal to the key, then perform
   deleteNode on target. */
RBSTNode* RBST::del(RBSTNode* target, const Key& key) {
  countDelete++;
  ////////////// Write your code below  ////////////////////////

  if (target == NULL) {
    return NULL;
  }
  if (*target == key) {
     return deleteNode(target);
  }
  if (*target < key) {
    RBSTNode* right = del(target->right(), key);
    target->setRight(right);
  } else {
    RBSTNode* left = del(target->left(), key);
    target->setLeft(left);
  }  
  return target;
  
};

/* This auxilliary method returns the appropriate node once target is
   deleted. If target is a leaf then NULL is repeated. If left is
   NULL but right is not, then right is returned. If left is not NULL
   but right is then left is returned. If target has both children,
   then the left most node of the right child is taken from its
   position and moved up to be the replacementNode. The right child of
   the replacementNode is the right child of target, the left child
   of the replacementNode is the left child of target. Target is then
   deleted.  */
RBSTNode* RBST:: deleteNode(RBSTNode* target) {
  if (target->right() == NULL && target->left() == NULL) {
    delete target;
    return NULL;
  }
  else if (target->right() == NULL) {
    RBSTNode* left = target -> left();
    delete target;
    return left;
  }
  else if (target->left() == NULL) {
    RBSTNode* right = target -> right();
    delete target;
    return right;
  }
  else {
    RBSTNode *replacementNode = findLeftMost(target->right());
    RBSTNode *newRight = deleteLeftMost(target->right());
    replacementNode->setRight(newRight);
    replacementNode->setLeft(target->left());
    delete target;
    return replacementNode;
  }
}

RBSTNode* RBST:: findLeftMost(RBSTNode* node) {
  if (node->left() == NULL) {
    return node;
  }
  else return findLeftMost(node->left());
}

RBSTNode* RBST:: deleteLeftMost(RBSTNode* node) {
  if (node->left() == NULL) {
    return node->right();
  } else {
    RBSTNode *newChild = deleteLeftMost(node->left());
    node->setLeft(newChild);
    return node;
  }
}
