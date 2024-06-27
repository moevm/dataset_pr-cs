from sklearn.metrics import accuracy_score
from sklearn import preprocessing
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn import datasets
import numpy as np


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X, y = wine.data[:, :2], wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    neighbors = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    neighbors.fit(X_train, y_train)
    return neighbors


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    met = accuracy_score(y_test, res)
    return np.round(met, 3)


def scale(data, mode='standard'):
    if mode == 'standard':
        return preprocessing.StandardScaler().fit_transform(data)
    elif mode == 'minmax':
        return preprocessing.MinMaxScaler().fit_transform(data)
    elif mode == 'maxabs':
        return preprocessing.MaxAbsScaler().fit_transform(data)
    return None