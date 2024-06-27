from sklearn import datasets, preprocessing
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
import numpy as np


def load_data(train_size = 0.8):
    wine = datasets.load_wine(return_X_y = True)
    x_train, x_test, y_train, y_test = train_test_split(wine[0][:, :2], wine[1], train_size = train_size, random_state=42)
    return x_train, x_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    my_model = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    my_model.fit(X_train, y_train)
    return my_model
    
    
def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return np.round(accuracy_score(res, y_test), 3)
  
    
def scale(data, mode = 'standard'):
    if mode == 'standard':
        scaler = preprocessing.StandardScaler()
    elif mode == 'minmax':
        scaler = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        scaler = preprocessing.MaxAbsScaler()
    else: 
        return None
    return scaler.fit_transform(data)
