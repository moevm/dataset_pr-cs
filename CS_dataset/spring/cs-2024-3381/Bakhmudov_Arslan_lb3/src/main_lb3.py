from sklearn import datasets, model_selection, neighbors, metrics, preprocessing


def load_data(train_size: float = 0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = model_selection.train_test_split(
        wine.data[:,:2], wine.target,
        train_size=train_size, test_size=1-train_size,
        random_state=42
    )
    return X_train, X_test, y_train, y_test


def scale(data, mode: str = 'standard'):
    if mode == 'standard':
        return preprocessing.StandardScaler().fit_transform(data)
    if mode == 'minmax':
        return preprocessing.MinMaxScaler().fit_transform(data)
    if mode == 'maxabs':
        return preprocessing.MaxAbsScaler().fit_transform(data)
    if mode == '':
        return data

def train_model(X_train, y_train, n_neighbors: int = 15, weights: str = 'uniform'):
    model = neighbors.KNeighborsClassifier(
        n_neighbors=n_neighbors, weights=weights
    )
    model.fit(X_train, y_train)
    return model


def predict(clf: neighbors.KNeighborsClassifier, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return round(metrics.accuracy_score(y_test, res), 3)
