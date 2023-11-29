package carwash.view.scenecontroller;

import java.beans.PropertyChangeSupport;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javafx.fxml.FXML;
// import globaloutbreak.gamespeed.GameSpeedObserver;
import javafx.scene.control.Button;

/**
 * Scene for settings.
 */
public final class MainMenuController extends AbstractSceneController {

    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @FXML
    private Button saveButton;

    @FXML
    private Button cancelButton;

    // could be used to notify for pressed button
    private final PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    @FXML
    public void fixTemperature() {
        logger.info("fixTemperature pressed");
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