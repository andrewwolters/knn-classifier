package stats;

import java.io.FileNotFoundException;
import java.util.List;
import java.util.Vector;

public class FeatureFileStats {
  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("No feature file specified, expected syntax: FeatStats");
      System.out.println("  java stats.FeatStats featurefile");
      System.out.println();
      System.out.println("This program calculates for every feature of every class in the feature");
      System.out.println("the average and writes this data to stdout");
    } else {
      try {
        FeatureFile ff = new FeatureFile(args[0]);

        // Compute per-class type feature averages ant print them
        List<FeatureFileStimulus> stimuli = ff.getStimuli();
        for (String className : ff.getClassNames()) {
          System.out.print(className + " "); // Print class name
          
          // Loop through all features
          for (int featureIndex = 0; featureIndex < ff.getFeatureCount(); featureIndex++) {
            double avg = 0;
            int avgCounter = 0;
            
            // Calculate per-feature average for the given class name
            for (FeatureFileStimulus stimulus : stimuli) 
              if (stimulus.getTargetClass().equals(className)) {
                avg += stimulus.getFeature(featureIndex); // Calculate sum of feature
                avgCounter++;                               // Count feature occurrences for this classname
              }
            
            avg /= avgCounter;           // Now we have this features average
            System.out.print(avg + " "); 
          }
          
          System.out.println(); // New line for next feature class
        }
                    
        
      } // Catch all featurefile errors
      catch (FeatureFile.MalformedFeatureFileException e) {
        System.err.println("Error in feature file: " + e.getMessage());
      } catch (FileNotFoundException e) {
        System.err.println("Feature file " + args[0] + " not found");
      }
    }
  }
}
