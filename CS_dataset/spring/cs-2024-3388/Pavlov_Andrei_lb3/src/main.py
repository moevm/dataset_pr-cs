import sklearn
import numpy as np


def load_data(train_size=0.8):
    dataset = sklearn.datasets.load_wine()
    return sklearn.model_selection.train_test_split(dataset.data[:, :2], dataset.target, train_size=train_size, random_state=42)


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    return sklearn.neighbors.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(X_train, y_train)


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return np.round(sklearn.metrics.accuracy_score(y_test, res), 3)


def scale(X, mode='standard'):
    scalers = dict(
        standard=sklearn.preprocessing.StandardScaler().fit_transform(X),
        minmax=sklearn.preprocessing.MinMaxScaler().fit_transform(X),
        maxabs=sklearn.preprocessing.MaxAbsScaler().fit_transform(X)
    )
    return scalers.get(mode, None)
