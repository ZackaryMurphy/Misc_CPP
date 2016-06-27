#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include <memory>

template <class connectee>
class Edge {

    private:
    protected:
        std::shared_ptr<connectee> owner;
        std::shared_ptr<connectee> child;
    public:
        Edge();

        Edge(connectee* own_connect);

        Edge(connectee* own_connect, connectee* child_connect);

        std::shared_ptr<connectee> get_owner() const;

        std::shared_ptr<connectee> get_child() const;

        void set_owner(connectee* new_owner);

        void set_child(connectee* new_child);
};

template <class connectee>
Edge<connectee>::Edge() : owner(), child()
{}

template <class connectee>
Edge<connectee>::Edge(connectee* own_connect) : owner(own_connect), child()
{}

template <class connectee>
Edge<connectee>::Edge(connectee* own_connect, connectee* child_connect) : owner(own_connect), child(child_connect)
{}

template <class connectee>
std::shared_ptr<connectee> Edge<connectee>::get_owner() const {
    return owner;
}

template <class connectee>
std::shared_ptr<connectee> Edge<connectee>::get_child() const {
    return child;
}

template <class connectee>
void Edge<connectee>::set_owner(connectee* new_owner) {
    owner.reset(new_owner);
}

template <class connectee>
void Edge<connectee>::set_child(connectee* new_child) {
    child.reset(new_child);
}

template <class connectee>
inline bool operator==(const Edge<connectee>& lhs, const Edge<connectee>& rhs) {
    return lhs.get_owner() == rhs.get_owner() && lhs.get_child() == rhs.get_child();
}

#endif // EDGE_H_INCLUDED
