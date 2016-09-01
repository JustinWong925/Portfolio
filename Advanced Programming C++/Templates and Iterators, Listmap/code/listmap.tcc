// $Id: listmap.tcc,v 1.5 2014-07-09 11:50:34-07 - - $

#include "listmap.h"
#include "trace.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (node* next, node* prev,
                                     const value_type& value):
            link (next, prev), value (value) {
}


//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap() {
   TRACE ('l', (void*) this);
}

//
// listmap::empty()
//
template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::empty() const {
   return anchor_.next == anchor_.prev;
}

//
// listmap::iterator listmap::begin()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::begin() {
   return iterator (anchor_.next);
}

//
// listmap::iterator listmap::end()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::end() {
   return iterator (anchor());
}

template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::print () {
   node *begin = anchor__.next;
   node *end = anchor();
   node *cur = (begin, begin->next, pair);
   if(begin == NULL){
      cout << "List is empty" << endl;
   }
   while (begin != NULL){
      cout << cur->pair << endl;
	  cur = cur->next;
   }
   
}

template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::print_values 
             (const xpair<Key,Value>& pair) {
	node *cur = anchor__.next;
	if(cur = NULL){
	   cout << "List is empty" << endl;
    }
    while (cur != NULL){
	   if(pair.second == cur->pair.second){
	       cout << cur->pair << endl;
	   }
	   cur = cur->next;
}


//
// iterator listmap::insert (const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::insert (const value_type& pair) {
   TRACE ('l', &pair << "->" << pair);
   node *begin = anchor__.next;
   node *end = anchor();
   node *tmp = new node(begin, begin->next, pair);
   if(begin==end){
      node *tmp = new node(begin->next, begin->prev, pair);
   } else {
      while(begin != end ){
	      if(pair.first == cur->pair.first){
		     cur->pair.second = pair.second;
			 break;
		  } else if (less(pair.first, cur->pair.first)){
		     if(curr == begin){
			    tmp->next = cur;
				cur->prev = tmp;
				begin = tmp;
				tmp->prev = NULL;				
			 } else {
			    tmp->next = begin;
				tmp->prev = cur->prev;
				begin->prev->next = tmp;
				begin->prev = tmp;
			 }
			 break;
		  }
	   begin = begin->next;
	  }
	  if(begin == NULL){
	     end->next = tmp;
		 tmp->prev = end;
		 end->tmp;
		 tmp->next = NULL;
	  }
   }
   return iterator();
}

//
// listmap::find(const key_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) const {
   TRACE ('l', that);
   return iterator();
}

//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::erase (iterator position) {
   TRACE ('l', &*position);
   return iterator();
}


//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type&
listmap<Key,Value,Less>::iterator::operator*() {
   TRACE ('l', where);
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type*
listmap<Key,Value,Less>::iterator::operator->() {
   TRACE ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++() {
   TRACE ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator--() {
   TRACE ('l', where);
   where = where->prev;
   return *this;
}


//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}
