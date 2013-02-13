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
  /* RBSTNode *left = left(target);
  target->setLeft(right(target));
  left->setRight(target);
  return left;*/
  RBSTNode *left = target -> left();
  left -> right() -> setLeft(target);
  target -> setRight(left);
  return left;
};

RBSTNode*  RBST::leftRotate(RBSTNode* target) {
  ////////////// Write your code below  ////////////////////////
  /*  RBSTNode *right = right(target);
  target->setRight(left(right));
  right->setLeft(target);*/
  //  return target;
  RBSTNode *right = target -> right();
  right -> left() -> setRight(target);
  target -> setLeft(right);
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
    srand(time(NULL));
    int r = rand() % ((m_size) + 1);
    if(r == 0) {
      return addRoot(target, key);
    } 

    if (*target < key) {
      return addRoot(target -> right(), key);
    } else {
      return addRoot(target -> left(), key);
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
    RBSTNode* right = del(target -> right(), key);
    target -> setRight(right);
    return right;
  } else {
    RBSTNode* left = del(target -> left(), key);
    target -> setLeft(left);
    return left;
  }  
};

RBSTNode* RBST:: deleteNode(RBSTNode* target, const Key& key) {
  if(target == NULL) {
    return NULL;
  }
}
