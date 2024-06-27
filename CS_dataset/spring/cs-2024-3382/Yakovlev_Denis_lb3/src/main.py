from sklearn import datasets
import sklearn as sk

def load_data(train_size = 0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = sk.model_selection.train_test_split(wine.data[:, :2], wine.target, random_state=42, train_size=train_size)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    classificator = sk.neighbors.KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights, metric="minkowski")
    classificator.fit(X_train, y_train)
    return classificator

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return round(sk.metrics.accuracy_score(res, y_test), 3)
    
def scale(data, mode = 'standard'):
    if mode == "standard":
        scaler = sk.preprocessing.StandardScaler()
        return scaler.fit_transform(data)
    elif mode == "maxabs":
        scaler = sk.preprocessing.MaxAbsScaler()
        return scaler.fit_transform(data)
    elif mode == "minmax":
        scaler = sk.preprocessing.MinMaxScaler()
        return scaler.fit_transform(data)
    else:
        return None