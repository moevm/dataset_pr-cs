from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = load_wine()

    x = wine.data[:, 0:2]
    y = wine.target

    train_x, test_x, train_y, test_y = train_test_split(x, y,
                                                        train_size=train_size,
                                                        test_size=1 - train_size,
                                                        random_state=42)

    return train_x, test_x, train_y, test_y


def train_model(train_x, train_y, n_neighbors=15, weights='uniform'):
    classifier = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    classifier.fit(train_x, train_y)

    return classifier


def predict(classifier, test_x):
    prediction_y = classifier.predict(test_x)

    return prediction_y


def estimate(res, test_y):
    accuracy = accuracy_score(test_y, res)

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

    scaled_data = scaler.fit_transform(data)

    return scaled_data
