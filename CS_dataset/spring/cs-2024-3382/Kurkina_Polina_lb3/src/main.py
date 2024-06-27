from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn import preprocessing

def load_data(train_size = 0.8):
    Wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(Wine.data[:, :2], Wine.target, train_size = train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    classifier = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    classifier.fit(X_train, y_train)
    return classifier

def predict(classifier, X_test):
    predicted_data = classifier.predict(X_test)
    return predicted_data

def estimate(predicted_data, y_test):
    return round( (sum(predicted_data == y_test) / len(y_test)), 3)

def scale(data, mode = 'standard'):
    if mode == 'standard':
        sc = preprocessing.StandardScaler()
    elif mode == 'minmax':
        sc = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        sc = preprocessing.MaxAbsScaler()
    else:
        return None
    
    sc_data = sc.fit_transform(data)
    return sc_data