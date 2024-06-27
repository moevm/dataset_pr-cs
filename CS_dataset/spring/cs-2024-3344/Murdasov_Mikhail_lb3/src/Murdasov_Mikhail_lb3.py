from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = load_wine()
    x = wine.data
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(x[:, [0,1]], y, train_size = train_size, random_state = 42)

    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = "uniform"):
    classifier = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    classifier.fit(X_train, y_train)

    return classifier

def predict(classifier, X_test):
    pred = classifier.predict(X_test)

    return pred

def estimate(res, y_test):
    return round(accuracy_score(y_true = y_test, y_pred = res), 3)

def scale(data , mode = "standard"):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else: 
        return None

    return scaler.fit_transform(data)