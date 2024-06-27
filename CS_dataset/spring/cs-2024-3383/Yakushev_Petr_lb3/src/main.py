
from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier

def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, :2], wine.target, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model

def predict(clf, X_test):
    res = clf.predict(X_test)
    return res

def estimate(res, y_test):
    correct = 0
    for pred, true in zip(res, y_test):
        if pred == true:
            correct += 1
    accuracy = correct / len(res)
    return round(accuracy, 3)

def scale(data, mode='standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None

    return scaler.fit_transform(data)
