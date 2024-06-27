from sklearn.metrics import accuracy_score
from sklearn import preprocessing
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn import datasets
import numpy as np

def load_data(train_size = 0.8):
    wine = datasets.load_wine()
    data = wine.data[:,[0,1]]
    target = wine.target
    x_train, x_test, y_train, y_test = train_test_split(data, target, train_size = train_size, random_state = 42)
    return x_train, x_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    neigh = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    neigh.fit(X_train, y_train)
    return neigh

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    met = accuracy_score(y_test, res)
    return np.round(met, 3)
def scale(data, mode = 'standard'):
    OK = ['standard', 'minmax', 'maxabs']
    if mode not in OK:
        return None
    if mode == OK[0]:
        data_scaled = preprocessing.StandardScaler().fit_transform(data)
    elif mode == OK[1]:
        data_scaled = preprocessing.MinMaxScaler().fit_transform(data)
    else:
        data_scaled = preprocessing.MaxAbsScaler().fit_transform(data)
    return data_scaled