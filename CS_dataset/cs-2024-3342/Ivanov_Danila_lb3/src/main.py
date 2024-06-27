from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing

def load_data(train_size=0.8):
    wine = datasets.load_wine()

    X = wine.data[:, :2]
    y = wine.target

    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)

    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    classifier = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)

    classifier.fit(X_train, y_train)

    return classifier

def predict(clf, X_test):
    prediction_data = clf.predict(X_test)
    return prediction_data

def estimate(res, y_test):
    accuracy = accuracy_score(y_test, res)
    return round(accuracy, 3)

def scale(data, mode='standard'):
    if mode == 'standard':
        sc = preprocessing.StandardScaler()
    elif mode == 'minmax':
        sc = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        sc = preprocessing.MaxAbsScaler()
    else:
        return None
    return sc.fit_transform(data)