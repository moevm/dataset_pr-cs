from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing
import numpy as np
import pandas as pd

def load_data(train_size=0.8):
    data = datasets.load_wine()
    X = data.data[:,[0,1]]
    y = data.target

    X_train, X_test, y_train, y_test = train_test_split(X,y,train_size=train_size, random_state=42)
    return X_train, X_test,y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    knn = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    knn.fit(X_train,y_train)
    return knn

def predict(clf, X_test):
    knn_predict = clf.predict(X_test)
    return knn_predict

def estimate(res, y_test):
    accuracy = round(accuracy_score(y_test, res),3)
    return accuracy
    
def scale(data, mode='standard'):
    if(mode=='standard'):
        scaler = preprocessing.StandardScaler()
    elif(mode=='minmax'):
        scaler = preprocessing.MinMaxScaler()
    elif(mode=='maxabs'):
        scaler = preprocessing.MaxAbsScaler()
    else:
        return None
    scaled_data = scaler.fit_transform(data)
    return scaled_data
