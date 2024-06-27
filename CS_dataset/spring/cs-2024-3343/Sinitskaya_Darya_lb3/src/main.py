# импорт необходимых модулей из библиотеки scikit-learn
from sklearn import datasets, model_selection, neighbors, metrics, preprocessing

# функция для загрузки данных о вине и разделения их на обучающий и тестовый наборы
def load_data(train_size = 0.8):
    # загрузка данных о вине из встроенного набора данных
    wine = datasets.load_wine()
    X = wine.data  
    y = wine.target  
    # разделение данных на обучающий и тестовый наборы
    X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, random_state = 42, train_size = train_size)
    return X_train[:, :2], X_test[:, :2], y_train, y_test

# функция для обучения модели классификации методом k-ближайших соседей
def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    return neighbors.KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights).fit(X_train, y_train)

# функция для предсказания меток классов на тестовых данных
def predict(clf, X_test):
    return clf.predict(X_test)

# функция для оценки точности модели с помощью метрики accuracy
def estimate(res, y_test):
    accuracy = metrics.accuracy_score(y_test, res)
    return round(accuracy, 3)

# функция для масштабирования данных с использованием различных методов
def scale(data, mode = 'standard'):
    if mode == 'standard':
        scaler = preprocessing.StandardScaler()  # стандартизация данных
    elif mode == 'minmax':
        scaler = preprocessing.MinMaxScaler()  # масштабирование на отрезок [0, 1]
    elif mode == 'maxabs':
        scaler = preprocessing.MaxAbsScaler()  # масштабирование по максимальному абсолютному значению
    else:
        return None
    return scaler.fit_transform(data)