from sklearn import datasets
from sklearn import model_selection
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X, y = wine.data[:, :2], wine.target
    X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, random_state=42, train_size=train_size)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    neighbors = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    return neighbors.fit(X_train, y_train)


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return round(accuracy_score(y_test, res), 3)


def scale(data, mode='standard'):
    if mode == 'standard':
        return preprocessing.StandardScaler().fit_transform(data)
    if mode == 'minmax':
        return preprocessing.MinMaxScaler().fit_transform(data)
    if mode == 'maxabs':
        return preprocessing.MaxAbsScaler().fit_transform(data)
    return None