package carwash.view.scenecontroller;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;

/**
 * Scene for settings.
 */
public final class MainMenuController extends AbstractSceneController implements MainSceneSetter {

    @FXML
    private TextField stateField;

    @FXML
    private TextField tempField;

    @FXML
    public void fixTemperature() {
        this.getView().fixMessage();
    }

    @Override
    public void setStatus(String text) {
        this.stateField.setText(text);
    }

    @Override
    public void setTemperature(String text) {
        this.tempField.setText(text);
    }
}