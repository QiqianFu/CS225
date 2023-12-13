#include<iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  clear();

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  ListNode *now_node = head_;
  ListNode *next_node = now_node;
  while (now_node  != tail_ && now_node !=NULL){
    next_node = now_node->next;
    delete now_node;
    now_node = next_node;
  }
  length_ =0 ;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  if (empty()){
    ListNode *new_node = new ListNode(ndata);
  
    head_ = new_node;
    tail_ = head_;
    length_++;
    return;
  }
  ListNode *new_node = new ListNode(ndata);
  new_node->next = head_;
  head_->prev = new_node;
  head_ = new_node;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  if (empty()){
    ListNode *new_node = new ListNode(ndata);
    tail_ = new_node;
    head_ = new_node;
    length_++;
    return;
  }
  ListNode *new_node = new ListNode(ndata);
  new_node->prev = tail_;
  tail_->next = new_node;
  tail_ = new_node;
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
  if(startPoint==endPoint){
    return;
  }
  if (startPoint == NULL || endPoint == NULL){
    return;
  }
  ListNode *now_oper = endPoint;
  ListNode *end   = endPoint;
  ListNode *stop  = startPoint;
  ListNode *next  = now_oper->prev;
  while(now_oper->prev != NULL && now_oper != stop){
    now_oper->next = next;
    next  = next->prev;
    now_oper->next->prev = now_oper;
    now_oper = now_oper->next;
  }

  end->prev = NULL;

  stop ->next = NULL;

  
  head_= endPoint;
  tail_= startPoint;







  // while (temp != NULL && temp != stop){
  //   temp = now_oper->prev;
  //   if (temp == stop){
  //     now_oper ->next = end;
  //     now_oper->prev  = NULL;
  //     temp->next = NULL;
  //     end->prev = now_oper;
  //     end = now_oper;
  //     head_ =end;
  //     tail_ =stop;
  //     std::cout <<"wft"<<std::endl;
  //     break;
  //   }
  //   now_oper ->next = end;
  //   now_oper->prev  = NULL;
  //   temp->next = NULL;
  //   end->prev = now_oper;
  //   end = now_oper;
  //   std::cout <<"w11ft"<<std::endl;

  //   now_oper = temp;


  // }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  if (n==0 || n==1){
    return;
  }
  if (n >= length_){
    reverse();
    return;
  }
  ListNode *temp1, *temp2, *temp_head;
  ListNode *next_start, *before_end ;
  temp1 = head_;
  temp2 = temp1;
  int flag = 1;
  int signal =1;
  while (flag){
    for (int i = 0 ; i < n-1 ; i++){
      if (temp2->next==NULL ){
        flag= 0;
        tail_ = temp1;
        break;
      }
      temp2 = temp2->next;

    }
    next_start = temp2->next;
    reverse(temp1,temp2);
    
    if (signal){
      temp_head = temp2;
      signal = 0; 
      before_end = temp1;
    }else{
      temp2->prev = before_end;
      before_end->next = temp2;
      before_end = temp1;
    }

    if (next_start==NULL){
      head_  = temp_head;
      tail_  = temp1;
      return;
    }
    temp1 = next_start;
    temp2 = temp1;

  }

  reverse(temp1,temp2);
  head_ = temp_head;

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  ListNode * now_node = head_->next;

  while(now_node->next != NULL ){
    ListNode *skip_node = now_node->next;
    skip_node->prev = now_node->prev;
    now_node->prev->next = skip_node;
    now_node->next = NULL;
    now_node->prev = tail_;
    tail_->next = now_node;
    tail_ = now_node;
    now_node = skip_node->next;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
  if (splitPoint == 0 ){
    return start;
  }
  ListNode *now = start;
  for(int i = 0; i <splitPoint;i++){
    now = now->next;
  }
  now->prev->next = NULL;
  now->prev       = NULL;
  return now;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  ListNode* the_first = first;
  ListNode* the_second= second;
  ListNode* now = NULL;
  ListNode* the_head = first;
  if (second == NULL){
    return the_head;
  }
  if (the_second->data < the_first->data){
    the_head = the_second;
  }
  while (the_first != NULL || the_second != NULL){
    if (the_first != NULL){
      if(the_second == NULL || the_first->data < the_second->data ){
        if(now ==NULL){
          the_first->prev = now;
          now = the_first;
          the_first = the_first->next;
        }else{
          now->next = the_first;
          the_first->prev = now;
          now = the_first;
          the_first = the_first->next;
        }

      }else{
        if(now == NULL){
          the_second->prev = now;
          now = the_second;
          the_second = the_second->next;
        }else{
          now->next = the_second;
          the_second->prev = now;
          now = the_second;
          the_second = the_second->next;
        }

      }
    }else{
      if(now == NULL){
        the_second->prev = now;
        now = the_second;
        the_second = the_second->next;
      }else{
        now->next = the_second;
        the_second->prev = now;
        now = the_second;
        the_second = the_second->next;
      }
    }
  

  }
  return the_head;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
  if (chainLength == 1){
    return start;
  }
  int len1 = int(chainLength/2);
  int len2 = chainLength -len1;
  ListNode* start2 = split(start,len1);
  ListNode* node1, *node2, *node3;
  node1 = mergesort(start, len1);
  node2 = mergesort(start2, len2);
  node3 = merge(node1,node2);
  return node3;
}