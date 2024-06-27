from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size=.8):
    wine_dataset = datasets.load_wine()
    features = wine_dataset.data
    labels = wine_dataset.target
    X_train, X_test, y_train, y_test = train_test_split(features[:, [0,1]], labels, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    classifier = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    classifier.fit(X_train, y_train)
    return classifier

def predict(clf, X_test):
    predictions = clf.predict(X_test)
    return predictions

def estimate(res, y_test):
    accuracy = accuracy_score(y_true=y_test, y_pred=res)
    return round(accuracy, 3)

def scale(X, mode = "standard"):
    if mode not in ["standard", "minmax", "maxabs"]:
        return None
    scaler = StandardScaler()
    if mode == "minmax":
        scaler = MinMaxScaler()
    elif mode == "maxabs":
        scaler = MaxAbsScaler()
    scaled = scaler.fit_transform(X)
    return scaled