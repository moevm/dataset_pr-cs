from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn import preprocessing

def load_data(train_size=0.8):
  wine = load_wine()
  z = np.delete(wine.data,list(range(2,13)),1)
  X,x,Y,y = train_test_split(z,wine.target,train_size=train_size,random_state=42)
  return X,x,Y,y

def train_model(X_train, y_train, n_neighbors=15, weights='uniform'):
  cls = KNeighborsClassifier(n_neighbors=n_neighbors,weights=weights)
  cls.fit(X_train,y_train)
  return cls

def predict(clf, X_test):
    return clf.predict(X_test)

def estimate(res, y_test):
    r = sum([res[i]==y_test[i] for i in range(len(res))])
    return round(r/(len(res)),3)
    
def scale(data,mode = 'standard'):
    if mode == 'standard':
      s = preprocessing.StandardScaler()
    elif mode == 'minmax':
      s = preprocessing.MinMaxScaler()
    elif mode == 'maxabs':
      s = preprocessing.MaxAbsScaler()
    else:
      return None
    return s.fit_transform(data)