import graphutils.Edge;
import graphutils.Node;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;

// javac GraphApp.java
// ruby run-tests.rb --args "java GraphApp"
public class GraphApp {
    public static void main(String[] args){

        //String input_path = "/Users/aleclock/Desktop/uni/ASD/laboratorio-algoritmi-2019-20/es04/src/test1/input.txt";
        String input_path = "/Users/aleclock/Desktop/uni/ASD/laboratorio-algoritmi-2019-20/es04/src/_test/tests.txt";
        String correct_path = "/Users/aleclock/Desktop/uni/ASD/laboratorio-algoritmi-2019-20/es04/src/test1/correct.txt";
        String output_path = "/Users/aleclock/Desktop/uni/ASD/laboratorio-algoritmi-2019-20/es04/src/test1/output.txt";

        //String input_path = args[0];
        //String correct_path = args[1];

        // Read file and create graph
        HashMap<Node, ArrayList<Edge>> graph = new HashMap<Node, ArrayList<Edge>>();

        String[] questions = fillGraph(graph, input_path);

        // Question answering
        File file = new File (output_path);
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(file))) {
            for (String q : questions)
                askQuestion(graph, q, bw);
        } catch (IOException e) {
            e.printStackTrace();
        }


        //checkResults(correct_path, output_path);

    }

    /**
     * This function read input_path file and fill graph HashMap. Then read questions
     * @param graph : HashMap
     * @param input_path: path to input file
     * @return list of questions
     */
    private static String[] fillGraph (HashMap<Node, ArrayList<Edge>> graph, String input_path) {
        File file = new File(input_path);
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            Node node1;
            Node node2;
            Edge edge;
            Graph graph_prova = new Graph();
            if ((line = br.readLine()) != null) {

                // Read graph composition
                int nodes_number = Integer.parseInt(line);
                for (int i = 0; i < nodes_number -1 && (line = br.readLine()) != null; i++) {
                    String[] node_line = line.split(" ");
                    node1 = new Node(Integer.parseInt(node_line[0]));
                    node2 = new Node(Integer.parseInt(node_line[1]));
                    edge = new Edge(node1, node2, Integer.parseInt(node_line[2]));

                    graph_prova.addNode(node1);
                    graph_prova.addNode(node2);
                    graph_prova.addEdge(edge);

                    //graph_prova.printGraph();
                }

                // Read questions
                int questions_number = Integer.parseInt(br.readLine());
                String[] result = new String[questions_number];
                for (int j = 0; j < questions_number && (line = br.readLine()) != null; j++) {
                    result[j] = line;
                    // TODO valutare di ritornare lista di Edge
                }

                return result;
            } else
                return null;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    private static void askQuestion (HashMap<Node, ArrayList<Edge>> graph, String question, BufferedWriter bw) {
        String[] params = question.split(" ");
        Node node1 = new Node(Integer.parseInt(params[0]));
        Node node2 = new Node(Integer.parseInt(params[1]));
        Edge edge = new Edge(node1, node2, Integer.parseInt(params[2]));

        try {
            if (node1.getValue() == node2.getValue()) { // circular edge (not admitted)
                bw.write("NO\n");
            } else {
                // ADD node to graph
                // calulate MST
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Compare each result in correct and answer file
     * @param correct : file path containing correct answer
     * @param answer : file path containing exe
     */
    private static void checkResults (String correct, String answer) {
        try {
            BufferedReader bw_correct = new BufferedReader(new FileReader(new File(correct)));
            BufferedReader bw_answer = new BufferedReader(new FileReader(new File(answer)));
            String line_correct = "";
            String line_answer = "";

            while ((line_correct = bw_correct.readLine()) != null && (line_answer = bw_answer.readLine()) != null) {
                if (!line_correct.equalsIgnoreCase(line_answer))
                    return;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
