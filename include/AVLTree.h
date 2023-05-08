#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <limits> // https://stackoverflow.com/a/2561391
#include <memory>
#include <stack>
#include <utility>

namespace Tree {
using namespace std;
template <typename T, typename V>
class AVL {
    class Node {
      private:
        T key;
        int height;
        Node *left;
        Node *right;
        V value;
        friend class AVL;

        friend bool operator==(const Node &lhs, const Node &rhs) {
            if (lhs.key == rhs.key && lhs.value == rhs.value) {
                return true;
            }
            return false;
        }

      public:
        Node() = default;

        Node(T _key) : key(_key), height(1), right(nullptr), left(nullptr){};

        Node(T _key, V _value) : key(_key), value(_value), height(1), right(nullptr), left(nullptr) {
        }

        Node(std::pair<T, V> _il) : key(_il.first), value(_il.second), height(1), right(nullptr), left(nullptr) {
        }

        ~Node() {
            delete left;
            left = nullptr;
            delete right;
            right = nullptr;
        }

        T Key() {
            return key;
        }

        V Value() {
            return value;
        }

        int Height() {
            return height;
        }

        bool IsLeaf() {
            if (left == nullptr && right == nullptr)
                return true;
            return false;
        }

        Node &operator=(const V &other) noexcept {
            value = other;
            return *this;
        }

        Node &operator=(V &&other) noexcept {
            value = other;
            return *this;
        }
    };

    void swap(Node *lhs, Node *rhs) noexcept {
        std::swap(lhs->key, rhs->key);
        std::swap(lhs->value, rhs->value);
        std::swap(lhs->left, rhs->left);
        std::swap(lhs->right, rhs->right);
        std::swap(lhs->height, rhs->height);
    }

    typedef Node *node_ptr;

  private:
    node_ptr root = nullptr;
    size_t size;
    enum leftRight { Left, Right };

  public:
    AVL(std::initializer_list<T> listNode) {
        for (T node : listNode) {
            Insert(node);
        }
    }

    AVL(std::initializer_list<std::pair<T, V>> listNode) {
        for (std::pair<T, V> i : listNode) {
            Insert(i);
        }
    }

    AVL() : size(0){};

    ~AVL() {
        delete root;
        root = nullptr;
    }

    node_ptr Root() {
        return root;
    }

    bool Insert(std::pair<T, V> _pair) {
        /**
         * @param _pair	The key and value pair
         * @return true if it success in insert and false if it doesn't
         */
        T x = _pair.first;
        if (root == nullptr) {
            root = new Node(_pair);
            return true;
        }

        // Insert the tree
        std::stack<node_ptr> stackNode;
        std::stack<leftRight> stackEdge;
        node_ptr currentNode = root;
        while (currentNode != nullptr) {
            if (x < currentNode->key) {
                if (currentNode->left == nullptr) {
                    stackNode.push(currentNode);
                    stackEdge.push(Left);
                    currentNode->left = new Node(_pair);
                    break;
                }
                stackNode.push(currentNode);
                stackEdge.push(Left);
                currentNode = currentNode->left;
                continue;
            }

            if (x > currentNode->key) {
                if (currentNode->right == nullptr) {
                    stackNode.push(currentNode);
                    stackEdge.push(Right);
                    currentNode->right = new Node(_pair);
                    break;
                }
                stackNode.push(currentNode);
                stackEdge.push(Right);
                currentNode = currentNode->right;

                continue;
            }
            // we don't want the AVL tree to have the same node
            return false;
        }

        // Balance the tree
        while (!stackNode.empty()) {
            Node *currNode = stackNode.top();
            stackNode.pop();
            stackEdge.pop();

            BalanceTreeDelete(currNode, stackNode, stackEdge);
            currNode->height = 1 + max(NodeHeight(currNode->left), NodeHeight(currNode->right));
        }

        return true;
    }

    bool Insert(T _key) {
        return Insert({_key, V{}});
    }

    bool Remove(T x) {
        /**
         * @param x The key to remove
         * @return true if the the remove has been done, false if the key doesn't
         * exist
         */
        if (root == nullptr)
            return false;

        std::stack<node_ptr> stackNode;
        std::stack<leftRight> stackEdge;
        node_ptr currentNode = root;
        while (true) {
            if (x < currentNode->key) {
                if (currentNode->left == nullptr) {
                    // Not found
                    return false;
                }
                stackNode.push(currentNode);
                stackEdge.push(Left);
                currentNode = currentNode->left;
                continue;
            }

            if (x > currentNode->key) {
                if (currentNode->right == nullptr) {
                    // Not found
                    return false;
                }
                stackNode.push(currentNode);
                stackEdge.push(Right);
                currentNode = currentNode->right;

                continue;
            }
            // We have found the same node
            RemoveNode(currentNode, stackNode, stackEdge);
            currentNode = nullptr;
            break;
        }

        // Balance the tree
        while (!stackNode.empty()) {
            Node *currNode = stackNode.top();
            stackNode.pop();
            stackEdge.pop();

            currNode->height = 1 + max(NodeHeight(currNode->left), NodeHeight(currNode->right));
            BalanceTreeDelete(currNode, stackNode, stackEdge);
        }

        return true;
    }

    node_ptr Search(T x) {
        Node *foundNode = TreeSearch(root, x).first;
        return foundNode;
    }

    Node *SearchNearSmallest(T _x) {
        Node *currentNode = root;
        Node *smallestNode = nullptr;

        while (currentNode != nullptr) {
            if (currentNode->key < _x) {
                smallestNode = currentNode;
                currentNode = currentNode->right;
                continue;
            }

            if (currentNode->key > _x) {
                currentNode = currentNode->left;
                continue;
            }

            smallestNode = currentNode;
            break;
        }

        return smallestNode;
    }

    Node &operator[](const T &_key) noexcept {
        Node *node = Search(_key);
        if (node == nullptr) {
            Insert(_key);
            return *Search(_key);
        }
        return *node;
    }

  private:
    void BalanceTreeDelete(Node *_head, const std::stack<Node *> &_stackNode, const std::stack<leftRight> &_stackEdge) {
        int balance = GetBalance(_head);

        // If the balance > 1 then Z = _head->left
        if (balance > 1 && GetBalance(_head->left) >= 0) {
            Rotation(_head, &AVL::LeftRotation, _stackNode, _stackEdge);
            return;
        }

        if (balance > 1 && GetBalance(_head->left) < 0) {
            Rotation(_head, &AVL::RightLeftRotation, _stackNode, _stackEdge);
            return;
        }

        if (balance < -1 && GetBalance(_head->right) <= 0) {
            Rotation(_head, &AVL::RightRotation, _stackNode, _stackEdge);
            return;
        }

        if (balance < -1 && GetBalance(_head->right) > 0) {
            Rotation(_head, &AVL::LeftRightRotation, _stackNode, _stackEdge);
            return;
        }
    }

    void Rotation(Node *_node, std::function<Node *(AVL *, Node *)> func, const std::stack<Node *> &_stackNode,
                  const std::stack<leftRight> &_stackEdge) {
        if (_stackNode.empty()) {
            Node *temp = func(this, _node);
            this->root = temp;
            return;
        }

        Node *parentNode = _stackNode.top();
        leftRight parentEdge = _stackEdge.top();

        Node *newNode = func(this, _node);
        if (parentEdge == Left) {
            parentNode->left = newNode;
            return;
        }
        parentNode->right = newNode;
        return;
    }

    void AssignNodeDirection(Node *_dst, Node *_src, leftRight _direction) {
        if (_dst == nullptr) {
            return;
        }
        if (_direction == Left) {
            _dst->left = _src;
            return;
        }
        _dst->right = _src;
    }

    void RemoveNode(Node *_head, std::stack<Node *> &_stackNode, std::stack<leftRight> &_stackEdge) {
        if (_head->IsLeaf()) {
            AssignParent(nullptr, _stackNode, _stackEdge);
            delete _head;
            _head = nullptr;
            return;
        }

        // the left node is not null
        if (_head->right == nullptr) {
            AssignParent(_head->left, _stackNode, _stackEdge);
            _head->left = nullptr;
            delete _head;
            _head = nullptr;
            return;
        }

        // the right node is not null
        if (_head->left == nullptr) {
            AssignParent(_head->right, _stackNode, _stackEdge);
            _head->right = nullptr;
            delete _head;
            _head = nullptr;
            return;
        }

        // both right and left node is not null
        // first we find the smallest children in right sub tree
        // replace the node with the smallest children
        // delete edge from smallest children parent left
        std::pair<Node *, std::stack<Node *>> pairSmallest = MinValueNode(_head->right, _head);
        Node *smallestNode = pairSmallest.first;
        std::stack<Node *> smallestParent = pairSmallest.second;

        _head->key = std::move(smallestNode->key);
        _head->value = std::move(smallestNode->value);

        // Because the smallest left node doesn't have a left subtree
        // (there can't be a smaller subtree than it
        // So we only copy the sub tree from the right to it parent
        Node *topParrent = smallestParent.top();
        if (smallestParent.size() == 1) {
            topParrent->right = smallestNode->left;
        } else {
            topParrent->left = smallestNode->right;
        }

        while (!smallestParent.empty()) {
            Node *eachParent = smallestParent.top();
            smallestParent.pop();

            // Create a temporary stack for
            std::stack<leftRight> tempStack;

            // check if the parent is itself then that node need to be on the right
            if (smallestParent.size() > 1) {
                tempStack.push(Left);
            } else if (smallestParent.size() == 1) {
                tempStack.push(Right);
            }
            // if it is empty then it is the l
            else {
                if (!_stackEdge.empty()) {
                    tempStack.push(_stackEdge.top());
                    std::stack<Node *> tempParent;
                    tempParent.push(_stackNode.top());
                    eachParent->height = 1 + max(NodeHeight(eachParent->left), NodeHeight(eachParent->right));
                    BalanceTreeDelete(eachParent, tempParent, tempStack);
                    continue;
                }
            }
            eachParent->height = 1 + max(NodeHeight(eachParent->left), NodeHeight(eachParent->right));
            BalanceTreeDelete(eachParent, smallestParent, tempStack);
        }

        smallestNode->left = nullptr;
        smallestNode->right = nullptr;
        delete smallestNode;
        smallestNode = nullptr;
        return;
    }

    void AssignParent(Node *_head, std::stack<Node *> &_stackNode, std::stack<leftRight> &_stackEdge) {
        if (_stackNode.empty()) {
            this->root = _head;
            return;
        }
        Node *parentNode = _stackNode.top();
        leftRight direction = _stackEdge.top();
        AssignNodeDirection(parentNode, _head, direction);
        return;
    }

    std::pair<Node *, std::stack<Node *>> MinValueNode(Node *_head, Node *_parent) {
        Node *currentNode = _head;
        std::stack<Node *> parentNode;
        parentNode.push(_parent);
        if (currentNode->left != nullptr) {
            parentNode.push(currentNode);
            currentNode = currentNode->left;
        }
        return {currentNode, parentNode};
    }

    int GetBalance(node_ptr _head) {
        // result
        // > 1 <-> _head.left > _head.right
        // <-1 <-> _head.right > _head.left
        if (_head == nullptr)
            return 0;
        return NodeHeight(_head->left) - NodeHeight(_head->right);
    }

    std::pair<node_ptr, std::pair<Node *, leftRight>> TreeSearch(node_ptr _root, const T &_key) {
        /**
         * param root the root of the tree
         * param key the key to be search in the tree
         * return the parent and current node (nullptr for both if the key doesn't
         * exist)
         */
        Node *currentNode = _root;
        Node *parentNode = nullptr;
        leftRight direction;

        while (currentNode != nullptr) {
            if (_key == currentNode->key) {
                break;
            }

            parentNode = currentNode;
            if (_key < currentNode->key) {
                direction = Left;
                currentNode = currentNode->left;
                continue;
            }

            if (_key > currentNode->key) {
                direction = Right;
                currentNode = currentNode->right;
                continue;
            }
        }

        if (currentNode == nullptr) {
            return {nullptr, {nullptr, Left}};
        }

        return {currentNode, {parentNode, direction}};
    }

    int NodeHeight(node_ptr _head) {
        if (_head == nullptr)
            return 0;
        return _head->height;
    }

    node_ptr LeftRotation(node_ptr head) {
        node_ptr newHead = head->left;
        head->left = newHead->right;
        newHead->right = head;

        head->height = max(NodeHeight(head->left), NodeHeight(head->right)) + 1;
        newHead->height = max(NodeHeight(newHead->left), NodeHeight(newHead->right)) + 1;
        return newHead;
    }

    node_ptr RightRotation(node_ptr head) {
        node_ptr newHead = head->right;
        head->right = newHead->left;
        newHead->left = head;

        head->height = max(NodeHeight(head->left), NodeHeight(head->right)) + 1;
        newHead->height = max(NodeHeight(newHead->left), NodeHeight(newHead->right)) + 1;
        return newHead;
    }

    node_ptr LeftRightRotation(node_ptr head) {
        // [note: 'a_oldright' is 'b']
        //              |                               |           //
        //              a(pos)                          c           //
        //             / \                             / \          //
        //            /   \                           /   \         //
        //          [d]   b(neg)         ==>         a     b        //
        //               / \                        / \   / \       //
        //              c  [g]                    [d] e  f  [g]     //
        //             / \                                          //
        //            e   f                                         //

        node_ptr rightNode = head->right;
        rightNode = LeftRotation(rightNode);
        head->right = rightNode;

        node_ptr newHead = RightRotation(head);
        return newHead;
    }

    node_ptr RightLeftRotation(node_ptr head) {
        // [note: 'a_oldleft' is 'b']
        //             |                               |         //
        //             a(-2)                           c         //
        //            / \                             / \        //
        //           /   \        ==>                /   \       //
        //      (pos)b    [g]                       b     a      //
        //          / \                            / \   / \     //
        //        [d]  c                         [d]  e f  [g]   //
        //            / \                                        //
        //           e   f                                       //

        node_ptr leftNode = head->left;
        leftNode = RightRotation(leftNode);
        head->left = leftNode;

        node_ptr newHead = LeftRotation(head);
        return newHead;
    }
};
} // namespace Tree