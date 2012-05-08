template<typename Node_type>
// equality_comparable<Node_type>
Node_type* delete_node(Node_type* head, Node_type* victim)
{
  Node_type* n = head;
  if(*n == *victim){ //equality comparable
    head = head->next;
    delete n;
    return head;
  }
  while(n->next){
    if(*(n.next) == *victim){
      Node_type* temp = n.next;
      n.next = n.next.next;
      delete temp;
      break;
    }
  }
return head;
}

template<typename Node_type>
// equality_comparable<Node_type>
Node_type* nth_to_last(Node_type* head, unsigned int n)
{
  if(!head)
    return 0;
  Node_type *p1,*p2;
  p1 = p2 = head;
  for(unsigned int i = 0; i < n-1; ++i){
    if(!p2)
      return 0;//size of the list is < n
    else
      p2 = p2->next;
  }
  while(p2->next){
    p1 = p1->next;
    p2 = p2->next;
  }
  return p1;
}


