import graphutils.Edge;
import graphutils.Node;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

/**
 * Graph class
 * adjList: Adjacency List (as HashMap <Node, ArrayList<Edge>>
 * indexes: Hashmap containing Nodes
 */
public class Graph {
  HashMap<Node, ArrayList<Edge>> adjList;
  HashMap<Node, Integer>  indexes;
  int index;

  public Graph () {
    this.adjList = new HashMap<>();
    this.indexes = new HashMap<>();
    this.index = -1;
  }
  public Graph (int size) {
    this.adjList = new HashMap<>(size);
    this.indexes = new HashMap<>(size);
    this.index = size;
  }

  public Graph(ArrayList<Node> vertices) {
    for (int i = 0; i <vertices.size() ; i++) {
      Node vertex = vertices.get(i);
      ArrayList<Edge> list = new ArrayList<>();
      adjList.put(vertex, list);
      indexes.put(vertex, ++index);
    }
  }

  public HashMap<Node, ArrayList<Edge>> getAdjList() {
    return adjList;
  }

  public HashMap<Node, Integer> getIndexes() {
    return indexes;
  }

  /**
   * Add node to graph (adjancy list and indexes) if not already stored
   * @param node: node to add in Graph
   */
  public void addNode(Node node) {
    if (!adjList.containsKey(node)) {
      ArrayList<Edge> edges = new ArrayList();
      adjList.put(node, edges);
      indexes.put(node, ++this.index);
      // TODO però deve aggiornare index
    }
  }

  /**
   * Add edge in both Node's adjancy list
   * @param edge: Edge edge (node1, node2, weight)
   */
  public void addEdge(Edge edge) {
    ArrayList<Edge> list1 = adjList.get(edge.getNode1());
    ArrayList<Edge> list2 = adjList.get(edge.getNode2());
    list1.add (edge);
    list2.add (edge);
    adjList.put(edge.getNode1(), list1);
    adjList.put(edge.getNode2(), list2);
  }

  /**
   * Print graph composition as Node_value  [list_of_edges weight]
   */
  public void printGraph() {
    Set<Node> set = adjList.keySet();
    Iterator<Node> iterator = set.iterator();

    System.out.println("__ Start");
    while(iterator.hasNext()){
      Node vertex = iterator.next();
      System.out.print(vertex.getValue() + "\t\t");
      ArrayList<Edge> list = adjList.get(vertex);
      for (int i = 0; i <list.size() ; i++) {
        System.out.print("( " + list.get(i).getNode1().getValue() + " , " + list.get(i).getNode2().getValue() + " ) w: " + list.get(i).getWeight() + "\t\t");
      }
      System.out.println();
    }
    System.out.println("__ Finish");
  }
}
