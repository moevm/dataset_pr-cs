from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
import sklearn.preprocessing


def load_data(train_size=0.8):
    model = datasets.load_wine()
    X = model.data[:, :2]
    y = model.target
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, test_size=1-train_size,  random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(X_train, y_train)
    return clf

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    return round(accuracy_score(y_test, res), 3)
    
def scale(data, mode='standard'):
    if(mode == 'minmax'):
        scaler = MinMaxScaler()
    elif(mode == 'maxabs'):
        scaler = MaxAbsScaler()
    elif(mode == 'standard'):
        scaler = StandardScaler()
    else:
        return None
    return scaler.fit_transform(data)