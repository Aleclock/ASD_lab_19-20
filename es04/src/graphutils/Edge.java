package graphutils;

/**
 * Class representing Edge between two nodes
 * node1, node2 : Nodes
 * weight: weight of edge
 */
public class Edge {
    private final Node node1;
    private final Node node2;
    private final int weight;

    public Edge() {
        this.node1 = null;
        this.node2 = null;
        this.weight = 0;
    }

    public Edge (Node node1, Node node2, int weight) {
        this.node1 = node1;
        this.node2 = node2;
        this.weight = weight;
    }

    public int getWeight() {
        return weight;
    }

    public Node getNode1() {
        return node1;
    }

    public Node getNode2() {
        return node2;
    }
}
