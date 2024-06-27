from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import MinMaxScaler, StandardScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, :2], wine.target, random_state=42, train_size=train_size)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    classification = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights, metric="minkowski")
    classification.fit(X_train, y_train)

    return classification

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return round(accuracy_score(res, y_test), 3)

def scale(data, mode = 'standard'):
    if mode == "standard":
        return StandardScaler().fit_transform(data)
    elif mode == "maxabs":
        return MaxAbsScaler().fit_transform(data)
    elif mode == "minmax":
        return MinMaxScaler().fit_transform(data)
    else:
        return None