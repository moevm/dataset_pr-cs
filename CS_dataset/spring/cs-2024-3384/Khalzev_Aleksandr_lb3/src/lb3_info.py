from sklearn.model_selection import train_test_split
from sklearn.datasets import load_wine
from sklearn.neighbors import KNeighborsClassifier
from sklearn import preprocessing 

def load_data(train_size = 0.8):
    x, y = load_wine(return_X_y = True)
    x = x[:, :2]
    x_train, x_test, y_train, y_test = train_test_split(x, y, train_size=train_size, random_state=42)
    return x_train, x_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(X_train, y_train)
    return model

def predict(clf, X_test):
    y = clf.predict(X_test)
    return y

def estimate(res, y_test):
    sc = accuracy_score(y_test, res)
    return round(sc, 3)

def scale(data, mode='standard'):
    if mode == 'standard':
        sc = preprocessing.StandardScaler()
    elif mode == 'minmax':
        sc = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        sc = preprocessing.MaxAbsScaler()
    else:
        return None
    sc_d = sc.fit_transform(data)
    return sc_d

