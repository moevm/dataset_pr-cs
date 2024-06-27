from sklearn import datasets
import sklearn.preprocessing


def load_data(train_size=0.8):
    model = datasets.load_wine()
    data = model.data[:, 0:2]
    X_train, X_test, y_train, y_test = sklearn.model_selection.train_test_split(data, model.target, train_size=train_size, test_size=1-train_size,  random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    clf = sklearn.neighbors.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(X_train, y_train)
    return clf

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return round(sklearn.metrics.accuracy_score(y_test, res), 3)

def scale(data, mode='standard'):
    if (mode == 'minmax'):
        return MinMaxScaler().fit_transform(data)
    elif (mode == 'maxabs'):
        return MaxAbsScaler().fit_transform(data)
    elif (mode == 'standard'):
        return StandardScaler().fit_transform(data)
    return None
