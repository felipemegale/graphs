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
  
  /**
   * Adds all edges to the graph
   */
  public void addEdges() {

    // subCoord == subject coordinate
    // depCoord == dependency coordinate
    int subCoord = 0;
    int depCoord = 0;
    String subject, dependency;

    // arrPos == array position
    // for each entry, do
    for (int arrPos = 0; arrPos < subjectGraph.length; arrPos++) {

      subject = subjectGraph[arrPos].get(0);

      // depNum == dependency number
      // for each dependency, do
      for (int depNum = 1; depNum < subjectGraph[arrPos].size(); depNum++) {

        dependency = subjectGraph[arrPos].get(depNum);

        // subInd == subject index
        // get subject's and its dependency position in the subject list
        for (int subInd = 0; subInd < subjectIndex.size(); subInd++) {

          if (subject.compareTo(subjectIndex.get(subInd)) == 0) {

            subCoord = subInd;

          } else if (dependency.compareTo(subjectIndex.get(subInd)) == 0) {

            depCoord = subInd;

          }
        }

        vertices[subCoord][depCoord] = 1;

      }
    }
  }

  /**
   * Finds whether a line in the matrix contains only zeroes
   * @param lineNumber is the line one wishes to analyze
   * @param vertices is the matrix one wishes to analyze
   * @return Whether the line analyzed has only zeroes
   */
  public boolean onlyZeroes(int lineNumber, int[][] matrix) {

    boolean isZeroes = true;

    for (int i = 0; i < numberOfVertices; i++)
      if (matrix[lineNumber][i] == 1)
        isZeroes = false;

    return isZeroes;
  }

  /**
   * Finds whether a graph has no more edges
   * @param matrix The adjacency matrix one wishes to analyze
   * @return whether the matrix analyzed has no edges
   */
  public boolean noEdges(int[][] matrix) {

    boolean noEdges = true;

    for (int i = 0; i < numberOfVertices; i++)
      for (int j = 0; j < numberOfVertices; j++)
        if (matrix[i][j] == 1)
          noEdges = false;

    return noEdges;
  }


  /**
   * Runs Kahn's algorithm to return a topologically sorted list of subjects
   */
  public ArrayList<String> topologicalSorting() {

    // subjInd is the index of the subject in the sorted list
    // tempVert is a copy of the integer matrix vertices
    int subjInd;
    int tempVert[][] = vertices;
    ArrayList<String> temp = new ArrayList<>();
    ArrayList<String> sorted = new ArrayList<>();

    // Gets all vertices without input arc
    for (int i = 0; i < subjectGraph.length; i++) {
      if (subjectGraph[i].size() == 1)
        temp.add(subjectGraph[i].get(0));
    }

    while (!temp.isEmpty()) {

      sorted.add(temp.get(0));
      subjInd = subjectIndex.indexOf(temp.get(0));
      temp.remove(0);

      /*
       * Percorre a coluna daquela materia
       * para achar as materias que dependem dela
       */
      for (int i = 0; i < numberOfVertices; i++) {

        // se tiver dependencia, tira a aresta e verifica se essa
        // materia ainda depende de outras
        if (tempVert[i][subjInd] == 1) {

          tempVert[i][subjInd] = 0;

          if (onlyZeroes(i, tempVert))
            temp.add(subjectIndex.get(i));
        }
      }
    }

    return sorted;
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
   * Prints the subject-dependency matrix
   */
  public void printMatrix() {

    for (int i = 0; i < numberOfVertices; i++) {

      for (int j = 0; j < numberOfVertices; j++) {

        System.out.print(vertices[i][j] + " ");

      }

      System.out.println();

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
    int ignore;

    try {

      ignore = Integer.parseInt(reader.readLine());
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
    ArrayList<String> sortedList;

    Graph graph = new Graph(subjectList.size(), subjectList, readList);

    graph.populateSubjectGraph();
    graph.addEdges();
    // graph.printSubjectGraph();
    // graph.printMatrix();
    sortedList = graph.topologicalSorting();

    for (String str : sortedList)
      System.out.println(str);

  }
}