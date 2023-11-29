package carwash.view;

import carwash.controller.Controller;
import carwash.model.message.Message;
import carwash.model.valuetype.ValueType;
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
     * Update value.
     * 
     * @param valueType
     *                  value type
     * @param newValue
     *                  new value
     */
    void updateValue(ValueType valueType, String newValue);

    /**
     * Send fixed message.
     */
    void fixMessage();
}