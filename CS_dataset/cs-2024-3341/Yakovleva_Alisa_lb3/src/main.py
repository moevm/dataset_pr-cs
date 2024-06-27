from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:,0:2], wine.target, train_size = train_size, random_state = 42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    return KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights).fit(X_train, y_train)

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(y_pred, y_test):
    return round(accuracy_score(y_test, y_pred), 3)

def scale(data, mode = 'standard'):
    if (mode == 'standard'):
        scaler = StandardScaler()
    elif (mode == 'minmax'):
        scaler = MinMaxScaler()
    elif (mode == 'maxabs'):
        scaler = MaxAbsScaler()
    else:
        return None
    return scaler.fit_transform(data)
