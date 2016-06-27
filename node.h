#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <vector>

template <class k, class v>
class Node {

    private:

    protected:
        unsigned int num_children;
        unsigned int num_parents;
        std::vector<Node<k,v>*> children;
        std::vector<Node<k,v>*> parents;
        k key;
        v value;

    public:
        Node(k contained_key,v contained_value);

        v get_value();

        k get_key();

        void set_value(v new_value);

        Node<k, v>* get_parent(k par_key);

        void add_parent(k par_key, v par_value);

        void add_parent(Node<k, v>* par, bool reciprocate = true);

        void remove_parent(k par_key, bool delete_pointer = false, bool reciprocate = true);

        Node<k,v>* get_child(k child_key);

        void add_child(k child_key ,v child_value);

        void add_child(Node<k, v>* child, bool reciprocate = true);

        void remove_child(k child_key, bool delete_pointer = false, bool reciprocate = true);
};

template <class k, class v>
Node<k, v>::Node(k contained_key, v contained_value) : num_children(0), num_parents(0), children(), parents() {
    key = contained_key;
    value = contained_value;
}

template <class k, class v>
v Node<k, v>::get_value() {
    return value;
}

template <class k, class v>
k Node<k, v>::get_key() {
    return key;
}

template <class k, class v>
void Node<k, v>::set_value(v new_value) {
    value = new_value;
}

template <class k, class v>
Node<k, v>* Node<k, v>::get_parent(k par_key) {
    for (int i = 0; i < num_parents; i++) {
        if (parents[i]->get_key() == par_key) {
            return parents[i];
        }
    }
    return nullptr;
}

template <class k, class v>
void Node<k,v>::add_parent(k par_key, v par_value) {
    parents.push_back(new Node<k,v>(par_key, par_value));
    parents[num_parents]->add_child(this, false);
    num_parents++;
}

template <class k, class v>
void Node<k,v>::add_parent(Node<k,v>* par, bool reciprocate) {
    parents.push_back(par);
    if (reciprocate) {
        parents[num_parents]->add_child(this, false);
    }
    num_parents++;
}

template <class k, class v>
void Node<k,v>::remove_parent(k par_key, bool delete_pointer, bool reciprocate) {
    for (int i = 0; i < num_parents; i++) {
        if (parents[i]->get_key() == par_key) {
            if (reciprocate) {
                parents[i]->remove_child(key, false, false);
            }
            if (delete_pointer) {
                delete parents[i];
            }
            parents.erase(i);
            num_parents--;
            return;
        }
    }
}

template <class k, class v>
Node<k,v>* Node<k,v>::get_child(k child_key) {
    for (int i = 0; i < num_children; i++) {
        if (children[i]->get_key() == child_key) {
            return children[i];
        }
    }
    return nullptr;
}

template <class k, class v>
void Node<k, v>::add_child(k child_key, v child_value) {
    children.push_back(new Node<k,v>(child_key, child_value));
    children[num_children]->add_parent(this, false);
    num_children++;
}

template <class k, class v>
void Node<k, v>::add_child(Node<k,v>* child, bool reciprocate) {
    children.push_back(child);
    if (reciprocate) {
        children[num_children]->add_parent(this, false);
    }
    num_children++;
}

template <class k, class v>
void Node<k,v>::remove_child(k child_key, bool delete_pointer, bool reciprocate) {
    for (int i = 0; i < num_children; i++) {
        if (children[i]->get_key() == child_key) {
            if (reciprocate) {
                children[i]->remove_parent(key, false, false);
            }
            if (delete_pointer) {
                delete children[i];
            }
            children.erase(i);
            num_children--;
            return;
        }
    }
}

#endif // NODE_H_INCLUDED

