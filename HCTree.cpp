#include "HCTree.hpp"
#include <queue>

  void HCTree::build(const vector<int>& freqs){
    //create the forest
    std::priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest;

    //generate leaves and take a counts
    for (int i = 0; i < freqs.size(); i++){
      if(freqs.at(i) != 0){
        HCNode *tmp = new  HCNode(freqs.at(i), i);
        leaves.at(i) = tmp; 
        forest.push(tmp);
      }
    }

    //one node edge case
    if(forest.size() == 0){
      forest.push(new HCNode(0,0));
    }

    //construct the tree
    while(forest.size() > 1){
      
      HCNode *parent = new HCNode(0,0); 
     
      //set right child
      HCNode* right = forest.top();
      right->p = parent;
      forest.pop();

      // set left child
      HCNode* left = forest.top();
      left->p = parent;
      forest.pop();

      //set parent
      parent->count = left->count + right->count;
      //parent->symbol = right->symbol;
      parent->c0 = right;
      parent->c1 = left;
      forest.push(parent);
      //cout << *parent << endl;
    }

    //set root
    root = forest.top();
  }

  
  HCTree::~HCTree(){
    clean(root);
    root = 0;
  }
  
  void HCTree::clean(HCNode* node){
    if(node){
      clean(node->c0);
      clean(node->c1);
      node->c0 = 0;
      node->c1 = 0;
      node->p=0;
      delete node;
    }
  }

  void HCTree::encode(byte symbol, BitOutputStream& out) const{
    HCNode* node = leaves.at(symbol);
    vector<int> seq;
    vector<int>::iterator head;
    //trace back get the correct sequence
    while(node != root){
      head = seq.begin();
      //cout << *node << endl;
      //check which child the node fall in
      if(node->p->c0 == node){
        seq.insert(head,0);
      }else if(node->p->c1 == node){
        seq.insert(head,1);
      }
      node = node->p;
    }

    //write bit out
    for(auto i:seq){
      out.writeBit(i);
    }
  }

   int HCTree::decode(BitInputStream& in) const{

    HCNode* node = root;
    int bit;

    // traverse from root to leaf to get the symbol
    while((node->c0 != 0)|| (node->c1 != 0)){
      bit = in.readBit();
      if(bit == 1){
        node = node->c1;
      }else if(bit ==0){
        node = node->c0;
      }
    }

    return node->symbol;
  }

    


      
    


