//
//  main.cpp
//  Graph
//
//  Created by Ian Murphy on 2/27/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
#include "Graph.h"

void Print(string data)
{
    cout<<data<<endl;
}

bool Error(string emsg)
{
    cout<<"Error: " + emsg << endl;
    return true;
}

int main(int argc, const char * argv[]) {
    
    Graph<string, string> mygraph;
    cout<<"===   Add Vertices   ==="<<endl;
    mygraph.AddVertex("Troutdale");
    mygraph.AddVertex("Gresham");
    mygraph.AddVertex("Portland");
    mygraph.AddVertex("Sandy");
    mygraph.AddVertex("Fairview");
    mygraph.AddVertex("Rockwood");
    mygraph.AddVertex("Welches");
    
    
    
    cout<<"===   Add Edges   ==="<<endl;
    mygraph.AddEdge("Troutdale", "Gresham", "Road", 10) || cout<<mygraph.GetError();
    mygraph.AddEdge("Troutdale", "Sandy", "Orient Drive", 20) || cout<<mygraph.GetError();
    mygraph.AddEdge("Troutdale", "Portland", "Stark Street", 23) || cout<<mygraph.GetError();
    mygraph.AddEdge("Gresham", "Rockwood", "Stark Street", 5) || cout<<mygraph.GetError();
    mygraph.AddEdge("Troutdale", "Fairview", "257th Drive", 6) || cout<<mygraph.GetError();
    mygraph.AddEdge("Gresham", "rprpf", "Stark Street", 23) || cout<<mygraph.GetError();
    
    for(mygraph.Begin(); !mygraph.IsDone(); mygraph.MoveNext())
    {
        cout<<mygraph.GetVertex().GetData()<<endl;
        mygraph.GetVertex().Begin();
        for (mygraph.GetVertex().Begin(); !mygraph.GetVertex().IsDone(); mygraph.GetVertex().MoveNext())
        {
            cout<<mygraph.GetVertex().GetEdge().GetData()<< " to " << mygraph.GetVertex().GetEdge().GetLink().GetData() <<
            ", Length: "<< mygraph.GetVertex().GetEdge().GetWeight() << endl;
        }
    }
//
    Graph<string, string> graph2(mygraph);
    mygraph.DeleteVertex("Troutdale");
    for(mygraph.Begin(); !mygraph.IsDone(); mygraph.MoveNext())
    {
        cout<<mygraph.GetVertex().GetData()<<endl;
        mygraph.GetVertex().Begin();
        for (mygraph.GetVertex().Begin(); !mygraph.GetVertex().IsDone(); mygraph.GetVertex().MoveNext())
        {
            cout<<"\t"<<mygraph.GetVertex().GetEdge().GetData()<< " to " << mygraph.GetVertex().GetEdge().GetLink().GetData() <<
            ", Length: "<< mygraph.GetVertex().GetEdge().GetWeight() << endl;
        }
    }
    for(graph2.Begin(); !graph2.IsDone(); graph2.MoveNext())
    {
        cout<<graph2.GetVertex().GetData()<<endl;
        graph2.GetVertex().Begin();
        for (graph2.GetVertex().Begin(); !graph2.GetVertex().IsDone(); graph2.GetVertex().MoveNext())
        {
            cout<<"\t"<<graph2.GetVertex().GetEdge().GetData()<< " to " << graph2.GetVertex().GetEdge().GetLink().GetData() <<
            ", Length: "<< graph2.GetVertex().GetEdge().GetWeight() << endl;
        }
    }

    cout<<" = = = = = INT Testing = = = = = "<<endl;
    
    Graph<int, string> intGraph;
    for (int i = 0; i<200; i++)
    {
        intGraph.AddVertex(i);
    }
    srand(time(NULL));
    for (int i = 0; i<100; i++)
    {
        intGraph.AddEdge(rand()%200, rand()%200, "Path", (rand()%1000)/2.3);
    }
    for(intGraph.Begin(); !intGraph.IsDone(); intGraph.MoveNext())
    {
        cout<<intGraph.GetVertex().GetData()<<endl;
        intGraph.GetVertex().Begin();
        for (intGraph.GetVertex().Begin(); !intGraph.GetVertex().IsDone(); intGraph.GetVertex().MoveNext())
        {
            cout<<"\t"<<intGraph.GetVertex().GetEdge().GetData()<< " to " << intGraph.GetVertex().GetEdge().GetLink().GetData() <<
            ", Length: "<< intGraph.GetVertex().GetEdge().GetWeight() << endl;
        }
    }

    

//    for (intGraph.Begin(); !intGraph.IsDone(); intGraph.MoveNext())
//    {
//        cout<<intGraph.GetVertex().GetData()<<endl;
//    }
//    
//    Graph<int, int> intGraph2(intGraph);
//    for (int i = 5; i<490; i++)
//    {
//        if(i>30)
//            intGraph2.DeleteVertex(i) || cout<<intGraph2.GetError();
//    }
//    for (intGraph2.Begin(); !intGraph2.IsDone(); intGraph2.MoveNext())
//    {
//        cout<<intGraph2.GetVertex().GetData()<<endl;
//    }
//    
//    mygraph.AddVertex("Test");
//    mygraph.AddVertex("Test 2");
//    mygraph.DeleteVertex("Test");
//    mygraph.AddEdge("Test", "Test 2", "Testerino", 2.4);
//    mygraph.DeleteEdge("Test", "Test 2", "Testerino");
    mygraph.DepthFirst(&Print);
//    mygraph.BreadthFirst(&Print);
//    mygraph.isEmpty();
//    
//    mygraph.Begin();
//    mygraph.End();
//    mygraph.GetVertex();
//    mygraph.MoveNext();
//    
//    mygraph.IsDone();
//    
//    mygraph.GetError();
//    
//    mygraph.BreadthFirst(&Print);
//    
//    Vertex<string, string> testVertex;
//    Vertex<string, string> testVertex2("Hi there");
//    testVertex = testVertex2;
//    cout<<testVertex.GetData()<<endl;
    return 0;
}
