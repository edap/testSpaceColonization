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

    auto current = root;
    bool found = false;
    while(!found){
        //auto current = branches.back();

        ofVec3f cur = current->getPosition();
        cout << cur.y << endl;
        for(auto l:leaves){
            float distance = cur.distance(l.getPosition());
            if(distance < max_dist){
                cout << "trovato" << endl;
                found = true;
            }
        }

        if (!found){
            shared_ptr<Branch> nextBranch(new Branch(current->direction));
            if(!branches.empty()){
                nextBranch->setParent(branches.back());
                nextBranch->move(current->direction * 5);
            }
            branches.push_back(nextBranch);
            current = branches.back();
        }
    }
    
}

void Tree::grow(){
    for(auto& l:leaves){
        float record = 10000.0;
        //iteri tramite indici, all'inizio il closed branch non e' ancora stato trovato
        // (index -1), poi quando lo trovi cambi ;'indice
        auto closestBranchIndex = -1;
        for(int i=0;i<branches.size();i++){
        //for(auto b:branches){
            auto distance = l.getPosition().distance(branches[i]->getPosition());
            if(distance < min_dist){
                l.reached = true;
                closestBranchIndex = -1;
                break;
            }else if (distance > max_dist){
                //break;
            }else if ((closestBranchIndex < 0) || (distance < record)){
                closestBranchIndex = i;
                record = distance;
            }
        }

        if(closestBranchIndex>=0){
            auto dir = (l.getPosition() - branches[closestBranchIndex]->getPosition()).normalize();
            branches[closestBranchIndex]->direction = branches[closestBranchIndex]->direction + dir;
            branches[closestBranchIndex]->count = branches[closestBranchIndex]->count + 1;

            shared_ptr<Branch> nextBranch(new Branch(dir));
            if(!branches.empty()){
                nextBranch->setParent(branches.back());
                nextBranch->move(branches[closestBranchIndex]->direction);
            }
        }
    }

    // this operation can be moved in the previous one
    // problema. Anche se hai marcato alcune foglie come reached
    // queste non vengono cancellate. Questo avviene perche' in realta'
    // tu non stai cambiando il boolean "reached" in nessuna delle foglie!
    for(int i =0; i< leaves.size(); i++){
        if(leaves[i].reached){
            cout << leaves.size() << endl;
            leaves.erase(leaves.begin()+i);
        }
    }

    for (auto b:branches) {
        if(b!= nullptr && b->count > 0){
            auto newDir = b->direction / float(b->count);
            shared_ptr<Branch> nextBranch(new Branch(newDir));
            nextBranch->setParent(b);
            nextBranch->move(newDir );
            branches.push_back(nextBranch);
        }
        if(b!= nullptr){
           b->reset();
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
