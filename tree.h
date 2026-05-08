//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.

   DO NOT IMPLEMENT ANYTHING HERE.
   Only placeholders and to-do comments.
*/


template <typename U> class Node {
    public:
        string id;
        U data;
        vector<Node<U>*> children;

        // Write constructor
        Node(const string &nodeID, const U &value) {
            id = nodeID;
            data = value;
        }
};

template <typename T> class Tree {
    private:
        Node<T>* root;

    public:
        Tree()
        // Initialize root pointer to nullptr
        {root = nullptr;}

        void createRoot(const string &id, const T &value)
        // Allocate memory, assign id, assign data, set as root
        {root = new Node<T>(id, value);}

        void addNode(const string &parentID, const string &childID, const T &value)
        // Find parent, create child, link parent to child
        // Support repeated children under multiple parents
        {
            auto child = findNode(childID);
            if (!child) child = new Node<T>(childID, value);
            auto parent = findNode(parentID);
            if (!parent) return;
            for (auto c : parent->children) if (c->id == child->id) return;
            parent->children.push_back(child);
        }

        Node<T>* findNode(const string &id)
        // Use DFS or BFS to search tree
        {
            if (!root || root->id == id) return root;
            stack<Node<T>*> s;
            s.push(root);
            while (!s.empty()) {
                Node<T>* node = s.top();
                s.pop();
                for (int i = 0; i < node->children.size(); i++) s.push(node->children[i]);
                if (node->id == id) return node;
            }
            return nullptr;
        }

        void printAll()
        // Print entire structure in readable form
        {
            if (!root) return;
            queue<Node<T>*> q;
            vector<Node<T>*> nodes;
            q.push(root);
            cout<<"===== Story Tree =====\n";
            while (!q.empty()) {
                Node<T>* node = q.front();
                q.pop();
                bool pushed = false;
                for (auto n : nodes) if (n == node) {
                    pushed = true;
                    break;
                }
                if (pushed) continue;
                nodes.push_back(node);
                cout << "Node " << node->id << ": "<<node->data<<"\n";
                if (node->children.size() > 0) {
                    for (int i = 0; i < node->children.size(); i++) {
                        cout << "  Child -> " << node->children[i]->id<<endl;
                        q.push(node->children[i]);
                    }
                    cout<<"\n";
                }else cout << "  Child -> (none)" << endl;
            }
            cout << "======================\n";
        }

        // Students, implement a method in Tree<T> called playGame()
        // This method should:
        // 1. Start at the root node.
        // 2. Display the current node's text.
        // 3. Display numbered options for each child.
        // 4. Ask the user which path to take.
        // 5. Move to the selected child and continue until a node has no children.
        // 6. Print an ending message.

        void playGame() {
            cout<<"===== Begin Adventure =====\n\n";
            Node<T>* curr = root;
            while(true){
                if (!curr) return;
                if (curr->children.size() > 0) {
                    cout<<curr->data<<"\nChoose your next action:\n";
                    int i;
                    for (i = 0; i < curr->children.size(); i++) cout<<(i+1)<<". "<<curr->children[i]->data<<endl;
                    bool updated = false;
                    string input;
                    do{
                        cout<<"Selection: ";
                        cin>>input;
                        const int ip = stoi(input);
                        if (ip <= i) {
                            curr = curr->children[ip - 1];
                            updated = true;
                        }
                    }while (!updated);
                }else{
                    cout<<"There are no further paths.\nYour journey ends here.\n\n===== Adventure Complete =====";
                    return;
                }
            }
        }

        ~Tree()
        // Free all allocated memory
        {
            vector<Node<T>*> nodes;
            stack<Node<T>*> s;
            s.push(root);
            while (!s.empty()) {
                Node<T>* node = s.top();
                s.pop();
                if (!node) continue;
                bool pushed = false;
                for (auto n : nodes) if (n == node) {
                    pushed = true;
                    break;
                }
                if (pushed) continue;
                nodes.push_back(node);
                for (auto child : node->children) s.push(child);
            }
            for (auto node : nodes) delete node;
        }
};

#endif //FA25EC3_TREE_H
