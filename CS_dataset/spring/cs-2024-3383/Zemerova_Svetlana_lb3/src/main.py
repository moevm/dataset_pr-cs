from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, :2],  wine.target, test_size=1-train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = "uniform"):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(X_train, y_train)
    return clf

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    correct = (res==y_test).sum() 
    total = len(y_test) 
    return round(correct/total, 3)

def scale(data, mode="standard"):
    if mode == "standard": 
        return StandardScaler().fit_transform(data)
    elif mode == "minmax": 
        return MinMaxScaler().fit_transform(data)
    elif mode == "maxabs": 
        return MaxAbsScaler().fit_transform(data)
    else: return None