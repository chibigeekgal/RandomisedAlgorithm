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

/* Approximate the ideal situation using randomisation. As it gives
   the same probability inserting on all the levels, which would give
   a balanced tree. */
unsigned int SkipList::randHeight() {
  unsigned int height = 0;
  int t = rand();
  int j = 2;
  for (height = 1; height < m_maxHeight; height++) {
    if (t > (RAND_MAX / j)) {
      break;
    }
    j = j * 2;
  }
  return height;
}

/* Find the correct position to insert the newNode at current level, 
   and link the levels below the current level until level 0 is
   reached. If the SkipListNode contains the same key as the newNode
   is already in the list, then the insertion fails. */
int SkipList::add(SkipListNode* target, SkipListNode* newNode, unsigned int level) {
  if (target->nextAtLevel(level) != NULL &&
      (*target->nextAtLevel(level)) < *newNode) {
    countAdd++;
  }
  ////////////// Write your code below  ///////////////////////
  SkipListNode *next = target->nextAtLevel(level);
  if (next != NULL && *next == *newNode) {
    return false;
  }
  if (next == NULL || *next > *newNode) {
    if (level < newNode->height()) {
      newNode->setNextAtLevel(level, next);
      target->setNextAtLevel(level, newNode);
    }
    if (level > 0) {
      return add(target, newNode, level - 1);
    } else {
      return true;
    }
  }
  return add(next, newNode, level);
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////

/* Search the key at the current level, if it is not found, then move
   down a level until level 0 is reached. If it is still not found 
   then the key is not in the list, otherwise the SkipListNode that
   contains key is returned. */
SkipListNode* SkipList::find(SkipListNode* target, const Key& key, unsigned int level) {
  if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
    countFind++;
  }
  if (target == NULL)
    return NULL;
  if(*target == key) 
    return target;
  SkipListNode *next = target->nextAtLevel(level); 
  if (next == NULL || key < *next) {
    if (level == 0)
      return NULL;
    return find(target, key, level - 1);
  }
  return find(next, key, level);
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////

/* Search through the list until the SkipListNode containing key is
   found or returning NULL. If the node is found, then delete links
   between the node's and its prev, next, and link prev and next,
   until level 0 is reached, and the node is returned. */
SkipListNode* SkipList::del(SkipListNode* target, const Key& key, unsigned int level) {
  if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
    countDelete++;
  }
  ////////////// Write your code below  ////////////////////////

  SkipListNode *next = target->nextAtLevel(level); 
  
  if(next != NULL && *next == key) {
    target->setNextAtLevel(level, next->nextAtLevel(level));
    if (level > 0) {
      return del(target, key, level - 1);
    } else {
      return next;
    }
  } else if(next == NULL || key < *next) {
    if (level == 0) {
      return NULL;
    }
    return del(target, key, level - 1);
  }
  return del(next, key, level);
}
