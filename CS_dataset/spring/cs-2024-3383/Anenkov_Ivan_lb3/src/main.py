from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import MinMaxScaler, StandardScaler, MaxAbsScaler

def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X = wine.data[:, :2]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, random_state = 42, train_size = train_size)
    return X_train, X_test, y_train, y_test
        
        
        
def train_model(X_train, y_train, n_neighbors = 15, weights = "uniform"):
    classification = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights, metric = "minkowski")
    classification.fit(X_train, y_train)
    return classification
    
    
def predict(classification, X_test):
    y_pred = classification.predict(X_test)
    return y_pred
    
def estimate(res, y_test):
    return round(accuracy_score(res, y_test), 3)
    
    
def scale(data, mode="standard"):
        if mode == "standard":
            scaler = StandardScaler()
            scaled_data = scaler.fit_transform(data)
            return scaled_data
        elif mode == "maxabs":
            scaler = MaxAbsScaler()
            scaled_data = scaler.fit_transform(data)
            return scaled_data
        elif mode == "minmax":
            scaler = MinMaxScaler()
            scaled_data = scaler.fit_transform(data)
            return scaled_data
        else:
            return None