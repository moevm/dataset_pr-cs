from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    x_train, x_test, y_train, y_test \
        = train_test_split(wine.data[:, :2], wine.target,  train_size=train_size, random_state=42)
    return x_train, x_test, y_train, y_test


def train_model(x_train, y_train, n_neighbors=15, weights='uniform'):
    return KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights).fit(x_train, y_train)


def predict(classifier, x_test):
    return classifier.predict(x_test)


def estimate(result, y_test):
    accuracy = sum(result == y_test) / len(y_test)
    return round(accuracy, 3)


def scale(data, mode='standard'):
    if mode == 'standard':
        return StandardScaler().fit_transform(data)
    elif mode == 'minmax':
        return MinMaxScaler().fit_transform(data)
    elif mode == 'maxabs':
        return MaxAbsScaler().fit_transform(data)
    else:
        return None
