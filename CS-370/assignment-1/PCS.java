import java.io.IOException;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

class Domino {
  public String top;
  public String bottom;

  public Domino(String top, String bottom) {
    this.top = top;
    this.bottom = bottom;
  }

  @Override
  public String toString() {
    return String.format("%s : %s", this.top, this.bottom);
  }

  @Override
  public int hashCode() {
    // overriding hashcode returned by Domino objects
    String dominoString = this.top + this.bottom;

    return dominoString.hashCode();
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;

    if (obj == null)
      return false;

    if (getClass() != obj.getClass())
      return false;

    Domino other = (Domino) obj;
    if (this.top == other.top && this.bottom == other.bottom)
      return false;

    return true;
  }
}

class State {
  String diff; // + -
  ArrayList<Domino> dominoes;
  State parent;
}

class Graph {
  private int maxQueueSize;
  private int maxNumStates;
  private int numDominoes;
  private Boolean verboseMode;
  private HashMap<String, Domino> dominoPool;
}

public class PCS {

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("missing input file name");
      System.exit(0);
    }

    String fileName = args[0];

    int maxQueueSize = 0;
    int maxNumStates = 0;
    Boolean verboseMode = false;
    int numDominoes = 0;
    Map<String, Domino> dominoPool = new HashMap<String, Domino>();

    // read the input file
    try {
      List<String> lines = Files.readAllLines(new File(fileName).toPath(), Charset.defaultCharset());

      maxQueueSize = Integer.parseInt(lines.get(0).trim());
      maxNumStates = Integer.parseInt(lines.get(1).trim());
      verboseMode = Boolean.parseBoolean(lines.get(2).trim());
      numDominoes = Integer.parseInt(lines.get(3).trim());

      for (int i = 1; i <= numDominoes; i++) {
        String[] line = lines.get(i + 3).trim().split("\\s+");

        String top = line[line.length - 2];
        String bottom = line[line.length - 1];

        Domino d = new Domino(top, bottom);
        dominoPool.put("D" + i, d);
      }
    } catch (IOException e) {
      System.out.printf("Unable to open file, \"%s\"\n", fileName);
      System.exit(1);
    } catch (Exception e) {
      System.out.println("Error parsing input file");
      System.exit(1);
    }

    System.out.printf("max queue size: %d\n", maxQueueSize);
    System.out.printf("max num states: %d\n", maxNumStates);
    System.out.printf("verbose: %b\n", verboseMode);
    System.out.printf("num dominoes: %d\n", numDominoes);

    for (String key : dominoPool.keySet()) {
      System.out.printf("key: %s, domino: %s\n", key, dominoPool.get(key));
    }
  }
}