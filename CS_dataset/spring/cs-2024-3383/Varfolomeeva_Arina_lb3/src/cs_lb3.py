from sklearn.datasets import load_wine
from sklearn.neighbors import KNeighborsClassifier
def load_data(train_size = 0.8):
    wine = load_wine()
    x = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(x, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    model = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    model.fit(X_train, y_train)
    return model

def predict(clf, X_test):
    predictions = clf.predict(X_test)
    return predictions

def estimate(res, y_test):
    count_right = 0
    for i in range(len(res)):
        if res[i] == y_test[i]:
            count_right += 1
    return round(count_right/len(y_test), 3)

def scale(data, mode = 'standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None
    #scaled_data = scaler.fit_transform(data)
    model = scaler.fit(data)
    scaled_data = model.transform(data)
    return scaled_data