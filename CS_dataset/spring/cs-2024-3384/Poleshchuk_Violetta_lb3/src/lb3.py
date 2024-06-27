from sklearn import datasets
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size=0.8):
    wine = load_wine()
    x = wine.data[:, :2]
    y = wine.target
    x_train, x_test, y_train, y_test = train_test_split(x, y, train_size=train_size, random_state=42)
    return x_train, x_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model

def predict(clf, X_test):
    return clf.predict(X_test)
    
def estimate(res, y_test):
    common_elements = sum(1 for result, test in zip(res, y_test) if result == test)
    result = round(common_elements / len(res), 3)
    return result
    
def scale(X, mode='standard'):
    if mode == 'standard':
        return StandardScaler().fit_transform(X)
    elif mode == 'minmax':
        return MinMaxScaler().fit_transform(X)
    elif mode == 'maxabs':
        return MaxAbsScaler().fit_transform(X)
    return None