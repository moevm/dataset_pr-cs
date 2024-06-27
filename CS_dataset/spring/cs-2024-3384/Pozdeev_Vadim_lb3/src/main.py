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
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights='uniform')
    model.fit(X_train, y_train)
    return model

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    accuracy = round(accuracy_score(res, y_test), 3)
    return accuracy

def scale(data, mode = 'standard'):
    if mode == 'standard':
        scaler = preprocessing.StandardScaler()
    elif mode == 'maxabs':
        scaler = preprocessing.MaxAbsScaler()
    elif mode == 'minmax':
        scaler = preprocessing.MinMaxScaler()
    else:
        return None
    res_data = scaler.fit_transform(data)
    return res_data
