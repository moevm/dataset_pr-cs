from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = datasets.load_wine()
    trainX, testX, trainY, testY = train_test_split(wine.data[:, :2], wine.target, train_size=train_size, random_state=42)
    return trainX, testX, trainY, testY


def train_model(trainX, trainY, n_neighbors=15, weights='uniform'):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(trainX, trainY)
    return clf

def scale(x, mode='standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None
    return scaler.fit_transform(x)


def predict(clf, x_test):
    return clf.predict(x_test)


def estimate(res, y_test):
    accuracy = accuracy_score(y_test, res)
    return round(accuracy, 3)
