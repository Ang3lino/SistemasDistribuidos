
/** Trie implementation by using KTrees, it maps string -> bool.
 * 
 */

#ifndef __TRIE_H__
#define __TRIE_H__

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <memory>
#include <string>


using namespace std;

template<typename T>
struct Trie {

    struct Node {
        char character;
        T data;
        std::vector<std::unique_ptr<struct Node > > children;

        Node() {}
        Node(char &_char): character(_char) { }
        Node(char &_char, T _data): character(_char), data(_data) { }
    };


    using u_ptr_node = std::unique_ptr<Node >;
    using u_ptr_nodes = std::vector<u_ptr_node >;

    std::unique_ptr<Node > root;


    Trie() {
        root = std::make_unique<Node >();
    }

    void __put(std::string &key, unsigned i, T &value, u_ptr_node &current_ptr) 
    {
        auto &children = current_ptr.get()->children;  
        // Insert the leaf with the value associated
        // If the element was inserted previously it'll be inserted again
        if (i == key.size() - 1) {  
            children.push_back(make_unique<Node> (key[i], value));
            return;
        }
        auto it = std::find_if(children.begin(), children.end(), 
                [&](u_ptr_node &child) -> bool {
                    return (child.get()->character == key[i]);
        });
        if (it != children.end()) { // found
            __put(key, i + 1, value, *it);
            return;
        }
        children.push_back(make_unique<Node> (key[i]));
        __put(key, i + 1, value, children[children.size() - 1]);
    }

    void put(std::string &key, T value) {
        __put(key, 0, value, root);
    }

    T __get(std::unique_ptr<Node > &self, std::string &key, unsigned i) {
        if (i >= key.size())
            throw "Trie::__get: Index out of range.\n";
        auto current_node = self.get();
        for (auto &node_uptr: current_node->children) {
            auto node = node_uptr.get(); 
            if (node->character == key[i]) {
                // std::cout << node->character;
                if (i == key.size() - 1)
                    return node->data;
                return __get(node_uptr, key, i + 1);
            }
        }
        throw "Trie::__get: There'is no such value.\n";
    }

    T get(std::string &key) {
        return __get(root, key, 0);
    }

};


#endif

