#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

//queue class implemented using linked list
template <typename T>
class queue{
    public:
      queue();
      void enqueue(T);
      T dequeue();
      T front();
      bool isEmpty();
      
      
      //big 3
      queue(const queue &);
      ~queue();
      const queue& operator = (const queue&);
      
      //to get amount recieved by casier
      //return amount
      double getCash(){return cash;}
      
      //to get number of customers
      //return count
      int getCount(){return count;}
      
      //check whether at customer's arriving time is free or not
      //parameter arriving time of customer
      //return true if cashier is free else false
      bool isFree(int x){
          if(x>timing){
              return true;
          }
          else{
              return false;
          }
      }
      
      //to get total time taken by casier
      //return time
      int totalTime(){
          return timing;
      }
      
      
    private:
    
      //node
      struct node{
          T data;
          node* next;
      };
      node* head;
      node* tail;
      int count=0;
      double cash=0;
      int timing=0;
      
      //delete linked list
      //parameter p(linked list)
      //return list after deleting
      node* delete_list(node* p){
        while(p){
            node* tmp=p;
            p=p->next;
            delete tmp;
        }
        return p;
      }
      
      //to copy a linked list
      //parameter p(linked list)
      //return new list after copying from parameter
      node* copy_list(node* p){
        if(!p){
            return p;
        }
        return new node{p->data,copy_list(p->next)};
      }
};

//constructor
//sets head and tail to nullptr
template <typename T>
queue<T>::queue(){
    head=nullptr;
    tail=nullptr;
}


//copy constructor
//parameter B(queue)
//copy all variables from B
template <typename T>
queue<T>::queue(const queue & B){
    head=copy_list(B.head);
    tail=copy_list(B.tail);
    cash=B.cash;
    count=B.count;
}

//assignment operator
//parameters B(queue)
//return this queue class
template <typename T>
const queue<T>& queue<T>::operator = (const queue& B){
    if(this== &B){
        return *this;
    }
    head=delete_list(head);
    tail=delete_list(tail);
    head=copy_list(B.head);
    tail=copy_list(B.tail);
    cash=B.cash;
    count=B.count;
    return *this;
}


//to add data into linked list
//parameter x(to be added)
//increments count and sets timing and cash
template <typename T>
void queue<T>::enqueue(T x){
    if(!head){
        tail=new node{x,nullptr};
        head=tail;
    }
    else{
        tail->next=new node{x,nullptr};
        tail=tail->next;
    }
    count++;
    cash+=x.amount;
    timing=x.arrival+x.process;
}

//deconstructor
template <typename T>
queue<T>::~queue(){
    head=delete_list(head);
    tail=nullptr;
}


//to remove first element from list
//return removed value
template <typename T>
T queue<T>::dequeue(){
    T ret_val=front();
    double x=front().amount;
    node *temp=head->next;
    delete head;
    head=temp;
    if(!head){
        tail=head;
    }
    count--;
    cash-=x;
    return ret_val;
}

//to get first element in list
//return first element
template <typename T>
T queue<T>::front(){
    if(isEmpty()){
        std::cout<<"Error";
        std::exit(0);
    }
    return head->data;
}

//check if list is empty
//return true if empty else false
template <typename T>
bool queue<T>::isEmpty(){
    return !head;
}


#endif
