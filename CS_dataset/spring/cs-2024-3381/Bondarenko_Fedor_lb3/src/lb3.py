from sklearn import datasets
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import MinMaxScaler, StandardScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, :2], wine.target, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(X_train, y_train)
    return model


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return round(sum(map(lambda x, y: x == y, res, y_test)) / len(y_test), 3)


def scale(data, mode='standard'):
    if mode == 'standard':
        scaler = StandardScaler().fit(data)
    elif mode == 'minmax':
        scaler = MinMaxScaler().fit(data)
    elif mode == 'maxabs':
        scaler = MaxAbsScaler().fit(data)
    else:
        return None
    return scaler.transform(data)
