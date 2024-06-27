from sklearn import datasets,neighbors, model_selection, metrics, preprocessing


def load_data(train_size=0.8):
    wine=datasets.load_wine()
    x_train,x_test,y_train,y_test=model_selection.train_test_split(wine.data, wine.target,train_size=train_size,random_state=42)
    return x_train[:,:2],x_test[:,:2],y_train,y_test

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    return neighbors.KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights).fit(X_train, y_train)

def predict(clf, x_test):
    return clf.predict(x_test)

def estimate(res, y_test):
    return round(metrics.accuracy_score(y_test,res),3)

def scale(data,mode='standard'):
    scalers = {
        'standard': preprocessing.StandardScaler(),
        'maxabs': preprocessing.MaxAbsScaler(),
        'minmax': preprocessing.MinMaxScaler()
    }
    if mode not in scalers.keys():
        return None
    return scalers[mode].fit_transform(data)