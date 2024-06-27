from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

def load_data(train_size = 0.8):
    wine = load_wine()
    X_train, X_test, y_train, y_test = train_test_split(wine.data[:, 0:2], wine.target, train_size=train_size,
                                                           test_size=0.2, random_state=42)
    return X_train, X_test, y_train, y_test
    
def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    classifier = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    classifier.fit(X_train, y_train)

    return classifier
    
def predict(classifier, X_test):
    perdictions = classifier.predict(X_test)
    
    return perdictions
    
def estimate(predicitions, y_test):
    accuracy = accuracy_score(y_test, predicitions)
    accuracy = round(accuracy, 3)
    
    return accuracy
    
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
    
