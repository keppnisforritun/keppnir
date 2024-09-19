#include <cstdio>
////////////////////////// QUAD EDGE DATA STRUCTURE ///////////////////////////////////
// First we define the Quad Edge data structure (Guibas and Stofli 1985)
// however, without flips since it is not required for the use case of 
// Delaunay Triangulation
template <typename T>
struct QuadEdge;

template <typename T>
struct Edge
{
    std::size_t n;
    T* data;
    Edge<T>* next;
    // Edge algebra, we refer to the current edge as e, it has an origin and a destination
    // We move in counterclockwise order, next = CCW, prev = CW
    // The next edge with the same origin as e
    inline Edge* Onext() { return next; }
    // The edge from the right face to the left face of e
    inline Edge* Rot() { return n < 3 ? this + 1 : this - 3; }
    // The edge from the destination of e to the origin of e
    inline Edge* Sym() { return n < 2 ? this + 2 : this - 2; }
    // The edge from the left face of e to the right face of e
    inline Edge* RotInv() { return n < 1 ? this + 3 : this - 1; }
    // The previous (next clockwise) edge with the same origin as e
    inline Edge* Oprev() { return Rot()->Onext()->Rot(); }
    // The next edge with the same left face as e
    inline Edge* Lnext() { return RotInv()->Onext()->Rot(); }
    // The next edge with the same right face as e
    inline Edge* Rnext() { return Rot()->Onext()->RotInv(); }
    // The next edge with the same destination as e
    inline Edge* Dnext() { return Sym()->Onext()->Sym(); }
    // The previous edge with the same left face as e
    inline Edge* Lprev() { return Onext()->Sym(); }
    // The previous edge with the same right face as e
    inline Edge* Rprev() { return Sym()->Onext(); }
    // The previous edge with the same destionatino as e
    inline Edge* Dprev() { return RotInv()->Onext()->RotInv(); }
    // Additionally we have the edge rings Org, Left, Right and Dest in CCW order
    // e Org   = {e, e Onext, e Onext Onext, ..., e Oprev Oprev, e Oprev}
    // e Left  = {e, e Lnext, e Lnext Lnext, ..., e Lprev Lprev, e Lprev}
    // e Right = {e, e Rnext, e Rnext Rnext, ..., e Rprev Rprev, e Rprev}
    // e Dest  = {e, e Dnext, e Dnext Dnext, ..., e Dprev Dprev, e Dprev}
    inline T* Org() { return data; }
    inline T* Dest() { return Sym()->data; }
    inline void SetOrg(const T* val) { data = val; }
    inline void SetDest(const T* val) { Sym()->SetOrg(val); }
    QuadEdge<T>* Quad() { return (QuadEdge<T>*)(this - n); }
};

template <typename T>
struct QuadEdge
{
    // The edges e, (e Rot), (e Sym) and (e RotInv)
    Edge<T> e[4];
    QuadEdge() {
        for (std::size_t i{ 0ull }; i < 4ull; ++i) {
            e[i].n = i;
            e[i].next = i%2 ? &(e[4-i]) : &(e[i]);
        }
    }
};

// Returns an edge e. It will not be a loop, the following will hold:
// - e Org != e Dest
// - e Left == e Right
// - e Lnext == e Rnext == e Sym
// - e Onext == e Oprev == e
// To construct a loop instead we can use e Rot since
// - e Rot Org == e Rot Dest
// - e Rot Left != e Rot Right
// - e Rot Lnext == e Rot Rnext == e Rot
// - e Rot Onext == e Rot Oprev == e Rot Syma
template <typename T>
Edge<T>* make_edge()
{
    QuadEdge<T>* qe = new QuadEdge<T>();
    return qe->e;
}

// This operation affects the two edge rings a Org and b Org and,
// independently the two edge rings a Left and b Left. In each case,
// (a) if the two rings are distinct, splice will combine them into one;
// (b) if the two are exactly the same ring, Splice wil break it in two separate pieces;
// (c) if the two are the same ring taken with opposite orientation,
//     Splice will Flip (and reverse the order) of a segment of that ring.
// The parameters a and b determine the place where the edge rings wqill be cut and joined.
// For the rings a Org and b Org, the cuts will occur immediately after a and b (CCW);
// for the rings a Left and b Left, the cuts will occur immediately before a Rot and b Rot.
//
// We only need to consider (a) and (b) since we don't have flips
template <typename T>
void splice(Edge<T>* a, Edge<T>* b)
{
    Edge<T>  *alpha = a->Onext()->Rot(),
             *beta = b->Onext()->Rot(),
             *aOnextPrime = b->Onext(),
             *bOnextPrime = a->Onext(),
             *alphaOnextPrime = beta->Onext(),
             *betaOnextPrime = alpha->Onext();

    a->next = aOnextPrime;
    b->next = bOnextPrime;
    alpha->next = alphaOnextPrime;
    beta->next = betaOnextPrime;
}

template <typename T>
void delete_edge(Edge<T>* e)
{
    splice(e, e->Oprev());
    splice(e->Sym(), e->Sym()->Oprev());
    delete e->Quad();
}

/////////////////// TOPOLOGICAL OPERATORS FOR DELAUNAY DIAGRAMS /////////////////////////////

template <typename T>
Edge<T>* connect(Edge<T>* a, Edge<T>* b)
{
    Edge<T>* e = make_edge<T>();
    e->SetOrg(a->Dest());
    e->SetDest(b->Org());
    splice(e, a->Lnext());
    splice(e->Sym(), b);
    return e;
}

template <typename T>
void swap(Edge<T>* e)
{
    Edge<T>* a = e->Oprev();
    Edge<T>* b = e->Sym()->Oprev();
    // first remove old edge
    splice(e, a);
    splice(e->Sym(), b);
    // then add the new one
    splice(e, a->Lnext());
    splice(e->Sym(), b->Lnext());
    e->SetOrg(a->Dest());
    e->SetDest(b->Dest());
}
