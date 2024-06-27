from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_wine
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import scale
from sklearn.metrics import accuracy_score

def scale(data, mode='standard'):
    if mode == 'minmax':
        scaler = MinMaxScaler()
        return scaler.fit_transform(data)
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
        return scaler.fit_transform(data)
    elif mode == 'standard':
        scaler = StandardScaler()
        return scaler.fit_transform(data)
    else:
        return None
def load_data(train_size=0.8):
    wine = datasets.load_wine()
    data = wine.data
    target = wine.target
    x_train, x_test, y_train, y_test = train_test_split(data[:, [0, 1]], target, train_size=train_size, random_state = 42)
    return x_train, x_test, y_train, y_test
def train_model(X_train, y_train, n_neighbors2=15, weights2='uniform'):
    neigh = KNeighborsClassifier(n_neighbors=n_neighbors2, weights=weights2) 
    neigh.fit(X_train, y_train)
    return neigh

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
     return round(accuracy_score(y_test, res), 3)