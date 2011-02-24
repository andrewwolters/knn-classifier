package stats;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import stats.FeatureFileStimulus.MalformedStimulusDescriptionException;

/**
 * This class reads data from a feature file and holds the extracted stimuli data.
 * 
 * @author Paul K. Gerke
 *
 */
public class FeatureFile {
  public class MalformedFeatureFileException extends Exception {
    public MalformedFeatureFileException(String msg) {
      super(msg);
    }
  }
  
  protected List<FeatureFileStimulus> featureList = new ArrayList<FeatureFileStimulus>();
  
  protected List<String> classNames = new ArrayList<String>();
  
  protected int stimulusCount = 0;
  protected int featureCount = 0;
  protected int classCount = 0;
  
  public FeatureFile(String fileName) throws MalformedFeatureFileException, FileNotFoundException  {
    super();
    
    // define error that occures if something is wrong with the header
    final String HEADER_ERROR = "First line of feature file is expected to be header information in the form \"simulusCount featureCount classCount\"";

    // File scanner to read the given file
    Scanner scn = new Scanner(new File(fileName));

    try {
      int lineIndex = 0;

      // Try to read and interpret header line
      if (!scn.hasNext())
        throw new MalformedFeatureFileException(HEADER_ERROR);
        
      String headerLine = scn.nextLine().trim();
      String[] headerLineParts = headerLine.split("\\s+");
      if (headerLineParts.length != 3)
        throw new MalformedFeatureFileException(HEADER_ERROR);

      // Parse the values
      try {
        stimulusCount = Integer.parseInt(headerLineParts[0]);
        featureCount = Integer.parseInt(headerLineParts[1]);
        classCount = Integer.parseInt(headerLineParts[2]);
      }
      catch (NumberFormatException e) {
        throw new MalformedFeatureFileException(HEADER_ERROR);
      }
      // Header is also a line
      lineIndex++;
      
      while (scn.hasNext()) {
        String line = scn.nextLine().trim();
        lineIndex++;
        
        if (line.length() == 0) // A bit dirty... makes the algorithm ignore empty lines in the feature file
          continue;
        
        // Try to interpret the following line 
        FeatureFileStimulus ffs = null;
        try {
          ffs = new FeatureFileStimulus(line); 
        } catch (MalformedStimulusDescriptionException e) {
          throw new MalformedFeatureFileException("Error interpreting line " + lineIndex + ": " + e.getMessage());
        }
        
        // Check if the amount of features extracted from the last line is correct
        if (ffs.getFeatureCount() != featureCount)
          throw new MalformedFeatureFileException("Line " + lineIndex + " contains wrong amount of features according to the header definition");
        
        // Collect all different target class names
        if (!classNames.contains(ffs.getTargetClass()))
          classNames.add(ffs.getTargetClass());
        
        // Nothing until now went wrong... add stimulus to stimuli-list
        featureList.add(ffs);
      }
  
      // If the count of classes differs from the amount spcified in the header the file is malformed:
      if (classNames.size() != classCount)
        throw new MalformedFeatureFileException("Feature file contains " + classNames.size() + " different classes but should have " + classCount);
  
      // If the count of stimuli differs from the amount spcified in the header the file is malformed:
      if (featureList.size() != stimulusCount)
        throw new MalformedFeatureFileException("Feature file contains " + featureList.size() + " stimuli but should contain " + stimulusCount);
    }
    finally {
      scn.close(); // always close the opened feature file
    }
  }

  /**
   * This function returns a copy of the internal list of stimuli.
   * @return
   */
  public List<FeatureFileStimulus> getStimuli() {
    return new ArrayList<FeatureFileStimulus>(featureList);
  }

  /**
   * Returns the in the feature file spcified amount of classes
   * @return
   */
  public int getClassCount() {
    return classCount;
  }

  /**
   * Returns the in the feature file specified amount of features per stimulus
   * @return
   */
  public int getFeatureCount() {
    return featureCount;
  }
  
  /**
   * Returns the count of stimuli
   * @return
   */
  public int getStimulusCount() {
    return stimulusCount;
  }
  
  /**
   * Returns all class identifiers used in the feature file (thus all "class names" for a given stimuli)
   * @return
   */
  public List<String> getClassNames() {
    return new ArrayList<String>(classNames);
  }
}
