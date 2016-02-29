//
//  Graph.h
//  Graph
//
//  Created by Ian Murphy on 2/27/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <list>
#include "Vertex.h"
#include <string>
using std::string;

template <typename V, typename E>
class Graph
{
public:
    Graph();
    Graph(const Graph & cp);
    Graph<V,E> & operator = (const Graph<V,E> & rhs);
    ~Graph();
    
    void AddVertex(V data);
    bool DeleteVertex(V data);
    bool AddEdge(V from, V to, E edge, double weight);
    bool DeleteEdge(V from, V to, E edge);
    void DepthFirst(void(*visit)(V data));
    void BreadthFirst(void(*visit)(V data));
    bool isEmpty();
    
    void Begin();
    void End();
    Vertex<V, E> & GetVertex();
    void MoveNext();
    
    bool IsDone();
    
    std::string GetError();
private:
    std::list<Vertex<V,E>> _vertices;
    int _vertice_count;
    typename std::list<Vertex<V,E>>::iterator _internal;
    std::string _errno;
    
};

template <typename V, typename E>
Graph<V,E>::Graph() : _vertice_count(0)
{
    
}

template <typename V, typename E>
Graph<V,E>::Graph(const Graph & cp) : _vertice_count(cp._vertice_count), _vertices(cp._vertices), _errno(cp._errno), _internal(cp._internal)
{
    
}

template <typename V, typename E>
Graph<V,E> & Graph<V,E>::operator=(const Graph<V, E> &rhs)
{
    if(this != &rhs)
    {
        _vertice_count = rhs._vertice_count;
        _vertices = rhs._vertices;
        _errno = rhs._errno;
        _internal = rhs._internal;
    }
    return *this;
}

template <typename V, typename E>
Graph<V,E>::~Graph()
{
    _vertice_count = 0;
    _errno = "Object destructed";
}

template <typename V, typename E>
void Graph<V,E>::AddVertex(V data)
{
    _vertices.emplace_back(data);
    _vertice_count++;
}

template <typename V, typename E>
bool Graph<V,E>::AddEdge(V from, V to, E edge, double weight)
{
    typename std::list<Vertex<V,E>>::iterator iter = _vertices.begin();

    Vertex<V, E> * v_from = nullptr;
    Vertex<V, E> * v_to = nullptr;
    while(iter != _vertices.end() && (!v_from || !v_to))
    {
        if(iter->GetData() == from)
            v_from = &*iter;
        if(iter->GetData() == to)
            v_to = &*iter;
        iter++;
    }
    if(v_from && v_to)
    {
        v_from->AddEdge(edge, v_to, weight);
        v_to->AddEdge(edge, v_from, weight);
        return true;
    }
    else
    {
        _errno = "Unable to link edge:\n";
        if(!v_to)
            _errno += "The second vertex was not found.\n";
        if(!v_from)
            _errno += "The first vertex was not found.\n";
    }
    return false;
}

template <typename V, typename E>
bool Graph<V,E>::DeleteVertex(V data)
{
    typename std::list<Vertex<V,E>>::iterator iter = _vertices.begin();
    bool found = false;
    while(iter != _vertices.end() && !found)
    {
        if(iter->GetData() == data)
        {
            found = true;
            iter->Begin();
            while(!iter->IsDone())
            {
                iter->RemoveEdge(iter->GetEdge().GetData());
                iter->MoveNext();
            }
            _vertices.erase(iter);
        }
        iter++;
    }
    if(found)
        _vertice_count--;
    else
    {
        _errno = "Unable to remove vertex:\n";
        _errno += "The vertex was not found\n";
        return false;
    }

    return true;
}

template <typename V, typename E>
bool Graph<V,E>::DeleteEdge(V from, V to, E edge)
{
    typename std::list<Vertex<V,E>>::iterator iter = _vertices.begin();
    Vertex<V, E> * v_from = nullptr;
    Vertex<V, E> * v_to = nullptr;
    while(iter != _vertices.end() && (!v_from || !v_to))
    {
        if(iter->GetData() == from)
            v_from = &*iter;
        if(iter->GetData() == to)
            v_to = &*iter;
        iter++;
    }
    if(v_from && v_to)
    {
        v_from->RemoveEdge(edge);
        v_to->RemoveEdge(edge);
    }
    else
    {
        _errno = "Unable to delink edge:\n";
        if(!v_to)
            _errno += "Vertex \"" + to + "\" was not found.\n";
        if(!v_from)
            _errno += "Vertex \"" + from + "\" was not found.\n";
    }

    return false;
}

template <typename V, typename E>
void Graph<V,E>::DepthFirst(void (*visit)(V))
{
    
}

template <typename V, typename E>
void Graph<V,E>::BreadthFirst(void (*visit)(V))
{
    
    for(Begin(); !IsDone(); MoveNext())
    {
        _internal->Processed() = false;
    }
    
    std::list<Vertex<V, E>> queue;
    Begin();
    _internal->Processed() = true;
    queue.push_back(*_internal);
  
    while(!queue.empty())
    {
        Vertex<V, E> vtex = queue.front();
        visit(vtex.GetData());
        queue.pop_front();
        
        Vertex<V, E> adj = vtex;
        for(adj.Begin(); !adj.IsDone(); adj.MoveNext())
        {
            if(!adj.GetEdge().GetLink().Processed())
            {
                adj.GetEdge().GetLink().Processed() = true;
                queue.push_back(adj.GetEdge().GetLink());
            }
        }
    }
}

template <typename V, typename E>
std::string Graph<V,E>::GetError()
{
    return _errno;
}

template <typename V, typename E>
void Graph<V,E>::Begin()
{
    _internal = _vertices.begin();
}

template <typename V, typename E>
void Graph<V,E>::End()
{
    _internal = _vertices.end();
}

template <typename V, typename E>
void Graph<V,E>::MoveNext()
{
    _internal++;
}



template <typename V, typename E>
Vertex<V, E> & Graph<V,E>::GetVertex()
{
    return *_internal;
}

template <typename V, typename E>
bool Graph<V,E>::IsDone()
{
    if(_internal == _vertices.end())
        return true;
    return false;
}

template <typename V, typename E>
bool Graph<V,E>::isEmpty()
{
    return _vertices.empty();
}


#endif /* Graph_h */
