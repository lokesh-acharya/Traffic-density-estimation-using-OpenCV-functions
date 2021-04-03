import numpy as np
import matplotlib.pyplot as plt
#matplotlib.style.use('ggplot')

# Using numpy we can use the function loadtxt to load your CSV file.
# We ignore the first line with the column names and use ',' as a delimiter.
data = np.loadtxt('m12.csv', delimiter=',', skiprows=1)

# You can access the columns directly, but let us just define them for clarity.
# This uses array slicing/indexing to cut the correct columns into variables.
m1_runtime = data[:,0]
m1_utility = data[:,1]
m1_parameter = data[:,2]
m2_runtime = data[:,3]
m2_utility = data[:,4]
m2_parameter = data[:,5]

# With matplotlib we define a new subplot with a certain size (10x10)
fig, ax = plt.subplots(figsize=(10,10))
fig, bx = plt.subplots(figsize=(10,10))
ax.set_xlabel('x')
ax.set_ylabel('time (s)')
bx.set_xlabel('sampling')
bx.set_ylabel('mean absolute error')

ax.plot(m1_parameter, m1_runtime, label='m1_r')
ax.plot(m2_parameter, m2_runtime, label='m2_r')
bx.plot(m1_parameter, m1_utility, label='m1_u')
bx.plot(m2_parameter, m2_utility, label='m2_u')

# Show the legend
plt.show()
