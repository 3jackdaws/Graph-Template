//
//  Edge.h
//  Graph
//
//  Created by Ian Murphy on 2/27/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef Edge_h
#define Edge_h

template <typename V, typename E> class Vertex;
template <typename V, typename E> class Graph;

template <typename V, typename E>
class Edge
{
public:
    friend class Graph<V,E>;
    Edge();
    Edge(E, Vertex<V, E> *, double);
    Edge(const Edge & cp);
    ~Edge();
    Edge<V,E> & operator = (const Edge<V,E> & rhs);
    
    void SetWeight(double);
    void SetData(E);
    void SetLink(Vertex<V, E> *);
    
    double GetWeight();
    E GetData();
    Vertex<V, E> & GetLink();
private:
    E _data;
    Vertex<V, E> * _link;
    double _weight;
};

template <typename V, typename E>
Edge< V, E>::Edge() : _link(nullptr)
{
    
}

template <typename V, typename E>
Edge< V, E>::Edge(E data, Vertex<V, E> * link, double weight) : _link(link), _data(data), _weight(weight)
{
    
}

template <typename V, typename E>
Edge< V, E>::Edge(const Edge<V,E> & cp) : _link(cp._link), _weight(cp._weight), _data(cp._data)
{
    
}

template <typename V, typename E>
Edge<V,E> & Edge< V, E>::operator=(const Edge<V, E> &rhs)
{
    if(this != &rhs)
    {
        _link = rhs._link;
        _data = rhs._data;
        _weight = rhs._weight;
    }
    return *this;
}

template <typename V, typename E>
Edge< V, E>::~Edge()
{
    
}

template <typename V, typename E>
void Edge< V, E>::SetData(E data)
{
    _data = data;
}

template <typename V, typename E>
void Edge< V, E>::SetLink(Vertex<V, E> * link)
{
    _link = link;
}

template <typename V, typename E>
void Edge< V, E>::SetWeight(double weight)
{
    _weight = weight;
}

template <typename V, typename E>
E Edge< V, E>::GetData()
{
    return _data;
}

template <typename V, typename E>
double Edge< V, E>::GetWeight()
{
    return _weight;
}

template <typename V, typename E>
Vertex<V, E> & Edge< V, E>::GetLink()
{
    return *_link;
}

#endif /* Edge_h */
