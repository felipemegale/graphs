import java.util.*;
import java.io.*;

class Graph {

  private int vertices[][];
  private int numberOfVertices;
  private ArrayList<String> subjects;
  private ArrayList<String> subjectIndex;
  private ArrayList<String> subjectGraph[];

  // Class constructor
  // index is the list with only one occurence of each subject
  // subjectList is the raw input
  public Graph(int numberOfSubjects, ArrayList<String> index, ArrayList<String> subjectList) {
    
    numberOfVertices = numberOfSubjects;
    vertices = new int[numberOfVertices][numberOfVertices];
    subjectGraph = new ArrayList[numberOfVertices];
    subjectIndex = index;
    subjects = subjectList;

    for (int i = 0; i < subjectGraph.length; i++)
      subjectGraph[i] = new ArrayList<>();
    
  }

  /**
   * Populates the graph with all elements needed.
   * @param readList contains the raw input
   */
  public void populateSubjectGraph() {

    String[] tokenSemiColon;
    String[] tokenComma;

    for (int i = 0; i < subjects.size(); i++) {
      
      tokenSemiColon = subjects.get(i).split(";");
      
      if (tokenSemiColon.length == 1) {

        subjectGraph[i].add(tokenSemiColon[0]);

      } else {

        subjectGraph[i].add(tokenSemiColon[0]);

        tokenComma = tokenSemiColon[1].split(",");

        for (int j = 0; j < tokenComma.length; j++){

          subjectGraph[i].add(tokenComma[j]);

        }
      }
    }
  }
  
  // Adds all edges to integer matrix
  public void addEdges() {

    int subPosition;
    String subject;

    
    
  }

  /**
   * Prints all subjects and their dependencies
   */
  public void printSubjectGraph() {

    for (int i = 0; i < subjectGraph.length; i++) {

      for (int j = 0; j < subjectGraph[i].size(); j++) {

        System.out.println(subjectGraph[i].get(j));

      }

    }

  }

  /**
   * Prints all elements present in a given graph
   */
  public void printElements() {

    for (int i = 0; i < numberOfVertices; i++) {

      for (int j = 0; j < numberOfVertices; j++) {

        System.out.println(vertices[i][j]);

      }

    }

  }

}

public class TopSort {

  /**
   * Adds all lines as is to a list
   * @return An ArrayList containing all lines in stdin
   */
  public static ArrayList<String> readList() {

    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    ArrayList<String> readList = new ArrayList<>();
    String subject;

    try {

      subject = reader.readLine();

      while (subject != null) {

        readList.add(subject);
        subject = reader.readLine();

      }

    } catch (IOException ioe) {ioe.printStackTrace();}

    return readList;
  }

  /**
   * Splits the lines into subject and dependencies
   * @param readList An ArrayList containing raw information offered by
   * function readList().
   * @return A partially processed list containing a line with subject and
   * another following line with its dependencies
   */
  public static ArrayList<String> partialProcess(ArrayList<String> readList) {
    
    ArrayList<String> partialProcessedList = new ArrayList<>();
    String[] innerSubjects;

    for (String str : readList) {

      innerSubjects = str.split(";");

      for (int i = 0; i < innerSubjects.length; i++)
        partialProcessedList.add(innerSubjects[i]);

      }

    return partialProcessedList;
  }

  /**
   * Splits the lines into subjects and dependencies
   * @param partialProcessedList is a partially processed subjects list that contains
   * a line with a subject and the following line, its dependencies
   * @return a final list, where each line is a subject
   */
  public static ArrayList<String> finalList(ArrayList<String> partialProcessedList) {

    ArrayList<String> finalList = new ArrayList<>();
    String[] innerSubjects;

    for (String str : partialProcessedList) {
      
      innerSubjects = str.split(",");
      
      for (int i = 0; i < innerSubjects.length; i++)
        finalList.add(innerSubjects[i]);

    }

    return finalList;
  }

  /**
   * Creates a subject list with only one subject occurence. This is used to determine
   * how many subjects there are in the graph.
   * @param finalList is a list containing all subjects read from stdin, one per line
   * @return a list with only one occurence of each subject
   */
  public static ArrayList<String> subjectList(ArrayList<String> finalList) {

    ArrayList<String> subjectList = new ArrayList<>();

    for (String str : finalList) {
      
      if (!subjectList.contains(str))
        subjectList.add(str);

    }

    return subjectList;

  }

  public static void main(String[] args) {

    ArrayList<String> readList = readList();
    ArrayList<String> partialProcessedList = partialProcess(readList);
    ArrayList<String> finalList = finalList(partialProcessedList);
    ArrayList<String> subjectList = subjectList(finalList);

    Graph graph = new Graph(subjectList.size(), subjectList, readList);

    graph.populateSubjectGraph();
    // graph.printSubjectGraph();
    // graph.printElements();

  }
}