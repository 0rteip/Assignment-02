package carwash.view;

import carwash.controller.Controller;
import carwash.model.message.Message;
import carwash.view.scenemanager.SceneManager;
import carwash.view.settings.WindowSettings;

/**
 * interface View.
 */
public interface View {

    /**
     * Start the view.
     * 
     * @param controller
     *                   controller
     */
    void start(Controller controller);

    /**
     * Display the message notification.
     * 
     * @param message
     *                to display
     */
    void displayMessage(Message message);

    /**
     * Returns the {@link WindowSettings}.
     * 
     * @return
     *         WindowSettings
     */
    WindowSettings getWindowSettings();

    /**
     * Returns the {@link SceneManager}.
     * 
     * @return
     *         SceneManager
     */
    SceneManager getSceneManager();

    /**
     * Quit the application.
     */
    void quit();

    /**
     * Render View.
     */
    void render();
}