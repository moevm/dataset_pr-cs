import numpy as np
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = load_wine()
    X = wine.data[:, :2]
    y = wine.target
    return train_test_split(X, y, train_size=train_size, random_state=42)


def train_model(X_train, y_train, n_neighbors=15, weights="uniform"):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model


def predict(model, X_test):
    return model.predict(X_test)


def estimate(predictions, y_test):
    return round(np.mean(predictions == y_test), 3)


def scale(data, mode="standard"):
    scalers = {
        "standard": StandardScaler,
        "minmax": MinMaxScaler,
        "maxabs": MaxAbsScaler,
    }
    scaler = scalers.get(mode)
    if scaler:
        return scaler().fit_transform(data)
    return None
