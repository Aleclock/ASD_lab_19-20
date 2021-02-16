import editdistancedynamic.EditDistanceDynamic;
import editdistancestatic.EditDistanceStatic;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class EditDistanceApp {

    public static void main(String[] args) throws IOException, Exception {

        Scanner input = new Scanner(System.in);
        /*System.out.println("Enter file path to correct");
        String path_sentence = input.nextLine();

        System.out.println("Enter dictionary file path");
        String path_dict = input.nextLine();*/

        String path_sentence  = "data/correctme.txt";
        String path_dict = "data/dictionary.txt";

        List<String> sentence = readFile(path_sentence);
        List<String> dict = readFile(path_dict);
        sentence = parseSentence(sentence);

        findCorrectWords(sentence, dict);
    }

    static void findCorrectWords(List<String> sentence, List<String> dict) {
        int editDistance, min;
        long startTime;
        List<String> similarWords = new ArrayList<>();

        for (String s: sentence) {
            min = Integer.MAX_VALUE;
            similarWords.clear();
            startTime = System.nanoTime();
            System.out.format("%15s %20s","Word",s + "\n");
            for (String d: dict) {
                if (!(Math.abs(s.length() - d.length()) > min)) {
                    editDistance = EditDistanceDynamic.editDistanceDynamic(s.toLowerCase(),d);
                    //editDistance = EditDistanceStatic.editDistance(s.toLowerCase(), d);
                    if (editDistance < min) {
                        min = editDistance;
                        similarWords.clear();
                        similarWords.add(d);
                    } else if (editDistance == min)
                        similarWords.add(d);
                }
            }
            long endTime = System.nanoTime();
            double duration = (double)(endTime - startTime)/ 1000000000; // time in seconds

            System.out.format("%15s %20s","Correct word",similarWords +"\n");
            System.out.format("%15s %20s","Edit distance",min +"\n");
            System.out.format("%15s %20s","Execution time", duration +"\n");
            System.out.println();
        }
    }

    static List<String> readFile(String path) {
        List <String> fileList = new ArrayList<>(); // TODO change name
        try {
            FileReader in = new FileReader(path);
            BufferedReader br = new BufferedReader(in);
            String line;
            while ((line = br.readLine()) != null) {
                fileList.add(line);
            }
            in.close();
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return fileList;
    }

    static List<String> parseSentence(List<String> input) {
        List<String> container = new ArrayList<>();
        for (String s : input) {
            s = s.replaceAll("[.:,;]", ""); // Remove punct
            container.addAll(Arrays.asList(s.split(" ")));
        }
        return container;
    }
}
