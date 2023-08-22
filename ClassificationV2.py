import pandas as pd
import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import train_test_split
from tensorflow.keras import layers, optimizers, Input, Model, Sequential
from tensorflow.keras.models import load_model

# Check environment details
print("TensorFlow version:", tf.__version__)
print("Num GPUs Available: ", len(tf.config.list_physical_devices('GPU')))

# Load dataset
def load_data(path):
    """
    Load the dataset and return features and labels.
    """
    df = pd.read_csv(path)
    print(df.head())
    features = df.drop(columns=["label", "class", "time"]).values
    labels = df["class"].values
    return features, labels

# Preprocess the data
def preprocess_data(features, labels):
    """
    Split the data into train and test sets, normalize them, and one-hot encode the labels.
    """
    x_train, x_test, y_train, y_test = train_test_split(features, labels, test_size=0.2, random_state=1)

    # Normalize the data
    mean = x_train.mean(axis=0)
    std = x_train.std(axis=0)
    x_train = (x_train - mean) / std
    x_test = (x_test - mean) / std

    # One-hot encode the labels
    y_train = tf.keras.utils.to_categorical(y_train)
    y_test = tf.keras.utils.to_categorical(y_test)

    return x_train, x_test, y_train, y_test

# Define the model architecture
def build_model():
    """
    Build and return a neural network model.
    """
    model = Sequential([
        layers.Dense(1024, activation='relu', input_shape=(8,)),
        layers.Dense(512, activation='relu'),
        layers.Dense(256, activation='relu'),
        layers.Dense(128, activation='relu'),
        layers.Dense(64, activation='relu'),
        layers.Dense(32, activation='relu'),
        layers.Dense(8, activation='softmax')
    ])
    return model

# Compile and train the model
def compile_and_train(model, x_train, y_train, batch_size=512, epochs=10, model_name="model"):
    """
    Compile, train the model and save it.
    """
    opt = optimizers.Nadam(lr=1e-3)
    model.compile(optimizer=opt, loss="categorical_crossentropy", metrics=["accuracy"])
    
    # Callbacks
    callbacks_list = [
        tf.keras.callbacks.EarlyStopping(monitor='val_accuracy', patience=2),
        tf.keras.callbacks.ModelCheckpoint(filepath=f'{model_name}.h5', monitor='val_loss', save_best_only=True)
    ]
    
    history = model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.2, callbacks=callbacks_list)
    return history

# Plot training and validation loss and accuracy
def plot_history(history):
    """
    Plot training and validation loss and accuracy.
    """
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
    
    # Loss
    ax1.plot(history.history['loss'], label='Training Loss')
    ax1.plot(history.history['val_loss'], label='Validation Loss')
    ax1.set_title('Loss')
    ax1.set_xlabel('Epochs')
    ax1.set_ylabel('Loss')
    ax1.legend()

    # Accuracy
    ax2.plot(history.history['accuracy'], label='Training Accuracy')
    ax2.plot(history.history['val_accuracy'], label='Validation Accuracy')
    ax2.set_title('Accuracy')
    ax2.set_xlabel('Epochs')
    ax2.set_ylabel('Accuracy')
    ax2.legend()

    plt.show()

# Main Execution
if __name__ == "__main__":
    # Load and preprocess data
    data_path = 'C:/Users/hcans/OneDrive/Masaüstü/EMG_data_for_gestures-master/EMG-data.csv'
    features, labels = load_data(data_path)
    x_train, x_test, y_train, y_test = preprocess_data(features, labels)
    
    # Build, compile, train and save the model
    model = build_model()
    history = compile_and_train(model, x_train, y_train, model_name="emg_model")
    
    # Plot results
    plot_history(history)
    
    # Evaluate the model
    evaluation = model.evaluate(x_test, y_test, verbose=2)
    print("\nTest loss:", evaluation[0]*100, "%")
    print("Test accuracy:", evaluation[1]*100, "%")

    # Make a prediction on a specific sample
    sample_idx = 105
    prediction = np.argmax(model.predict(x_test)[sample_idx])
    print("\nPredicted Class:", prediction)
    print("Actual Class:", np.argmax(y_test[sample_idx]))
