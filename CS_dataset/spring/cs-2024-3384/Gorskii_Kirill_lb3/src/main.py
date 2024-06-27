from sklearn import datasets
from sklearn import model_selection
from sklearn import preprocessing
from sklearn.neighbors import KNeighborsClassifier

def load_data(train_size = 0.8):
    dataset = datasets.load_wine()
    X = dataset.data[:, :2]
    Y = dataset.target
    X_train, X_test, Y_train, Y_test = model_selection.train_test_split(X, Y, train_size = train_size, random_state = 42)
    return X_train, X_test, Y_train, Y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    n_correct = sum(res == y_test)
    n_total = len(y_test)
    return round(n_correct / n_total, 3)
  
def scale(data, mode='standard'):
    if mode == 'standard':
        scaler = preprocessing.StandardScaler()
    elif mode == 'minmax':
        scaler = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None

    return scaler.fit_transform(data)
