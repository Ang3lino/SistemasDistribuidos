
/** Trie implementation by using KTrees, it maps string -> bool.
 */

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


    using u_ptr_node = std::unique_ptr<Node >;
    using u_ptr_nodes = std::vector<u_ptr_node >;

    std::unique_ptr<Node > root;

    Trie() {
        root = std::make_unique<Node >();
    }

    u_ptr_nodes::iterator __linear_search(std::vector<u_ptr_node> &nodes, char &c) 
    {
        return std::find_if(nodes.begin(), nodes.end(), 
                [&](u_ptr_node &child) {
                    return (child.get()->character == c) ;
        });
    }

    void __put_child(u_ptr_nodes &children, char &character, bool value=false) 
    {
        auto node_ptr = std::make_unique<Node >(character, value);
        children.push_back(std::move(node_ptr));
    }

    void __put(std::string &key, unsigned i, bool &value, u_ptr_node &current_ptr) 
    {
        auto &children = current_ptr.get()->children;  
        // Insert the leaf with the value associated
        // If there's a repeated element it'll be inserted again
        if (i == key.size() - 1) {  
            __put_child(children, key[i], value);
            return;
        }
        auto it = __linear_search(children, key[i]);  // u_ptr_nodes::iterator
        if (it != children.end()) { // found
            __put(key, i + 1, value, *it);
            return;
        }
        __put_child(children, key[i]);
        __put(key, i + 1, value, children[children.size() - 1]);
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

