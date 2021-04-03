import numpy as np
import matplotlib.pyplot as plt
#matplotlib.style.use('ggplot')

# Using numpy we can use the function loadtxt to load your CSV file.
# We ignore the first line with the column names and use ',' as a delimiter.
data = np.loadtxt('m34.csv', delimiter=',', skiprows=1)

# You can access the columns directly, but let us just define them for clarity.
# This uses array slicing/indexing to cut the correct columns into variables.
m1_runtime = data[:,0]
m1_utility = data[:,1]
m1_parameter = data[:,2]
m2_runtime = data[:,3]
m2_utility = data[:,4]
m2_parameter = data[:,5]
base_runtime = data[:,6]
base_para = data[:,7]

# With matplotlib we define a new subplot with a certain size (10x10)
fig, ax = plt.subplots(figsize=(10,10))
fig, bx = plt.subplots(figsize=(10,10))
ax.set_xlabel('num_threads')
ax.set_ylabel('time (s)')
bx.set_xlabel('num_threads')
bx.set_ylabel('mean absolute error')

ax.plot(m1_parameter, m1_runtime,'r-',label='method1')
ax.plot(m2_parameter, m2_runtime,'b-',label='method2')
ax.plot(base_para, base_runtime,'g-',label='base')
bx.plot(m1_parameter, m1_utility,'r-',label='method1')
bx.plot(m2_parameter, m2_utility,'b-',label='method2')

# Show the legend
plt.show()
