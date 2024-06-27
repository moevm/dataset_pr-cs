from sklearn import datasets
from sklearn.model_selection import train_test_split
import pandas as pd
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = datasets.load_wine()
    X = wine.data
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size= 1 - train_size, random_state=42)
    return np.take(X_train, [0, 1], axis=1), np.take(X_test, [0, 1], axis=1), y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(X_train, y_train)
    return clf

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    correct_predictions = (res== y_test).sum() 
    total_predictions = len(y_test) 
    return round(correct_predictions/total_predictions, 3)

def scale(data, mode='standard'):
    if mode == 'standard': scaler = StandardScaler()
    elif mode == 'minmax': scaler = MinMaxScaler()
    elif mode == 'maxabs': scaler = MaxAbsScaler()
    else: return None
    return scaler.fit_transform(data)