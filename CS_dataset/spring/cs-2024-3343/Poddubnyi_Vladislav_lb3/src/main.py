from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_ratio=0.8, random_seed=42):
    wine_dataset = datasets.load_wine()
    features = wine_dataset.data[:, :2]
    target = wine_dataset.target
    X_train, X_test, y_train, y_test = train_test_split(
        features, target, train_size=train_ratio, random_state=random_seed)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, k_neighbors=15, weight_method='uniform'):
    knn_classifier = KNeighborsClassifier(n_neighbors=k_neighbors, weights=weight_method)
    knn_classifier.fit(X_train, y_train)
    return knn_classifier

def predict(classifier, X_test):
    return classifier.predict(X_test)

def estimate(predicted_labels, y_test):
    return round((predicted_labels == y_test).mean(), 3)

def scale(data, mode='standard'):
    scalers = {
        'standard': StandardScaler(),
        'minmax': MinMaxScaler(),
        'maxabs': MaxAbsScaler()
    }
    selected_scaler = scalers.get(mode)
    return selected_scaler.fit_transform(data) if selected_scaler else None
