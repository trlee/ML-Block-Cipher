import tensorflow as tf
import pandas as pd
from sklearn.metrics import precision_score, recall_score, confusion_matrix, classification_report, accuracy_score, f1_score
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from sklearn.model_selection import StratifiedKFold
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score
from sklearn.dummy import DummyClassifier
from sklearn.linear_model import SGDClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.linear_model import Perceptron
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.ensemble import BaggingClassifier
from sklearn.svm import SVR
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.neural_network import MLPClassifier
# print(tf.__version__)
# print(pd.__version__)

#File Paths for Training and Testing Data
census = pd.read_csv("C:/Users/User/Desktop/NN Datasets/trainingdata500k.csv")

censustest = pd.read_csv("C:/Users/User/Desktop/NN Datasets/testingdata_secure.csv")

#def label_fix(label):
#    if label['ActiveSBox'] <= int(1.5*label['Rounds']):
#        if label['ActiveSBox'] < int(0.5*(label['Rounds']+1)):
#            return 0
#        else:
#            if label['ActiveSBox'] < int(1*label['Rounds']):
#                return 1
#            else:
#                return 2
#    else:
#        return 3

def label_fix(label):
    if label['ActiveSBox'] > int(1.5*label['Rounds']):
        return 1
    else:
        return 0

def perm_fix(label):
    perm_value = int(label['Perm1']*1000)+int(label['Perm2']*100)+int(label['Perm3']*10)+int(label['Perm4'])
    #print(perm_value)
    return perm_value

census['ActiveSBox'] = census.apply(label_fix, axis=1)
censustest['ActiveSBox'] = censustest.apply(label_fix, axis=1)

# Setting the Permutation data to the form of Rep1
#census['Perm1'] = census.apply(perm_fix, axis=1)
#censustest['Perm1'] = censustest.apply(perm_fix, axis=1)

y_labels = census['ActiveSBox']
testing_labels = censustest['ActiveSBox']
testing_data = censustest.drop(['ActiveSBox'], axis=1)

x_data = census.drop(['ActiveSBox'], axis=1)
#x_train, x_test, y_train, y_test = train_test_split(x_data,
#                                                    y_labels,
#                                                    test_size=0.2)

# K Fold Validation: Split data accordingly for experiments accordingly
skf = StratifiedKFold(n_splits=5)
skf.get_n_splits(x_data, y_labels)

print(skf)

for train_index, test_index in skf.split(x_data, y_labels):
    #print("TRAIN: ", train_index, "TEST: ", test_index)
    x_train, x_test = x_data.values[train_index], x_data.values[test_index]
    y_train, y_test = y_labels.values[train_index], y_labels.values[test_index]
    #print(x_train, x_test)
    #print(y_train, y_test)
    

#*****************************************************************************************
neigh = KNeighborsClassifier(n_neighbors=4, algorithm="ball_tree", leaf_size=40, n_jobs=-1)
#Cross Validation, enable accordingly
#print('Cross Val Score: ', cross_val_score(neigh, x_data, y_labels, cv=5))
neigh.fit(x_data, y_labels)
#neigh.fit(x_train, y_train)
predictions = neigh.predict(testing_data)
#predictions = neigh.predict(x_test)
print('KNN')

#Uncomment the following for baseline experiments
print('Predictions:', predictions)
print(classification_report(testing_labels, predictions))
print('Accuracy:', accuracy_score(testing_labels, predictions))
print('Recall:', recall_score(testing_labels, predictions, average="weighted"))
print('Precision:', precision_score(testing_labels, predictions, average="weighted"))
confusion = confusion_matrix(testing_labels, predictions)

#Uncomment the following for generalization experiments
#print(classification_report(y_test, predictions))
#print('Accuracy:', accuracy_score(y_test, predictions))
#print('Recall:', recall_score(y_test, predictions, average="weighted"))
#print('Precision:', precision_score(y_test, predictions, average="weighted"))
#confusion = confusion_matrix(y_test, predictions)

print('Confusion matrix:')
print(confusion)

#*****************************************************************************************
decisiontree = DecisionTreeClassifier( max_leaf_nodes=None, min_samples_split=2, splitter="random")
print('Decision Tree')
#Cross validation, enable accordingly
#print('Cross Val Score: ', cross_val_score(decisiontree, x_data, y_labels, cv=5))
decisiontree.fit(x_data, y_labels)
#decisiontree.fit(x_train, y_train)
predictions = decisiontree.predict(testing_data, check_input=True)
#predictions = decisiontree.predict(x_test, check_input=True)
score = decisiontree.score(testing_data, testing_labels, sample_weight=None)
#score = decisiontree.score(x_test, y_test, sample_weight=None)
print('Score: ', score)
print('Predictions: ', predictions)

#Uncomment the following for baseline experiments
print(classification_report(testing_labels, predictions))
print('Accuracy:', accuracy_score(testing_labels, predictions))
print('Recall:', recall_score(testing_labels, predictions, average="weighted"))
print('Precision:', precision_score(testing_labels, predictions, average="weighted"))
confusion = confusion_matrix(testing_labels, predictions)

#Uncomment the following for generalization experiments
#print(classification_report(y_test, predictions))
#print('Accuracy:', accuracy_score(y_test, predictions))
#print('Recall:', recall_score(y_test, predictions, average="weighted"))
#print('Precision:', precision_score(y_test, predictions, average="weighted"))
#confusion = confusion_matrix(y_test, predictions)

print('Confusion matrix:')
print(confusion)

#*****************************************************************************************
mlp = MLPClassifier(random_state=0, batch_size=5000, max_iter=1000, n_iter_no_change=1000)
#Cross Validation, enable accordingly
#print('Cross Val Score: ', cross_val_score(mlp, x_data, y_labels, cv=5))
print('MLP Classifier')
mlp.fit(x_data, y_labels)
#mlp.fit(x_train, y_train)
predictions = mlp.predict(testing_data)
score = mlp.score(testing_data, testing_labels, sample_weight=None)
#predictions = mlp.predict(x_test)
#score = mlp.score(x_test, y_test, sample_weight=None)
print('Score: ', score)
print('Predictions: ', predictions)

#Uncomment the following for baseline experiments
print(classification_report(testing_labels, predictions))
print('Accuracy:', accuracy_score(testing_labels, predictions))
print('Recall:', recall_score(testing_labels, predictions, average="weighted"))
print('Precision:', precision_score(testing_labels, predictions, average="weighted"))
confusion = confusion_matrix(testing_labels, predictions)

#Uncomment the following for generalization experiments
#print(classification_report(y_test, predictions))
#print('Accuracy:', accuracy_score(y_test, predictions))
#print('Recall:', recall_score(y_test, predictions, average="weighted"))
#print('Precision:', precision_score(y_test, predictions, average="weighted"))
#confusion = confusion_matrix(y_test, predictions)

print('Confusion matrix:')
print(confusion)

#*****************************************************************************************
model = LogisticRegression(n_jobs=-1, max_iter=500000)
model.fit(x_data, y_labels)
predictions = model.predict(testing_data)
#model.fit(x_train, y_train)
#predictions = model.predict(x_test)
print('LogisticRegression')
print('Predictions:' , predictions)

#Uncomment the following for baseline experiments
print(classification_report(testing_labels, predictions))
print('Accuracy:', accuracy_score(testing_labels, predictions))
print('Recall:', recall_score(testing_labels, predictions, average="macro"))
print('Precision:', precision_score(testing_labels, predictions, average="macro"))
confusion = confusion_matrix(testing_labels, predictions)

#Uncomment the following for generalization experiments
#print(classification_report(y_test, predictions))
#print('Accuracy: ', accuracy_score(y_test, predictions))
#print('Recall: ', recall_score(y_test, predictions, average="macro"))
#print('Prediction: ', precision_score(y_test, predictions, average="macro"))
#confusion = confusion_matrix(y_test, predictions)

print('Confusion matrix:')
print(confusion)

#*****************************************************************************************
model = Perceptron(n_jobs=-1, n_iter_no_change=750, max_iter=750)
model.fit(x_data, y_labels)
predictions = model.predict(testing_data)
#model.fit(x_train, y_train)
#predictions = model.predict(x_test)
print('Perceptron')
print('Predictions:' , predictions)

#Uncomment the following for baseline experiments
print(classification_report(testing_labels, predictions))
print('Accuracy:', accuracy_score(testing_labels, predictions))
print('Recall:', recall_score(testing_labels, predictions, average="macro"))
print('Precision:', precision_score(testing_labels, predictions, average="macro"))
confusion = confusion_matrix(testing_labels, predictions)

#Uncomment the following for generalization experiments
#print(classification_report(y_test, predictions))
#print('Accuracy: ', accuracy_score(y_test, predictions))
#print('Recall: ', recall_score(y_test, predictions, average="macro"))
#print('Prediction: ', precision_score(y_test, predictions, average="macro"))
#confusion = confusion_matrix(y_test, predictions)

print('Confusion matrix:')
print(confusion)
