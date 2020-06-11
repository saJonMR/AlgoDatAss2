#ifndef BST_HPP
#define BST_HPP
#include <iostream>

template<typename T>
class Bst;

//Node Struct which saves Data, a pointer to parent and both children. Def. init. to 0
template<typename T>
struct TreeNode {
    T        data = 0;
    TreeNode*  parent = nullptr;
    TreeNode* l_child = nullptr;
    TreeNode* r_child = nullptr;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const TreeNode<T> n) {
    os << n->data;
}

template<typename T>
class Bst {
public:

    Bst() {
        size_ = 0;
        root_ = nullptr;
    }

    //Overload of add function to only take one arg
    void add(T const& node) {
        TreeNode<T> *newNode = new TreeNode<T>;
        newNode->data = node;
        if (root_ == nullptr) {
            root_ = newNode;
        } else {
            add(node, root_);
        }
        size_++;
    }

    //Add a Node and put in in the right place
    void add(int key, TreeNode<T>* const& node) {
        TreeNode<T> *newNode = new TreeNode<T>;
        newNode->data = key;
        if (key < node->data) {
            if (node->l_child == nullptr) {
                node->l_child = newNode;
                newNode->parent = node;
                return;
            }
            return add(key, node->l_child);
        }
        else {
            if (node->r_child == nullptr) {
                node->r_child = newNode;
                newNode->parent = node;
                return;
            }
            return add(key, node->r_child);
        }
    }

    //Remove node and adjust Tree
    void remove(int key) {
        if (exists(key) != true) {
            return;
        } 
        TreeNode<T> *node = new TreeNode<T>;
        node = find(key);
        //If node is Leaf (0 Children)
        if (node->r_child == nullptr && node->l_child == nullptr) {
            TreeNode<T> *parent = new TreeNode<T>;
            parent = node->parent;
            node->parent = nullptr;
            if (parent->l_child->data == key) {
                parent->l_child = nullptr;
            } else {
                parent->r_child = nullptr;
            } delete node;
            size_--;
        } //If Node has two Children
        else if(node->r_child != nullptr && node->l_child != nullptr) {
            TreeNode<T> *lefty = new TreeNode<T>;
            lefty = leftMostOf(node->r_child);
            node->data = lefty->data;
            lefty->parent->l_child = nullptr;
            lefty->parent = nullptr;
            delete lefty;
            size_--;
        } else {
            //If only one Child
            TreeNode<T> *parent = new TreeNode<T>;
            parent = node->parent;
            //If only right Child
            if (node->r_child != nullptr) {
                if(parent->l_child->data == key) {
                    parent->l_child = node->r_child;
                } else {
                    parent->r_child = node->r_child;
                } node->r_child->parent = parent;
                node->r_child = nullptr;
                node->parent = nullptr;
                delete node;
                size_--;
            } else {
                //If only left child
                if(parent->l_child->data == key) {
                    parent->l_child = node->r_child;
                } else {
                    parent->r_child = node->r_child;
                }
                node->l_child = nullptr;
                node->parent = nullptr;
                delete node;
                size_--;
            }
        }
    }

    //Find max node in Tree
    TreeNode<T>* max(TreeNode<T>* node) {
        if (node == nullptr) {
            return NULL;
        }
        if (node->r_child == nullptr) {
            return node;
        } return max(node->r_child);
    }
    //Find min node in Tree
    TreeNode<T>* min(TreeNode<T>* node) {
        if (node == nullptr) {
            return NULL;
        }
        if (node->l_child == nullptr) {
            return node;
        } return min(node->l_child);
    }
    
    //Find max data in Tree
    int maxData(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->r_child == nullptr) {
            return node->data;
        } return maxData(node->r_child);
    }
    //Find min data in Tree
    int minData(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->l_child == nullptr) {
            return node->data;
        } return minData(node->l_child);
    }

    //Returns left most node of given node
    TreeNode<T>* leftMostOf(TreeNode<T>* const& node) {
        if (node->l_child != nullptr) {
            return leftMostOf(node->l_child);
        }
        return node;
    }

    //Returns right most of given node
    TreeNode<T>* rightMostOf(TreeNode<T>* const& node) {
        if (node->r_child != nullptr) {
            return rightMostOf(node->r_child);
        }
        return node;
    }

    //Returns data of successor Node of given key
    int successor(T const& key) {
        if (exists(key) == true) {
            TreeNode<T> *node = new TreeNode<T>;
            node = find(key);
            if (node->r_child != nullptr) {
                return leftMostOf(node->r_child)->data;
            } else if (node == max(root_)) {
                return -1;
            } else {
                TreeNode<T> *tmp = new TreeNode<T>;
                tmp = node->parent;
                while(key > tmp->data) {
                    tmp = tmp->parent;
                }
                return tmp->data;
            }
        } 
        return -1;
    }

    //Returns data of predecessor Node of given key
    int predecessor(T const& key) {
        if (exists(key)) {
            TreeNode<T> *node = new TreeNode<T>;
            node = find(key);
            if (node->l_child != nullptr) {
                return rightMostOf(node->l_child)->data;
            } else if(node == min(root_)) {
                return node->data;
            } else {
                TreeNode<T> *tmp = new TreeNode<T>;
                tmp = node->parent;
                while(key > tmp->data) {
                    tmp = tmp->parent;
                }
                return tmp->data;
            }
        } else {
            return -1;
        }
    }

    //Function that returns Node with same data as key value
    TreeNode<T>* find(TreeNode<T>* const& node, T const& key) const {
        if (node == nullptr) {
            return NULL;
        } else if (node->data == key) {
            return node;
        } else if (key > node->data) {
            return find(node->r_child, key);
        } else {
            return find(node->l_child, key);
        }
    }
    
    //Overload of find function to only take one argument
    TreeNode<T>* find(T const& key) {
        return find(root_, key);
    }

    //Returns false if find function returns 0x0 and true otherwise
    bool exists(T const& key) {
        if (find(root_, key) == 0x0) {
            return false;
        } 
        return true;
    }

    std::size_t size() {
        return size_;
    }

    TreeNode<T>* getRoot() const {
        return root_;
    }

    int printRoot() const {
        return root_->data;
    }

private:
    std::size_t size_;
    TreeNode<T>* root_;
};

#endif //BST_HPP

