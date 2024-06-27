from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size=0.8):
    wine_data = datasets.load_wine()
    
    features = wine_data.data[:, :2]
    target = wine_data.target
    
    X_train, X_test, y_train, y_test = train_test_split(features, target, train_size=train_size, random_state=42)
    
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    model = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    model.fit(X_train, y_train)
    return model

def predict(clf, X_test):
    predictions = clf.predict(X_test)
    return predictions

def estimate(predictions, y_test):
    accuracy = (predictions == y_test).mean()
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