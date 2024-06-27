from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine['data'], wine['target'], train_size=train_size, random_state=42)
    return X_train[:, :2], X_test[:, :2], y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    knn = KNeighborsClassifier(n_neighbors=n_neighbors,weights=weights)
    knn.fit(X_train, y_train)
    return knn

def predict(clf, X_test):
    y_pred = clf.predict(X_test)
    return y_pred

def estimate(res, y_test):
    accuracy = accuracy_score(y_test, res)
    return round(accuracy,3)
def get_scaler(mode='standard'):
    if mode == 'standard':
        return StandardScaler()
    elif mode == 'minmax':
        return MinMaxScaler()
    elif mode == 'maxabs':
        return MaxAbsScaler()
    return None
def scale(val, mode = 'standard'):
    scaler = get_scaler(mode)
    if scaler == None:
        return None
    scaler.fit(val)
    return scaler.transform(val)
        