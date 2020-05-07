
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

    Node * __get_node(u_ptr_node &self, std::string &key, unsigned i) {
        if (i >= key.size())
            return nullptr;  // index out of bounds
        auto &children = self.get()->children;
        auto it = std::find_if(children.begin(), children.end(), 
                [&] (auto &node_uptr) -> bool {
                    return node_uptr.get()->character == key[i];
        });
        if (it == children.end())
            return nullptr; // No such value
        if (i == key.size() - 1)
            return it->get();
        return __get_node(*it, key, i + 1);
    }

    T get(std::string &key) {
        Node *node_ptr = __get_node(root, key, 0);
        if (node_ptr == nullptr)
            throw "Trie:get: There's no such value\n";
        return node_ptr->data;
    }

    T get(std::string &key, T &default_value) {
        Node *node_ptr = __get_node(root, key, 0);
        if (node_ptr == nullptr)
            return default_value;
        return node_ptr->data;
    }

    bool has(std::string key) {
        return __get_node(root, key, 0) != nullptr;
    }

};


#endif

