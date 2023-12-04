package carwash.view.scenecontroller;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
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
    private TextField carsWashedField;

    @FXML
    private Button fixButton;

    @FXML
    public void fixTemperature() {
        this.getView().fixMessage();
        this.fixButton.setVisible(false);
    }

    @Override
    public void initializeScene() {
        this.fixButton.setVisible(false);
    }

    @Override
    public void setStatus(String text) {
        this.stateField.setText(text);
        if (text.equals("Maintenance")) {
            this.fixButton.setVisible(true);
        }
    }

    @Override
    public void setTemperature(String text) {
        this.tempField.setText(text);
    }

    @Override
    public void setCarsWashed(String string) {
        this.carsWashedField.setText(string);
    }
}