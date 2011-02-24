package stats;

/**
 * This class holds the data of a stimulus that is specified as a line of a feature file
 * 
 * @author Paul K. Gerke
 *
 */
public class FeatureFileStimulus {
  public class MalformedStimulusDescriptionException extends Exception {
    public MalformedStimulusDescriptionException(String msg) {
      super(msg);
    }
  }
  
  protected double[] features = null;
  protected String targetClass = null;
  
  /**
   * This constructor tries to create a new stimulus based on a line of a feature file
   * 
   * @param line
   *   The lien of the feature file
   * @throws MalformedStimulusDescriptionException
   */
  public FeatureFileStimulus(String line) throws MalformedStimulusDescriptionException {
    super();
    
    String[] lineParts = line.split("\\s+");
    if (lineParts.length == 0)
      throw new MalformedStimulusDescriptionException(lineParts + " is not a valid stimulus description");
    
    targetClass = lineParts[0];
    features = new double[lineParts.length - 1];
    for (int i = 1; i < lineParts.length; i++) {
      try {
        features[i - 1] = Double.parseDouble(lineParts[i]);
      }
      catch (NumberFormatException e) {
        throw new MalformedStimulusDescriptionException(lineParts[i] + " is not a valid float");
      }
    }
  }
  
  /**
   * Returns the target class specification
   * @return
   */
  public String getTargetClass() {
    return new String(targetClass);
  }
  
  /**
   * Returns the count of features extracted from the line given to the constructor
   * @return
   */
  public int getFeatureCount() {
    return features.length;
  }
  
  /**
   * Returns a given feature specified by index i. 
   * @param i
   *   0 <= i < getFeatureCount()
   * @return
   */
  public double getFeature(int i) {
    return features[i];
  }
}
