from sklearn import datasets
from sklearn import model_selection
from sklearn import neighbors
from sklearn import metrics
from sklearn import preprocessing


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = model_selection.train_test_split(wine.data[:, :2], wine.target, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    classifier = neighbors.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(X_train, y_train)
    return classifier


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return round(metrics.accuracy_score(y_test, res), 3)


def scale(data, mode='standard'):
    if mode == 'standard':
        return preprocessing.StandardScaler().fit_transform(data)
    elif mode == 'minmax':
        return preprocessing.MinMaxScaler().fit_transform(data)
    elif mode == 'maxabs':
        return preprocessing.MaxAbsScaler().fit_transform(data)
    else:
        return None
