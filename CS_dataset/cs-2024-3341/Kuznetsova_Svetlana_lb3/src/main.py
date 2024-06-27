from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

def load_data(train_size = 0.8):
    wine = load_wine()
    
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:,:2], wine.target, train_size = train_size, random_state = 42)
    
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    neighbors = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    neighbors.fit(X_train, y_train)
    
    return neighbors

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    accur = accuracy_score(y_test, res)
    accur = round(accur, 3)
    
    return accur

def scale(data, mode = 'standard'):
    if (mode == 'standard'):
        scaler = StandardScaler()
        return scaler.fit_transform(data)
    elif (mode == 'minmax'):
        scaler = MinMaxScaler()
        return scaler.fit_transform(data)
    elif (mode == 'maxabs'):
        scaler = MaxAbsScaler()
        return scaler.fit_transform(data)
    else:
        return None
