from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing

def load_data(train_size = 0.8):
    wine = datasets.load_wine(return_X_y = True)
    X_train, X_test, y_train, y_test = train_test_split(wine[0][:, :2], wine[1], train_size = train_size, random_state = 42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    model = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights).fit(X_train, y_train)
    return model

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return round(accuracy_score(res, y_test), 3)

def scale(data, mode = 'standard'):
    if (mode == 'standard'): return preprocessing.StandardScaler().fit_transform(data)
    elif (mode == 'minmax'): return preprocessing.MinMaxScaler().fit_transform(data)
    elif (mode == 'maxabs'): return preprocessing.MaxAbsScaler().fit_transform(data)
    else: return None