package carwash.view.scenecontroller;

/**
 * Interface for scene setters.
 */
public interface MainSceneSetter {

    /**
     * Set text to Status field.
     * 
     * @param text
     *             text to set
     */
    void setStatus(String text);

    /**
     * Set text to Temperature field.
     * 
     * @param text
     *             text to set
     */
    void setTemperature(String text);
}
