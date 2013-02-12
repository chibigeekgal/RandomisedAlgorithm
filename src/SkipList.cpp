#include "SkipList.hpp"
#include <time.h>
/***********************************************************/
/********************** PROVIDED FUNCTIONS *****************/
/***********************************************************/
void SkipList::init(int maxHeight) {
    m_maxHeight = maxHeight;
    m_head = new SkipListNode("", m_maxHeight);
}

SkipList::~SkipList() {
    while (m_head != NULL) {
        SkipListNode* head = m_head;
        m_head = m_head->nextAtLevel(0);
        delete head;
    }
}

int SkipList::add(const Key& key, bool verbose) {
    if (find(key, false) != 0) {
        if (verbose) {
            cout<<"Node "<<key<<" is already in the list."<<endl;
        }
        return 0;
    }

    SkipListNode* newNode = new SkipListNode(key, randHeight());
    if (verbose) {
        cout<<"Add new node "<<*newNode<<" with height "<<newNode->height()<<endl;
    }
    int ret = add (m_head, newNode, m_maxHeight-1);
    if (ret == 0 ) {
        return ret;
    }
    return 1;
}

int SkipList::find(const Key &key, bool verbose) {
    SkipListNode* ret =find (m_head, key, m_maxHeight-1) ;
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<< "Node "<<key<<" is in the list"<<endl;
        }
        return 1;
    }

}
int SkipList::del(const Key& key, bool verbose) {
    if (key.length() == 0){
      return 1;
    }
    SkipListNode* toBeDeleted  = del(m_head, key, m_maxHeight-1);

    if (toBeDeleted == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
    } else {
        delete toBeDeleted;
        if (verbose) {
            cout<< "Node "<<key<<" is deleted from the list"<<endl;
        }
    }
    return 1;
}

void SkipList::dump(char sep) {
    int length = -1;
    cout<<"Current List: ";
    for ( SkipListNode* iter = m_head; (iter != NULL); iter=iter->nextAtLevel(0)) {
        length++;
        cout << string(*iter)<<" ";
        cout <<"("<< iter->height() <<":";
        unsigned int i;
        for (i=0; i< iter->height(); i++) {
            if (iter->nextAtLevel(i)) {
                cout<<" "<<i<<":"<<*(iter->nextAtLevel(i));
                cout.flush();
            }
        }
        cout<<")"<<sep;
    }
    cout<<length<<" nodes in total."<<endl;
}


/***********************************************************/
/***************  FUNCTIONS TO BE COMPLETED  ****************/
/***********************************************************/

/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

unsigned int SkipList::randHeight() {
  int height;

  /* initialize random seed. */
  srand(time(NULL));
  
  /* generate random height. */
  height = rand() % (m_maxHeight + 1);
  
  return height;
}


int SkipList::add(SkipListNode* target, SkipListNode* newNode, unsigned int level) {
    if (target->nextAtLevel(level) != NULL &&
            (*target->nextAtLevel(level)) < *newNode) {
        countAdd++;
    }
    ////////////// Write your code below  ////////////////////////
    SkipListNode *next = target->nextAtLevel(level);
    if (target == newNode) {
      return 0;
    }
    if (next == NULL || *next > *newNode) {
      if (level < newNode->height()) {
	newNode->setNextAtLevel(level, next);
	target->setNextAtLevel(level, newNode);
      }
      if (level > 0) {
	add(target, newNode, level - 1);
      }
      return 1;
    } else {
      return add(next, newNode, level);
    }
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::find(SkipListNode* target, const Key& key, unsigned int level) {
  if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
    countFind++;
  }
  ////////////// Write your code below  ////////////////////////
  if (*target == key) {
    return target;
  }
  SkipListNode *next = target->nextAtLevel(level);
  if (next == NULL || *next > key) {
    return find(target, key, level - 1);
  } else {
    return find(next, key, level);
  }
  return NULL;
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::del(SkipListNode* target, const Key& key, unsigned int level) {
  if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
    countFind++;
  }
  ////////////// Write your code below  ////////////////////////
  SkipListNode *next = target->nextAtLevel(level);
  if (level < 0) {
    return next;
  }
  if (*next == key) {
    target->setNextAtLevel(level, next->nextAtLevel(level));
    return del(target, key, level - 1);
  }
  if (next == NULL || *next > key) {
    return del(target, key, level -1);
  } else {
    return del(next, key, level);
  }
}
