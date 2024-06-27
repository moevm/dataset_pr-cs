from sklearn import datasets
from sklearn import neighbors
from sklearn import preprocessing
from sklearn import metrics
from sklearn.model_selection import train_test_split

def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X, y = wine.data[:, 0:2], wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = neighbors.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    return model.fit(X_train, y_train)


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return round(metrics.accuracy_score(res, y_test), 3)


def scale(data, mode='standard'):
    if (mode == 'standard'):
        scaler = preprocessing.StandardScaler()
    elif (mode == 'minmax'):
        scaler = preprocessing.MinMaxScaler()
    elif (mode == 'maxabs'):
        scaler = preprocessing.MaxAbsScaler()
    else:
        return None
    return scaler.fit_transform(data)