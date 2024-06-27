import numpy as np
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(split_ratio=0.8, seed=42):
    wine_data = load_wine()
    features = wine_data.data[:, :2]
    target_labels = wine_data.target

    training_features, testing_features, training_labels, testing_labels = train_test_split(
        features, target_labels, train_size=split_ratio, random_state=seed
    )

    return training_features, testing_features, training_labels, testing_labels


def train_model(training_features, training_labels, neighbors=15, weights='uniform'):
    knn_model = KNeighborsClassifier(n_neighbors=neighbors, weights=weights)
    knn_model.fit(training_features, training_labels)

    return knn_model


def predict(model, testing_features):
    predicted_labels = model.predict(testing_features)

    return predicted_labels


def estimate(predicted_labels, ground_truth_labels):
    correct_predictions = np.equal(predicted_labels, ground_truth_labels)
    number_correct = np.sum(correct_predictions)
    accuracy = number_correct / len(ground_truth_labels)

    return round(accuracy, 3)


def scale(data, mode='standard'):
    valid_methods = ['standard', 'minmax', 'maxabs']
    if mode not in valid_methods:
        return None

    scaler_map = {
        'standard': StandardScaler(),
        'minmax': MinMaxScaler(),
        'maxabs': MaxAbsScaler()
    }

    scaler = scaler_map[mode]
    scaled_data = scaler.fit_transform(data)

    return scaled_data
