from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import MaxAbsScaler, MinMaxScaler, StandardScaler
import numpy as np


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    x = wine.data[:, [0, 1]]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(x, y, train_size=train_size, random_state=42)

    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    classifier = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    classifier.fit(X_train, y_train)

    return classifier


def predict(clf, X_test):
    prd = clf.predict(X_test)
    return prd


def estimate(res, y_test):
    correct = np.sum(res == y_test)
    total = len(y_test)

    return round(correct / total, 3)


def scale(args, mode='standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None
    scaled = scaler.fit_transform(args)

    return scaled
