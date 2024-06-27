from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler, StandardScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=1 - train_size, random_state=42)
    return X_train, X_test, y_train, y_test


def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    return KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(X_train, y_train)



def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(res, y_test):
    return round(((res == y_test).sum() / len(y_test)), 3)


def scale(data, mode='standard'):
    if mode == "standard":
        scaler = StandardScaler()
    elif mode == "maxabs":
        scaler = MaxAbsScaler()
    elif mode == "minmax":
        scaler = MinMaxScaler()
    else:
        return None

    scaled_data = scaler.fit_transform(data)
    return scaled_data
