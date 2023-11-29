package carwash.view.sceneloader;

import java.beans.PropertyChangeSupport;
import java.io.IOException;
import java.util.EnumMap;
import java.util.concurrent.CountDownLatch;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import carwash.model.message.Message;
import carwash.model.valuetype.ValueType;
import carwash.view.View;
import carwash.view.message.MessageDialog;
import carwash.view.scenecontroller.MainSceneSetter;
import carwash.view.scenecontroller.SceneController;
import carwash.view.scenecontroller.observer.CarWashObserver;
import carwash.view.utilities.SceneStyle;
import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;
import javafx.scene.layout.Region;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * Implementation of {@link SceneLoader}.
 */
public final class SceneLoaderImpl implements SceneLoader {

    private static final String UPDATE_OBS = "update";

    private final PropertyChangeSupport pcs = new PropertyChangeSupport(this);
    private final Logger logger = LoggerFactory.getLogger(this.getClass());
    private final View view;
    private final EnumMap<SceneStyle, Scene> sceneLoaded = new EnumMap<>(SceneStyle.class);

    /**
     * Create a SceneLoader with an associated view.
     * 
     * @param view
     *             view
     */
    // @formatter:off
    @SuppressFBWarnings(
        value = "EI_EXPOSE_REP2",
        justification = "We need to use the correct instance of the View to let the SceneController to access to the View"
    )
    // @formatter:on
    public SceneLoaderImpl(final View view) {
        this.view = view;
    }

    @Override
    public void loadScene(final SceneStyle sceneStyle, final Stage stage) {
        FXMLLoader loader;
        try {
            final Region root;
            final Scene scene;

            // If the scene is already in cache, set the cached scene.
            if (this.sceneLoaded.containsKey(sceneStyle)) {
                scene = this.sceneLoaded.get(sceneStyle);
                loader = (FXMLLoader) scene.getUserData();
            } else {
                // If the scene isn't in the cache, then create a new one, with the current
                // root.
                loader = new FXMLLoader();
                loader.setLocation(ClassLoader.getSystemResource(sceneStyle.getFxmlFile()));
                root = loader.load();
                scene = new Scene(root, this.view.getWindowSettings().getDefWindowWidth(),
                        this.view.getWindowSettings().getDefWindowHeight());
                scene.setUserData(loader);
                this.sceneLoaded.put(sceneStyle, scene);
            }

            // Set the current size in settings.
            stage.widthProperty()
                    .addListener((obs, oldVal, newVal) -> this.view.getWindowSettings().setWidth(newVal.intValue()));
            stage.heightProperty()
                    .addListener((obs, oldVal, newVal) -> this.view.getWindowSettings().setHeight(newVal.intValue()));

            stage.setTitle(sceneStyle.getTitle());
            stage.setResizable(true);
            stage.setScene(scene);
            stage.setMinWidth(this.view.getWindowSettings().getDefWindowWidth());
            stage.setMinHeight(this.view.getWindowSettings().getDefWindowHeight());
            stage.setHeight(this.view.getWindowSettings().getDefWindowHeight());
            stage.setWidth(this.view.getWindowSettings().getDefWindowWidth());

            final SceneController controller = (SceneController) loader.getController();
            this.initializeScene(controller, sceneStyle);

            if (!stage.isShowing()) {
                stage.show();
            }
        } catch (IOException e) {
            logger.warn("Error while loading {}", sceneStyle.getFxmlFile(), e);
        }
    }

    private void initializeScene(final SceneController controller, final SceneStyle sceneStyle) {
        controller.setSceneManager(this.view.getSceneManager());
        controller.setView(this.view);
        switch (sceneStyle) {
            case INITIALMENU:
                if (!this.pcs.hasListeners(UPDATE_OBS)) {
                    final MainSceneSetter sceneSetter = (MainSceneSetter) controller;
                    this.pcs.addPropertyChangeListener(UPDATE_OBS, new CarWashObserver(sceneSetter));
                }
                break;
            default:
                break;
        }
    }

    @Override
    public void openDialog(final Stage stage, final Message message, final CountDownLatch latch) {
        MessageDialog.showMessageDialog(stage, message, latch);
    }

    @Override
    public void updateValue(final ValueType valueType, final String newValue) {
        logger.info("Update value {} with {}", valueType.getValue(), newValue);
        this.pcs.firePropertyChange(UPDATE_OBS, valueType.getValue(), newValue);
    }
}