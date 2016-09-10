#include "tree.h"

Tree::Tree() {
    auto rootPos = ofVec3f(ofGetWidth()/2, ofGetHeight(), 0);
    auto rootDir = ofVec3f(0, -1, 0);
    shared_ptr<Branch> root(new Branch(rootDir));
    root->move(rootPos);
    branches.push_back(root);

    for (int i =0; i<n_leaves; i++) {
        leaves.push_back(Leaf());
    }

    bool found = false;
    while(!found){
        auto current = *branches.back();
        ofVec3f cur = current.getPosition();
        for(auto l:leaves){
            l.draw();
            float distance = cur.distance(l.getPosition());
            if(distance < max_dist){
                found = true;
            }
        }

        if (!found){
            shared_ptr<Branch> nextBranch(new Branch(current.direction));
            if(!branches.empty()){
                nextBranch->setParent(branches.back());
                nextBranch->move(current.direction);
            }
            branches.push_back(nextBranch);
        }
    }
}

void Tree::grow(){
    for(auto l:leaves){
        deque<shared_ptr<Branch>> closestBranch = {};
        float record = 10000.0;
        for(auto b:branches){
            auto distance = l.getPosition().distance(b->getPosition());
            if(distance < min_dist){
                l.reached = true;
                break;
            }else if (distance > max_dist){
                break;
            }else if (closestBranch.size() ==0 || distance < record){
                closestBranch.push_back(b);
                closestBranch.pop_front();
                record = distance;
            }
        }

        if(closestBranch.size()>0){
            auto dir = (l.getPosition() - closestBranch.at(0)->getPosition()).normalize();

            closestBranch.at(0)->direction = closestBranch.at(0)->direction + dir;
            closestBranch.at(0)->count++;
//            shared_ptr<Branch> nextBranch(new Branch(dir));
//            if(!branches.empty()){
//                nextBranch->setParent(branches.back());
//                nextBranch->move(current.direction);
//            }
        }
    }

    for(int i =0; i< leaves.size(); i++){
        if(leaves[i].reached){
            leaves.erase(leaves.begin()+i);
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
