from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = datasets.load_wine();
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, :2], wine.target, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test
    pass

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model = model.fit(X_train, y_train)
    return model
    pass

def predict(clf, X_test):
    return clf.predict(X_test)
    pass

def estimate(res, y_test):
    return float('{:.3f}'.format(accuracy_score(res, y_test)))
    pass

def scale(X, mode='standard'):
    if mode not in ['standard', 'minmax', 'maxabs']:
        return None
    elif (mode == 'standard'):
        model = StandardScaler()
    if mode == 'minmax':
        model = MinMaxScaler()
    elif mode == 'maxabs':
        model = MaxAbsScaler()
    model = model.fit_transform(X)
    return model
