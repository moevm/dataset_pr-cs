from sklearn import datasets, preprocessing
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
import numpy as np

def load_data(train_size=0.8):
    dataset = datasets.load_wine()
    # Extract first two columns
    X_train, X_test, y_train, y_test = train_test_split(dataset.data[:, :2],
                                                        dataset.target,
                                                        random_state=42,
                                                        train_size=train_size)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights="uniform"):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return round(np.equal(res, y_test).sum() / len(res), 3)

def scale(data, mode="standard"):
    if(mode == "standard"): scaler = preprocessing.StandardScaler()
    elif(mode == "minmax"): scaler = preprocessing.MinMaxScaler()
    elif(mode == "maxabs"): scaler = preprocessing.MaxAbsScaler()
    else: return None
    
    return scaler.fit_transform(data)
