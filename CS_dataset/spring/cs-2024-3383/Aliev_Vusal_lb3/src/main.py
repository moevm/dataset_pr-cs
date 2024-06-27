from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler
from sklearn.metrics import accuracy_score
from sklearn import datasets

def load_data(train_size=0.8):
    wine_dataset = datasets.load_wine()
    features = wine_dataset.data
    labels = wine_dataset.target
    X_train, X_test, y_train, y_test = train_test_split(features[:, [0, 1]], labels, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

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

def train_model(train_data, train_labels, neighbors=15, weight='uniform'):
    knn_model = KNeighborsClassifier(n_neighbors=neighbors, weights=weight)
    knn_model.fit(train_data, train_labels)
    return knn_model

def predict(model, test_data):
    return model.predict(test_data)

def estimate(predictions, test_labels):
    return round(accuracy_score(test_labels, predictions), 3)