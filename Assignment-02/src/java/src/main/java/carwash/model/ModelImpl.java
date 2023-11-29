package carwash.model;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

import carwash.model.message.MessageType;

public class ModelImpl implements Model {

    final PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    public ModelImpl() {
        pcs.firePropertyChange(MessageType.WARNING.getTitle(), "message", "msg");
    }

    @Override
    public void addListener(final PropertyChangeListener listener) {
        this.pcs.addPropertyChangeListener(listener);
    }

}
