from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler, MaxAbsScaler

#Загрузка данных
def load_data(train_size=0.8):
    wine = datasets.load_wine()
    X_train, X_test, y_train, y_test = train_test_split(
        wine.data[:, :2],  #Берем только первые два признака
        wine.target,
        train_size=train_size,
        random_state=42
    )
    return X_train, X_test, y_train, y_test

#Обучение модели
def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
    clf = KNeighborsClassifier(n_neighbors=n_neighbors, weights=weights)
    clf.fit(X_train, y_train)
    return clf

#Применение модели
def predict(clf, X_test):
    return clf.predict(X_test)

#Оценка качества
def estimate(y_pred, y_test):
    accuracy = accuracy_score(y_pred, y_test)
    return round(accuracy, 3)

#Предобработка данных
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