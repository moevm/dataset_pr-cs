import sklearn as sl
from sklearn import datasets as ds
from sklearn import model_selection as ms
from sklearn import neighbors as nb
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import MaxAbsScaler


def load_data(train_size=0.8):
    wine = ds.load_wine()
    X, y = wine['data'][:, 0:2], wine['target']
    X_train, X_test, y_train, y_test = ms.train_test_split(X, y, train_size=train_size,
                                                           test_size=0.2, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    neigh = nb.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    return neigh.fit(X_train, y_train)


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return round(sl.metrics.accuracy_score(y_test, res), 3)


def scale(X, mode='standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None
    return scaler.fit_transform(X)
