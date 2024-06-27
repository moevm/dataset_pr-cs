from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn import preprocessing
from sklearn.metrics import accuracy_score


def load_data(split_ratio=0.8):
    data_wine = load_wine()
    x = data_wine.data[:, :2]
    y = data_wine.target

    x_train, x_test, y_train, y_test = train_test_split(
        x, y, train_size=split_ratio, random_state=42
    )

    return x_train, x_test, y_train, y_test


def train_model(x_train, y_train, neighbors=15, weights='uniform'):
    knn_model = KNeighborsClassifier(n_neighbors=neighbors, weights=weights)
    knn_model.fit(x_train, y_train)

    return knn_model


def predict(clf, x_test):
    PredictData = clf.predict(x_test)

    return PredictData


def estimate(res, y_test):
    return round(accuracy_score(y_test, res), 3)


def scale(data, mode='standard'):
    if mode == 'standard':
        Scaler = preprocessing.StandardScaler()
    elif mode == 'minmax':
        Scaler = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
        Scaler = preprocessing.MaxAbsScaler()
    else:
        return None

    return Scaler.fit_transform(data)
