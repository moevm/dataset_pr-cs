import sklearn as sk


def load_data(train_size = 0.8):
    wine = sk.datasets.load_wine()
    data = wine.data[:, :2]
    target = wine.target
    X_train, X_test, y_train, y_test = sk.model_selection.train_test_split(data, target, train_size  = train_size, random_state = 42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    classifier = sk.neighbors.KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    classifier.fit(X_train, y_train)
    return classifier


def predict(clf, X_test):
    predictions = clf.predict(X_test)
    return predictions


def estimate(res, y_test):
    accuracy = accuracy_score(y_test, res)
    return round(accuracy, 3)


def scale(data, mode='standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None
    scaled_data = scaler.fit_transform(data)
    return scaled_data
