import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_wine
import sklearn.preprocessing as scalers
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

def load_data(train_size = 0.8):
    wine = load_wine(as_frame=True)
    target = wine.target
    wine = wine.data.iloc[:, [0,1]]
    X_train, X_test, y_train, y_test = train_test_split(wine, target, test_size = 1 - train_size, random_state = 42)
    X_train = X_train.to_numpy()
    X_test = X_test.to_numpy()
    y_test = y_test.to_numpy()
    y_train = y_train.to_numpy()
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    X_train = pd.DataFrame(X_train)
    knn = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    knn.fit(X_train, y_train)
    return knn 

def predict(knn, X_test):
    X_test = pd.DataFrame(X_test)
    y_pred = knn.predict(X_test)
    return y_pred

def estimate(y_pred, y_test):
    y_test = pd.DataFrame(y_test)
    return round(accuracy_score(y_test, y_pred),3)

def scale(df, mode='standard'):
    if mode not in [ 'standard', 'minmax', 'maxabs']:
        return None
    if mode == 'standard':
        scaler = scalers.StandardScaler()
    elif mode == 'minmax':
        scaler = scalers.MinMaxScaler()
    else:
        scaler = scalers.MaxAbsScaler()
    scaler.fit(df)
    df = scaler.transform(df)
    return df
