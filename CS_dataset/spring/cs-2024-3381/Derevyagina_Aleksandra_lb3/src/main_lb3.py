from sklearn import datasets
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = datasets.load_wine(return_X_y = True)
    X_train, X_test, y_train, y_test = train_test_split(wine[0][:, :2], wine[1], train_size = train_size, random_state = 42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    instance = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    instance.fit(X_train, y_train)
    return instance

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    accuracy_predictions = sum(res == y_test)
    return round(accuracy_predictions / len(y_test), 3)

def scale(data, mode = 'standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None
    return scaler.fit_transform(data)
