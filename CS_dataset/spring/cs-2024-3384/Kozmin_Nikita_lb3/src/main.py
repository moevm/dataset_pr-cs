from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing
from numpy import ndarray


def load_data(train_size: float=0.8) -> list:
    """Загрузка набора данных о вине из библиотеки sklearn

    Args:
        train_size (float, optional): Размер обучающей выборки. Defaults to 0.8

    Returns:
        list: Набор данных, разделенный на тренировочные и тестовые значения и результаты
    """
    X, y = load_wine(return_X_y = True)
    X = X[:,:2]
    X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=train_size, random_state=42)
    return X_train, X_test, y_train, y_test

def train_model(X_train: ndarray, y_train: ndarray, n_neighbors: int=15, weights: str="uniform") -> KNeighborsClassifier:
    """Обучение модели. Классификация методом k-ближайших соседей

    Args:
        X_train (ndarray): Обучающую выборка (значения)
        y_train (ndarray): Обучающую выборка (результаты)
        n_neighbors (int, optional): Количество соседей, используемых по умолчанию для kneighbors запросов. Defaults to 15
        weights (str, optional): Весовая функция, используемая при прогнозировании. Defaults to "uniform"

    Returns:
        KNeighborsClassifier: Обученная модель
    """
    neigh = KNeighborsClassifier(n_neighbors, weights=weights)
    neigh.fit(X_train, y_train)
    return neigh

def predict(clf: KNeighborsClassifier, X_test: ndarray) -> ndarray:
    """Выполнение классификации данных

    Args:
        clf (KNeighborsClassifier): Обученная модель классификатора
        X_test (ndarray): Тренировочный набор данных

    Returns:
        ndarray: Предсказанные данные
    """
    return clf.predict(X_test)

def estimate(res: ndarray, y_test: ndarray) -> float:
    """Степень качества отработанной модели

    Args:
        res (ndarray): Результаты классификации
        y_test (ndarray): Метки тестовых данных

    Returns:
        float: Оценка, являющаяся отношением количества правильных ответов ко всем
    """
    # return round(sum((a == b for a, b in zip(res, y_test)))/len(y_test), 3)
    return round(accuracy_score(y_test, res), 3)

def scale(X: ndarray, mode: str="standard") -> ndarray:
    """Предобработка значений определенным способом, для повышения точности

    Args:
        X (ndarray): Значения
        mode (str, optional): Один из способов 'standard', 'minmax', 'maxabs'. Defaults to "standard"

    Returns:
        None | ndarray: Предобработанные значения
    """
    if mode == "standard":
        scaler = preprocessing.StandardScaler()
    elif mode == "minmax":
        scaler = preprocessing.MinMaxScaler()    
    elif mode == "maxabs":
        scaler = preprocessing.MaxAbsScaler()
    else:
        return None
    X_scale = scaler.fit_transform(X)
    return X_scale
