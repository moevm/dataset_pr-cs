import sklearn as sk
import pandas as pd
import numpy as np


def load_data(train_size = 0.8):
    wine = sk.datasets.load_wine()
    X = wine.data[:, :2]
    Y = wine.target
    return sk.model_selection.train_test_split(X, Y, train_size = train_size, random_state = 42)


def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    model = sk.neighbors.KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    model.fit(X_train, y_train)
    return model


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return np.round(sk.metrics.accuracy_score(y_test, res), 3)


def scale(test, mode = 'standard'):
  switch = {
      'standard' : sk.preprocessing.StandardScaler().fit_transform(test),
      'minmax' : sk.preprocessing.MinMaxScaler().fit_transform(test),
      'maxabs' : sk.preprocessing.MaxAbsScaler().fit_transform(test)
  }
  return switch.get(mode, None)