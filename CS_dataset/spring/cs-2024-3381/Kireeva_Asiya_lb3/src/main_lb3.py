import sklearn

def load_data(train_size=0.8):
    wine = sklearn.datasets.load_wine()
    X = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = sklearn.model_selection.train_test_split(X, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = sklearn.neighbors.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model

def predict(model, X_test):
    y_pred = model.predict(X_test)
    return y_pred

def estimate(y_pred, y_test):
    accuracy = (y_pred == y_test).mean()
    return round(accuracy, 3)

def scale(data, mode='standard'):
    if mode == 'standard':
        scaler = sklearn.preprocessing.StandardScaler()
    elif mode == 'minmax':
        scaler = sklearn.preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        scaler = sklearn.preprocessing.MaxAbsScaler()
    else:
        return None
    scaled_data = scaler.fit_transform(data)
    return scaled_data