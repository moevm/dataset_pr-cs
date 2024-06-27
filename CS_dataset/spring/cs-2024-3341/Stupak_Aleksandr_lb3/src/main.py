from sklearn import datasets, neighbors, model_selection, metrics, preprocessing

def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = model_selection.train_test_split(wine.data, wine.target, train_size=train_size, random_state=42)
    return X_train[:, :2], X_test[:, :2], y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    n = neighbors.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    n.fit(X_train, y_train)
    return n

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    accuracy = metrics.accuracy_score(y_test, res)
    return round(accuracy, 3)

def scale(data, mode='standard'):
    if mode == 'standard':
        return preprocessing.StandardScaler().fit_transform(data)
    if mode == 'minmax':
        return preprocessing.MinMaxScaler().fit_transform(data)
    if mode == 'maxabs':
        return preprocessing.MaxAbsScaler().fit_transform(data)
    else:
        return None