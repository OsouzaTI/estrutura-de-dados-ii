#include <iostream>
#include <vector>
#include <algorithm>

#define ALFA_SIZE 26

class TNode {
public:
    TNode();
    bool isWord;
    int  recurrence;
    TNode* children[ALFA_SIZE];
    void insert(std::string word);
    bool search(std::string word);
    bool isCompost(std::string word);
    int  numOfRecurrences(std::string word);
    void print(); 
};

TNode::TNode(){
    this->isWord = false;
    this->recurrence = 0;
    int i;
    for(i = 0; i < ALFA_SIZE; i++)
        this->children[i] = nullptr;
}

void TNode::print(){
    int i;
    for(i = 0; i < ALFA_SIZE; i++){
        if(this->children[i] != nullptr){
            std::cout << (char)(i + 'a');
            this->children[i]->print();
        }
    }
}

int TNode::numOfRecurrences(std::string word){
    TNode* curr = this;
    for(char k : word){
        int index = k - 'a';
        curr = curr->children[index];
        if(curr == nullptr)
            return 0;       
    }  
    return curr->recurrence;
}

bool TNode::search(std::string word){
    TNode* curr = this;
    for(char k : word){
        int index = k - 'a';
        curr = curr->children[index];
        if(curr == nullptr)
            return false;       
    }  
    return curr->isWord;
}

bool TNode::isCompost(std::string word){
    TNode* curr = this;
    int prefixCount = 0;
    for(char k : word){
        int index = k - 'a';
        curr = curr->children[index];
        if(curr->isWord)
            prefixCount++;       
    }  
    return prefixCount > 1;
}

void TNode::insert(std::string word){
    TNode* curr = this;
    for(char k : word){
        int index = k - 'a';
        if(curr->children[index] == nullptr){
            curr->children[index] = new TNode();
        }
        curr = curr->children[index];
    }    

    if(!curr->isWord)
        curr->isWord = true;
    curr->recurrence++;
}

int main(){
    TNode* root = nullptr;
    
    
    return 0;
}