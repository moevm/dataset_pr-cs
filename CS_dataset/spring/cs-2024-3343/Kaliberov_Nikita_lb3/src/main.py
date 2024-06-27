from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42, train_size=train_size)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model

def predict(classifier, X_test):
    return classifier.predict(X_test)

def estimate(y_pred, y_test):
    accuracy = accuracy_score(y_test, y_pred)
    return round(accuracy, 3)

def scale(data, mode='standard'):
    scaler = {
        'standard': StandardScaler(),
        'minmax': MinMaxScaler(),
        'maxabs': MaxAbsScaler()
    }
    r_scaler = scaler.get(mode)
    if r_scaler:
        return r_scaler.fit_transform(data)
    else:
        return None