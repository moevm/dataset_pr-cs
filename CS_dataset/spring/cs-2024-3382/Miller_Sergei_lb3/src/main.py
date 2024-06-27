from sklearn import datasets
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn import preprocessing


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, :2],
                                    wine.target, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

  
def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(X_train, y_train)
    return clf


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    accuracy = np.sum(res == y_test)/len(y_test)
    return round(accuracy, 3)


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
