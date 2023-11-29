package carwash.view.scenemanager;

import java.util.concurrent.CountDownLatch;

import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;
import carwash.model.message.Message;
import carwash.model.valuetype.ValueType;
import carwash.view.utilities.SceneStyle;
import carwash.view.View;
import carwash.view.sceneloader.SceneLoader;
import carwash.view.sceneloader.SceneLoaderImpl;
import javafx.stage.Stage;

/**
 * Class that manage the scene changing.
 */
public final class SceneManagerImpl implements SceneManager {

    private final SceneLoader sceneLoader;
    private final Stage stage;

    /**
     * Constructor that load menu scenes.
     * 
     * @param stage
     * @param view
     * 
     */
    // @formatter:off
    @SuppressFBWarnings(
        value = "EI_EXPOSE_REP2",
        justification = "We need to use the correct instance of The Stage the open the Scene in the correct way"
    )
    // @formatter:on
    public SceneManagerImpl(final Stage stage, final View view) {
        this.stage = stage;
        this.sceneLoader = new SceneLoaderImpl(view);
    }

    @Override
    public void openInitialMenu() {
        this.openScene(SceneStyle.INITIALMENU);
    }

    private void openScene(final SceneStyle sceneStyle) {
        this.sceneLoader.loadScene(sceneStyle, this.stage);
    }

    @Override
    public void openMessage(final Message message, final CountDownLatch latch) {
        this.sceneLoader.openDialog(this.stage, message, latch);
    }

    @Override
    public void updateValue(final ValueType valueType, final String newValue) {
        this.sceneLoader.updateValue(valueType, newValue);
    }
}