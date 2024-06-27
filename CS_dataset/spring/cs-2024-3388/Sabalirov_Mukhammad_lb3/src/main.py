import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.datasets import load_wine
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = load_wine()
    X = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    return clf.fit(X_train, y_train)


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return np.round(accuracy_score(y_test, res), 3)


def scale(X_test, mode='standard'):
    answers_dict = {
        'standard': lambda X: StandardScaler().fit_transform(X),
        'minmax': lambda X: MinMaxScaler().fit_transform(X),
        'maxabs': lambda X: MaxAbsScaler().fit_transform(X)
    }
    return answers_dict.get(mode, lambda X: None)(X_test)
