from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
def load_data(train_size=0.8):
    wine = load_wine()
    return train_test_split(wine.data[:,:2], wine.target, train_size=train_size, test_size=1-train_size, random_state=42)


from sklearn.neighbors import KNeighborsClassifier
def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    return KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(X_train, y_train)


def predict(clf, X_test):
    return clf.predict(X_test)


from sklearn.metrics import accuracy_score
def estimate(res, y_test):
    return round(accuracy_score(res, y_test), 3)


from sklearn import preprocessing
def scale(data, mode='standard'):
    if mode == 'standard':
        sc = preprocessing.StandardScaler().fit_transform(data)
    elif mode == 'minmax':
        sc = preprocessing.MinMaxScaler().fit_transform(data)
    elif mode == 'maxabs':
        sc = preprocessing.MaxAbsScaler().fit_transform(data)
    else:
        sc = None
    return sc