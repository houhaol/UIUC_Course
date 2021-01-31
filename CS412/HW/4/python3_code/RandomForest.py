import sys
import random
import operator
from collections import deque
import math
# import time

# start = time.clock()
#long running
#do something other


# Read File
(train, test) = sys.argv[1], sys.argv[2]
sample_size = 0.6
tree_size = 100

def get_train_file():
    data = []
    for i in range(tree_size):
        data.append([])    
    with open(train, 'r') as trainfile:
        label_count = 0
        for row in trainfile:
            row = row.strip().split(' ')
            label = row[0]
            temp = []
            temp.append(row[0])
            index_value = row[1:]
            label_count = max(label_count, int(label))
            for i in index_value:
                index, value = i.split(':')
                temp.append((index,value))
            # Random Select
            for i in range(tree_size):
                if random.random() < sample_size:
                    data[i].append(temp)
    return data, label_count

def get_test_file():
    labels = []
    test_data = []
    test_count = 0
    with open(test, 'r') as testfile:
        for row in testfile:
            temp = []
            row = row.strip().split(' ')
            label = row[0]
            temp.append(label)
            labels.append(label)
            index_value = row[1:]
            for i in index_value:
                index, value = i.split(':')
                temp.append(value)
            test_data.append(temp)
            test_count += 1
    return test_data, test_count, labels

def createMatrix(row, col):
	mat = []
	for i in range(int(row)):
		rowlist = []
		for j in range(int(col)):
			rowlist.append(0)
		mat.append(rowlist)
	return mat

# Need edit
def confusion_matrix_rf(num, label, predict_labels):
    label_by_major = []
    for i in range(len(label)):
        # print(predict_labels)
        temp = sorted(predict_labels[i].items(), key=lambda x:x[1], reverse=True)[0][0]
        label_by_major.append(temp)
    confusion_matrix = createMatrix(num,num)
    
    for j in range(len(label)):
        label_loc = int(label[j])-1
        predict = int(label_by_major[j]) -1
        confusion_matrix[label_loc][predict] += 1
    for row in confusion_matrix:
        num = []
        for i in row:
            num.append(str(i))
        sys.stdout.write(' '.join(num) + '\n')
    return confusion_matrix

def Accuracy(confusion_matrix):
    diag = 0
    all_entries = 0
    for i, item in enumerate(confusion_matrix):
        diag += item[i]
        for j in item:
            all_entries += j 
    Accuracy = diag/all_entries
    # print(Accuracy)
    return Accuracy

def rf_major (num_data,data,tree_size):
    result = []
    for i in range(num_data):
        result.append({})
    for i in range(tree_size):
        decisiontree = tree(data[i], 'rf')
        predict_labels = decisiontree.test(test)
        for j, label in enumerate(predict_labels):
            if label not in result[j]:
                result[j][label] = 0
            result[j][label] += 1
    return result

# def Accuracy(confusion_matrix):
#     diag = 0
#     all_entries = 0
#     for i, item in enumerate(confusion_matrix):
#         diag += item[i]
#         for j in item:
#             all_entries += j 
#     Accuracy = diag/all_entries
#     print(Accuracy)
#     return Accuracy

###############################################################################
# Node

class node():
    def __init__(self, data, model_type):
        self.data = data
        self.type = model_type
        # container for later use
        self.is_end = False
        self.label = None
        self.label_class = set()
        
        self.index = None
        self.all = {}
        self.num_index = {}
        self.num_value = {}
        self.num_label = {}
        self.gini_dic = {}
        self.maj_vot = 0
        
        self.sub = {}
        self.relation = {}

        self.generate()

        if self.is_end is False:
            self.gini()
            self.split()
        
    def generate(self):
        if len(self.data[0]) == 1:
            self.is_end = True
            labels = {}
            for row in self.data:
                label = row[0]
                if label not in labels:
                    labels[label] = 0
                labels[label] += 1
            self.label = sorted(labels.items(), key=lambda x: x[1], reverse=True)[0][0]
            return
        
        maj_vot = {}
        for row in self.data:
            label = row[0]
            if label not in maj_vot:
                maj_vot[label] = 0
            maj_vot[label] += 1 # The total number for each label
            self.label_class.add(label)
            
            for each in row[1:]:
                index = each[0]
                value = each[1]
                if index not in self.num_index:
                    self.all[index] = {}
                    self.num_index[index] = 0
                if value not in self.all[index]:
                    self.all[index][value] = set()
                if (index, value) not in self.num_value:
                    self.num_value[(index,value)] = 0
                if (index, value, label) not in self.num_label:
                    self.num_label[(index, value, label)] = 0
                self.all[index][value].add(label)
                self.num_index[index] +=1 # The total number of attributes for each index
                self.num_value[(index, value)] += 1 # The total number of each tuple
                self.num_label[(index, value, label)] += 1
            # print(self.num_index)
        self.maj_vot = sorted(maj_vot.items(), key=lambda x: x[1], reverse=True)[0][0]
        # print(self.maj_vot)
        if len(self.label_class) ==1: # Chech whether it's last one
            self.is_end = True
            self.label = list(self.label_class)[0]
            self.label_class = set()
        
        
    def gini(self):
        if self.type =='dt':
            for index in self.all.keys(): # For each index
                index_num = self.num_index[index]
                if index not in self.gini_dic:
                    self.gini_dic[index] = 0
                for value in self.all[index].keys():
                    value_num = float(self.num_value[(index, value)])
                    sub_gini = 1.0
                    for label in self.all[index][value]:
                        label_num = float((self.num_label[(index, value, label)]))
                        p = label_num/value_num
                        sub_gini -= p**2
                    gini = (value_num/index_num)*sub_gini
                    self.gini_dic[index] += gini
        if self.type == 'rf':
            indexs = self.all.keys()
            indexs = random.sample(indexs, int(math.ceil((len(indexs)/1.2))))
            for index in indexs:
                index_num = self.num_index[index]
                if index not in self.gini_dic:
                    self.gini_dic[index] = 0
                for value in self.all[index].keys():
                    value_num = float(self.num_value[(index, value)])
                    sub_gini = 1.0
                    for label in self.all[index][value]:
                        label_num = float((self.num_label[(index, value, label)]))
                        p = label_num/value_num
                        sub_gini -= p**2
                    gini = (value_num/index_num)*sub_gini
                    self.gini_dic[index] += gini
                    
    
    def split(self):
        self.index = sorted(self.gini_dic.items(), key=lambda x:x[1])[0][0]
        for row in self.data:
            temp = [row[0]]
            split = None
            for index_value in row[1:]:
                index = index_value[0]
                value = index_value[1]
                if index == self.index:
                    split = value
                else:
                    temp.append(index_value)
            if split not in self.sub:
                self.sub[split] = []
            self.sub[split].append(temp)

####################################################################################################

####################################################################################################
# Tree
class tree():
    def __init__(self, data, model_type):
        self.data = data
        self.type = model_type
        self.root = None
        self.generate()
        
    
    def generate(self):
        container = deque()
        

        if self.root is None:
            self.root= node(self.data, self.type)
            container.append(self.root)


        while len(container) >0 :
            current_node = container.pop()
            if current_node.is_end is True:
                continue
            for i in current_node.sub.keys():
                current_node.relation[i] = node(current_node.sub[i], self.type)
                container.append(current_node.relation[i])
    
    def test(self, data):
        correct_num = 0
        label_match = []
        labels = []
        for row in data:
            current_node = self.root
            prediction = None
            while current_node.is_end is False:
                index = int(current_node.index)
                if index >= len(row):
                    break
                value = row[index]
                if value not in current_node.relation:
                    break
                current_node = current_node.relation[value]
            if current_node.is_end:
                prediction = current_node.label
            else:
                prediction = current_node.maj_vot
            if prediction == row[0]:
                correct_num += 1
            label_match.append((row[0], prediction))
            labels.append(prediction)
        if self.type == 'dt':
            return correct_num, label_match
        else:
            return labels




data, num_class = get_train_file()
test, num_data, label = get_test_file()
rf_major_count = rf_major(num_data,data,tree_size)    
confusion_matrix = confusion_matrix_rf(num_class, label, rf_major_count)
# accuracy = Accuracy(confusion_matrix)

# end = time.clock()
# print (end-start)

################
"Reference: https://github.com/bwang8482"
