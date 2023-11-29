package carwash.model;

import java.beans.PropertyChangeListener;

/**
 * Model for GlobalOutbreak app.
 */
public interface Model {

    /**
     * Add a listener for the News.
     * 
     * @param listener
     *                 listener
     */
    void addListener(PropertyChangeListener listener);
}