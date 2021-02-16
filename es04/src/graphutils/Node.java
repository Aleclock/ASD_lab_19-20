package graphutils;

/**
 * Class representing nodes
 * value: node value
 * father
 */
public class Node {
    private final int value;
    private final Node father;

    public Node () {
        this.value = 0;
        this.father = null;
    }

    public Node (int value) {
        this.value = value;
        this.father = null;
    }

    public Node (int value, Node father) {
        this.value = value;
        this.father = father;
    }

    public int getValue() {
        return value;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        return value == ((Node) o).value;
    }

    @Override
    public int hashCode() {
        // TODO fare hashcode
        return value;
    }
}
