#include "tree.h"
//http://www.jgallant.com/procedurally-generating-trees-with-space-colonization-algorithm-in-xna/
//http://johnwhigham.blogspot.de/2011/12/seeing-wood-for-trees.html
Tree::Tree() {
    auto rootPos = ofVec3f(ofGetWidth()/2, ofGetHeight(), 0);
    auto rootDir = ofVec3f(0, -1, 0);
    shared_ptr<Branch> root(new Branch(rootDir));
    root->move(rootPos);
    branches.push_back(root);

    for (int i =0; i<n_leaves; i++) {
        leaves.push_back(Leaf());
    }

    auto current = root;
    bool found = false;
    while(!found){
        ofVec3f cur = current->getPosition();
        for(auto l:leaves){
            float distance = cur.distance(l.getPosition());
            if(distance < max_dist){
                found = true;
            }
        }

        if (!found){
            shared_ptr<Branch> nextBranch(new Branch(current->direction));
            if(!branches.empty()){
                nextBranch->setParent(branches.back());
                nextBranch->move(current->direction * branch_length );
            }
            branches.push_back(nextBranch);
            current = branches.back();
        }
    }
    
}

void Tree::grow(){
    cout << branches.size() << endl;
    for(int it=0;it<leaves.size();it++){
        float record = 10000.0;

        auto closestBranchIndex = -1;
        for(int i=0;i<branches.size();i++){
            auto distance = leaves[it].getPosition().distance(branches[i]->getPosition());
            if(distance < min_dist){
                leaves[it].reached = true;
                closestBranchIndex = -1;
                break;
            }else if (distance > max_dist){
                //break;
            }else if ((closestBranchIndex < 0) || (distance < record)){
                closestBranchIndex = i;
                record = distance;
            }
        }

        if(closestBranchIndex>=0 && !leaves[it].reached){
            auto dir = (leaves[it].getPosition() - branches[closestBranchIndex]->getPosition()).normalize();
            branches[closestBranchIndex]->direction = branches[closestBranchIndex]->direction + dir;
            branches[closestBranchIndex]->count = branches[closestBranchIndex]->count + 1;

            shared_ptr<Branch> nextBranch(new Branch(dir));
            if(!branches.empty()){
                nextBranch->setParent(branches.back());
                nextBranch->move(branches[closestBranchIndex]->direction * branch_length);
            }
        }

        if(leaves[it].reached){
            leaves.erase(leaves.begin()+it);
        }
    }

    for (int i = 0; i<branches.size(); i++) {
        if(branches[i]!= nullptr && branches[i]->count > 0){
            auto newDir = branches[i]->direction / float(branches[i]->count);
            shared_ptr<Branch> nextBranch(new Branch(newDir));
            nextBranch->setParent(branches[i]);
            nextBranch->move(newDir * branch_length);
            branches.push_back(nextBranch);
        }
        if(branches[i]!= nullptr){
            branches[i]->reset();
        }
    }
}

void Tree::draw(){
    for(auto l:leaves){
        l.draw();
    }
    for(auto b:branches){
        b->draw();
    }
}
