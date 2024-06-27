from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler


def load_data(train_size=0.8):
    wine = load_wine()
    features = wine.data[:, :2] 
    target = wine.target
    X_train, X_test, y_train, y_test = train_test_split(
        features,
        target,
        train_size=train_size,
        random_state=42
    )
    return X_train, X_test, y_train, y_test
    

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model


def predict(model, X_test):
    return model.predict(X_test)
    

def estimate(y_pred, y_test):
    accuracy = accuracy_score(y_test, y_pred)
    return round(accuracy, 3) 


def scale(X, mode='standard'):
    if mode == 'standard':
        scaler = StandardScaler()
    elif mode == 'minmax':
        scaler = MinMaxScaler()
    elif mode == 'maxabs':
        scaler = MaxAbsScaler()
    else:
        return None
    X_scaled = scaler.fit_transform(X)
    return X_scaled
