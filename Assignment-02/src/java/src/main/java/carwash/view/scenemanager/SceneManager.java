package carwash.view.scenemanager;

import java.util.concurrent.CountDownLatch;

import carwash.model.message.Message;
import carwash.model.valuetype.ValueType;

/**
 * Interface that manage the javaFX scenes.
 */
public interface SceneManager {

    /**
     * Open menu Scene.
     */
    void openInitialMenu();

    /**
     * Open a Message.
     * 
     * @param message
     *                message
     * @param latch
     *                CountDownLatch
     */
    void openMessage(Message message, CountDownLatch latch);

    /**
     * Update value.
     * 
     * @param valueType
     *                  value type
     * @param newValue
     *                  new value
     */
    void updateValue(ValueType valueType, String newValue);
}