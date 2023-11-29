package carwash.view.utilities;

/**
 * All the scenes of the application.
 */
public enum SceneStyle {

    /**
     * Main menu.
     */
    INITIALMENU("Initial Menu", "layouts/carWash.fxml");

    private final String title;
    private final String fxmlFile;

    SceneStyle(final String title, final String fxmlFile) {
        this.title = title;
        this.fxmlFile = fxmlFile;
    }

    /**
     * @return the fxml file of the scene
     */
    public String getFxmlFile() {
        return this.fxmlFile;
    }

    /**
     * @return the fxml path of the scene
     */
    public String getTitle() {
        return this.title;
    }
}