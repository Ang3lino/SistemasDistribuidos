
#ifndef __TRIE_H__
#define __TRIE_H__

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <string>


struct Trie {

    struct Node {
        char character;
        bool data;
        std::vector<std::unique_ptr<struct Node > > children;

        Node() {}
        Node(char &_char): character(_char) { }
        Node(char &_char, bool _data): character(_char), data(_data) { }
    };

    std::unique_ptr<Node > root;

    Trie() {
        root = std::make_unique<Node >();
    }

    void __put(std::string &key, unsigned i, bool &value, 
                std::unique_ptr<Node > &current_ptr) {
        Node *current = current_ptr.get();
        if (i == key.size() - 1) {  // If there's a repeated element it'll be inserted again
            auto node_ptr = std::make_unique<Node >(key[i], value);
            current->children.push_back(std::move(node_ptr));
            return;
        }
        for (auto &node_ptr: current->children) { 
            auto node = node_ptr.get();
            if (node->character == key[i]) {
                __put(key, i + 1, value, node_ptr);
                return;
            }
        }
        auto &children = current->children;
        children.push_back(std::make_unique<Node >(key[i]));
        int n = children.size();
        __put(key, i + 1, value, children[n - 1]);
    }

    void put(std::string &key, bool value=true) {
        __put(key, 0, value, root);
    }

    bool __get(std::unique_ptr<Node > &self, std::string &key, unsigned i) {
        if (i >= key.size())
            return false;
        auto current_node = self.get();
        for (auto &node_uptr: current_node->children) {
            auto node = node_uptr.get(); 
            if (node->character == key[i]) {
                std::cout << node->character;
                if (i == key.size() - 1)
                    return node->data;
                return __get(node_uptr, key, i + 1);
            }
        }
        return false;
    }

    bool get(std::string &key) {
        return __get(root, key, 0);
    }

};


#endif

