# importa modulos

from keras.datasets.mnist import load_data
import matplotlib.pyplot as plt
from keras.utils import to_categorical
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
import numpy as np

# ----------------------------------------------------------------

# carrega e pre processa os dados

(train_digits, train_labels), (test_digits, test_labels) = load_data()

np.random.seed(123)

rand_14 = np.random.randint(0, train_digits.shape[0],14)
sample_digits = train_digits[rand_14]
sample_labels = train_labels[rand_14]
num_rows, num_cols = 2, 7
f, ax = plt.subplots(num_rows, num_cols, figsize=(12,5),
                    gridspec_kw={'wspace':0.03, 'hspace':0.01}, 
                    squeeze=True)

for r in range(num_rows):
    for c in range(num_cols):
        image_index = r * 7 + c
        ax[r,c].axis("off")
        ax[r,c].imshow(sample_digits[image_index], cmap='gray')
        ax[r,c].set_title('No. %d' % sample_labels[image_index])
plt.show()
plt.close()

# ----------------------------------------------------------------

# reformula os dados das imagens

image_height = train_digits.shape[1]  
image_width = train_digits.shape[2]
num_channels = 1

train_data = np.reshape(train_digits, (train_digits.shape[0], image_height, image_width, num_channels))
test_data = np.reshape(test_digits, (test_digits.shape[0],image_height, image_width, num_channels))

# train_data = train_data.astype('float32') / 255.
# test_data = test_data.astype('float32') / 255.

num_classes = 10
train_labels_cat = to_categorical(train_labels,num_classes)
test_labels_cat = to_categorical(test_labels,num_classes)
train_labels_cat.shape, test_labels_cat.shape

# ----------------------------------------------------

# ajeita valores para treinamento e validacao

for _ in range(5): 
    indexes = np.random.permutation(len(train_data))

train_data = train_data[indexes]
train_labels_cat = train_labels_cat[indexes]

val_perc = 0.1
val_count = int(val_perc * len(train_data))

val_data = train_data[:val_count,:]
val_labels_cat = train_labels_cat[:val_count,:]

train_data2 = train_data[val_count:,:]
train_labels_cat2 = train_labels_cat[val_count:,:]

# ----------------------------------------------------

# constroi modelo

def build_model():

    model = Sequential()
    model.add(Conv2D(filters=32, kernel_size=(3,3), activation='relu', padding='same', input_shape=(image_height, image_width, num_channels)))
    model.add(MaxPooling2D(pool_size=(2,2)))
    model.add(Conv2D(filters=64, kernel_size=(3,3), activation='relu', padding='same'))
    model.add(MaxPooling2D(pool_size=(2,2)))
    model.add(Conv2D(filters=64, kernel_size=(3,3), activation='relu', padding='same'))
    model.add(MaxPooling2D(pool_size=(2,2)))    
    model.add(Flatten())
    model.add(Dense(128, activation='relu'))
    model.add(Dense(num_classes, activation='softmax'))
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
    return model

model = build_model()
print(model.summary())