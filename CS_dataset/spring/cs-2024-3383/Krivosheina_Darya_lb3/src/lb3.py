from sklearn.datasets import load_wine
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split  
from sklearn.neighbors import KNeighborsClassifier
from sklearn import preprocessing
import numpy as np

def load_data(train_size=0.8):
    wine = load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, [0, 1]], wine.target, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test
    
def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    classifier = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    classifier.fit(X_train, y_train)
    return classifier

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return np.round(accuracy_score(y_test, res), 3)

def scale(X, mode='standard'):
    if mode == 'standard':
        scaler = preprocessing.StandardScaler()
    elif mode == 'minmax':
        scaler = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        scaler = preprocessing.MaxAbsScaler()
    else:
        return None
    X_scaled = scaler.fit_transform(X)
    return X_scaled
        
