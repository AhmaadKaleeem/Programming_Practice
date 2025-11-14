#include "vote_queue.h"

VoteNode::VoteNode(): cnic("Null"),c_name("Null"),next(nullptr){}
VoteNode::VoteNode(const string& u_cnic, const string& canidate ): cnic(u_cnic),c_name(canidate),next(nullptr){}
VoteQueue::VoteQueue(){
    front = rear = nullptr;
}

bool VoteQueue::is_empty() const{
   if(front != nullptr){
    return false;
   }

    return true;
}

void VoteQueue::enqueue(const string& cnic_nbr,const string& canidate){
 VoteNode* new_vote = new VoteNode(cnic_nbr,canidate);
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

