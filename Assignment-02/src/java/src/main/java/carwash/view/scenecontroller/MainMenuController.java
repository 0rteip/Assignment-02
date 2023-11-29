package carwash.view.scenecontroller;

import java.beans.PropertyChangeSupport;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;

/**
 * Scene for settings.
 */
public final class MainMenuController extends AbstractSceneController implements MainSceneSetter {

    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @FXML
    private TextField stateField;

    @FXML
    private TextField temperatureField;

    // could be used to notify for pressed button
    private final PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    @FXML
    public void fixTemperature() {
        logger.info("fixTemperature pressed");
    }

    @Override
    public void setStatus(String text) {
        this.stateField.setText(text);
    }

    @Override
    public void setTemperature(String text) {
        this.temperatureField.setText(text);
    }

    // /**
    // * Save settings before closing.
    // */
    // @FXML
    // public void saveSettings() {
    // this.pcs.firePropertyChange("gameSpeed",
    // this.getView().getGameSettings().getGameSpeed(),
    // this.gameSpeedComboBox.getSelectionModel().getSelectedItem());
    // this.exitSettings();
    // }
}