//
//  Vertex.h
//  Graph
//
//  Created by Ian Murphy on 2/27/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

#include "Edge.h"

//template <typename V, typename E> class Graph;

template <typename V, typename E>
class Vertex
{
public:
    
    friend class Graph<V,E>;
    Vertex();
    Vertex(V data);
    Vertex(const Vertex & cp);
    Vertex<V,E> & operator = (const Vertex<V,E> & cp);
    
    V GetData();
    void SetData(V);

    void AddEdge(E, Vertex<V,E> *,double);
    bool RemoveEdge(E);
    
    void Begin();
    void MoveNext();
    //void GetPrev();
    bool IsDone();
    Edge<V,E> & GetEdge();
    bool & Processed();
    
    bool ExistsEdge(E data);

private:
    
    V _data;
    bool _processed;
    std::list<Edge<V, E>> _edges;
    typename std::list<Edge<V, E>>::iterator _internal;
    
    
};

template <typename V, typename E>
Vertex<V, E>::Vertex() : _processed(false)
{
    
}

template <typename V, typename E>
Vertex<V, E>::Vertex(V data) : _processed(false), _data(data)
{
    
}

template <typename V, typename E>
Vertex<V, E>::Vertex(const Vertex & cp) : _processed(cp._processed), _edges(cp._edges), _data(cp._data)
{
    
}

template <typename V, typename E>
Vertex<V,E> & Vertex<V, E>::operator=(const Vertex<V, E> & rhs)
{
    if(this != &rhs)
    {
        _data = rhs._data;
        _processed = rhs._processed;
        _edges = rhs._edges;
    }
    return *this;
}

template <typename V, typename E>
V Vertex<V, E>::GetData()
{
    return _data;
}

template <typename V, typename E>
void Vertex<V,E>::SetData(V data)
{
    _data = data;
}

template <typename V, typename E>
void Vertex<V, E>::AddEdge(E data, Vertex<V,E> * link, double weight)
{
    _edges.emplace_back(data, link, weight);
}

template <typename V, typename E>
bool Vertex<V, E>::RemoveEdge(E data)
{
    typename std::list<Edge<V,E>>::iterator iter = _edges.begin();
    bool found = false;
    bool found_other = false;
    while(iter != _edges.end() && !found)
    {
        if(iter->GetData() == data)
        {
            found = true;
            
            iter->GetLink().Begin();
            
            while(!iter->GetLink().IsDone() && !found_other)
            {
                if(iter->GetLink().GetEdge().GetData() == data)
                {
                    iter->GetLink()._edges.erase(iter->GetLink()._internal);
                    found_other = true;
                }
                iter->GetLink().MoveNext();
            }
            _edges.erase(iter);
        }
        iter++;
    }
    return found;
}

template <typename V, typename E>
void Vertex<V, E>::Begin()
{
    _internal = _edges.begin();
}

template <typename V, typename E>
void Vertex<V, E>::MoveNext()
{
    _internal++;
}


template <typename V, typename E>
Edge<V, E> & Vertex<V, E>::GetEdge()
{
    return *_internal;
}

template <typename V, typename E>
bool Vertex<V, E>::IsDone()
{
    return _internal == _edges.end();
}

template <typename V, typename E>
bool & Vertex<V, E>::Processed()
{
    return _processed;
}

template <typename V, typename E>
bool Vertex<V, E>::ExistsEdge(E data)
{
    bool found = false;
    typename std::list<Edge<V, E>>::iterator iter;
    for (iter = _edges.begin(); !found && iter != _edges.end(); iter++)
    {
        if(iter->GetData() == data)
        {
            found = true;
        }
    }
    return found;
}
#endif /* Vertex_h */
