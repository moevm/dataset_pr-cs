from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler



def load_data(train_ratio=0.8, random_seed=42):
    wine_data = datasets.load_wine()
    features = wine_data.data[:, :2]  # Выбираем только первые два признака
    labels = wine_data.target
    X_train, X_test, y_train, y_test = train_test_split(
        features, labels, train_size=train_ratio, random_state=random_seed)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, k_neighbors=15, weight_method='uniform'):
    knn_classifier = KNeighborsClassifier(n_neighbors=k_neighbors, weights=weight_method)
    knn_classifier.fit(X_train, y_train)
    return knn_classifier

def predict(classifier, X_test):
    return classifier.predict(X_test)

def estimate(predicted_labels, y_test):
    accuracy = (predicted_labels == y_test).mean()
    return round(accuracy, 3)

def scale(data, mode='standard'):
    scaler_mapping = {
        'standard': StandardScaler(),
        'minmax': MinMaxScaler(),
        'maxabs': MaxAbsScaler()
    }
    scaler = scaler_mapping.get(mode)
    if scaler:
        scaled_data = scaler.fit_transform(data)
        return scaled_data
    else:
        return None
