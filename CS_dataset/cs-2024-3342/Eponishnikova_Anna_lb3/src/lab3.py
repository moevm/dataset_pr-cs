from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing


def load_data(train_size = 0.8):
    wine = datasets.load_wine()

    y = wine.target
    x = wine.data[:,:2]

    X_train, X_test, y_train, y_test = train_test_split(x, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights='uniform'):
    return KNeighborsClassifier(n_neighbors = n_neighbors, weights=weights).fit(X_train, y_train)

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return round(accuracy_score(y_test, res),3)

def scale(data, mode = 'standard'):
    if mode == "standard":
        transformer = preprocessing.StandardScaler()
    elif mode == 'minmax':
        transformer = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
       transformer = preprocessing.MaxAbsScaler()
    else:
        return None

    return transformer.fit_transform(data)