#include "vote_queue.h"
#include <libraries.h>
using namespace std;
VoteNode::VoteNode(): cnic("Null"),c_name("Null"),next(nullptr){}
VoteNode::VoteNode(const string& user_cnic, const string& canidate,const string& c_type ): cnic(user_cnic),c_name(canidate),type(c_type),next(nullptr){}
VoteQueue::VoteQueue(){
    front = rear = nullptr;
}

bool VoteQueue::is_empty() const{
   if(front != nullptr){
    return false;
   }

    return true;
}

void VoteQueue::enqueue(const string& cnic_nbr,const string& canidate,const string& c_type){
 VoteNode* new_vote = new VoteNode(cnic_nbr,canidate,c_type);
 if(front == nullptr){
    front = rear = new_vote;
 }
 else{
    rear->next = new_vote;
    rear = new_vote;
 }
}

void VoteQueue::dequeue() {
    if (is_empty()){
        return;
    }
    else{
       VoteNode* temp = front;
       front = temp->next;
       delete temp;
    }
}
VoteNode* VoteQueue::check_top() const{
    if(is_empty()){
        return nullptr;
    }
   return front;
}

