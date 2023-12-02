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

    /**
     * Set text to Cars washed field.
     * 
     * @param string
     *               text to set
     */
    void setCarsWashed(String string);
}
