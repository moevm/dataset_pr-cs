from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(X_train, y_train)
    return clf

def predict(clf, X_test):
    res = clf.predict(X_test)
    return res

def estimate(res, y_test):
    accuracy = (res == y_test).mean()
    return round(accuracy, 3)
    
def scale(data, mode='standard'):
    valid_methods = ['standard', 'minmax', 'maxabs']
    if mode not in valid_methods:
        return None

    scaler_map = {
        'standard': StandardScaler(),
        'minmax': MinMaxScaler(),
        'maxabs': MaxAbsScaler()
    }

    scaler = scaler_map[mode]
    scaled_data = scaler.fit_transform(data)

    return scaled_data