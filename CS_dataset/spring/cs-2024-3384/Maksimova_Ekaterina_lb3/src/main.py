from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn import preprocessing

def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X = wine.data[:, :2]
    Y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, Y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    classifier = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    classifier.fit(X_train, y_train)
    return classifier

def predict(classifier, X_test):
    return classifier.predict(X_test)

def estimate(res, y_test):
    return round(accuracy_score(res, y_test), 3)

def scale(data, mode='standard'):
    if mode == 'standard':
        return preprocessing.StandardScaler().fit_transform(data)
    elif mode == 'minmax':
        return preprocessing.MinMaxScaler().fit_transform(data)
    elif mode == 'maxabs':
        return preprocessing.MaxAbsScaler().fit_transform(data)
    else:
        return None
