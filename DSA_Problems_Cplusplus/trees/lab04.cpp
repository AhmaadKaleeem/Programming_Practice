#include <iostream>
using namespace std;

template <class T>
class TreeNode {
private:
    T data;       
    TreeNode* left;   
    TreeNode* right; 
public:
    void set_left_node(TreeNode* t){
        this->left = t;
    }
    void set_right_node(TreeNode* t){
        this->right = t;
    }
    T set_value(T user_value)
    { this->data = user_value;}
    T get_value(){
        return data;
    }
    TreeNode* get_left_node(){
        return left;
    }
    TreeNode* get_right_node(){
        return right;
    }
    
    TreeNode(const T& user_data) : data(user_data), left(nullptr), right(nullptr) {}
};
template <typename T>
void insert(TreeNode<T>* root, T data) {
    TreeNode<T>* p = root;
    TreeNode<T>* q = root;

    while (q != nullptr && data != p->get_value()) {
        p = q;
        if (data < p->get_value()) {
            q = p->get_left_node();
        } else {
            q = p->get_right_node();
        }
    }
    
    if (data == p->get_value()) {
        cout << "Found a duplicate in list : " << data << endl;
    } else if (data < p->get_value()) {
        p->set_left_node(new TreeNode<T>(data));
    } else {
        p->set_right_node(new TreeNode<T>(data));
    }
}
template <typename T>
void displayTree(TreeNode<T>* node) {
    if (node == nullptr) {
        return; 
    }

    displayTree(node->get_left_node());
    cout << node->get_value() << " ";
    displayTree(node->get_right_node());
}

int main() {
    int numbers[] = {2556,2565,21445,1212,1522,1251,212,12,1,2,3,45452,126593,253,25,2,1,3,9,8,9};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    if (size == 0) {
        cout << "The list is empty." << endl;
        return 0;
    }
    
    TreeNode<int>* root = new TreeNode<int>(numbers[0]);
    cout << "Root : " << numbers[0] << endl;

    for (int i = 1; i < size ; ++i) {
        insert(root, numbers[i]);
    }

    cout << "\nTree elements: ";
    displayTree(root);
    cout << endl;
    
    return 0;
}