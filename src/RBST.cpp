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

RBSTNode*  RBST::rightRotate(RBSTNode* target) {
  ////////////// Write your code below  ////////////////////////
  RBSTNode *left = target -> left();
  RBSTNode *right_of_left = left->right();
  target->setLeft(right_of_left);
  left->setRight(target);
  return left;
};

RBSTNode*  RBST::leftRotate(RBSTNode* target) {
  ////////////// Write your code below  ////////////////////////
  RBSTNode *right = target -> right();
  RBSTNode *left_of_right = right->left(); 
  target->setRight(left_of_right);
  right->setLeft(target);
  return right;
};

RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key) {
  countAdd++;
  ////////////// Write your code below  ////////////////////////
  if (target == NULL) {
    m_size++;
    target = new RBSTNode(key);
    return target;
  }

  if (key < target->getKey()) {
    target->setLeft(addRoot(target->left(), key));
    return rightRotate(target);
  } else {
    target->setRight(addRoot(target->right(), key));
    return leftRotate(target);
  }
};


RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
    if (target == NULL) {
      m_size++;
      return new RBSTNode(key);
    }
    srand(time(NULL));
    int r = rand() % (target->getHeight()) + 1;
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
