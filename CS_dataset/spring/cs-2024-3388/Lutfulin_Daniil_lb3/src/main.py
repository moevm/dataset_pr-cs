from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing
import numpy as np


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    k_neighbours_model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(X_train, y_train)
    return k_neighbours_model


def predict(clf, X_test):
    predicted_data = clf.predict(X_test)
    return predicted_data


def estimate(res, y_test):
    accuracy = accuracy_score(y_test, res)
    return accuracy.round(3)


def scale(data, mode='standard'):
    if mode == 'standard':
        scaler = preprocessing.StandardScaler()
    elif mode == 'minmax':
        scaler = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        scaler = preprocessing.MaxAbsScaler()
    else:
        return None
    return scaler.fit_transform(data)
    
