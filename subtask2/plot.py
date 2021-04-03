import numpy as np
import matplotlib.pyplot as plt
#matplotlib.style.use('ggplot')

# Using numpy we can use the function loadtxt to load your CSV file.
# We ignore the first line with the column names and use ',' as a delimiter.
data = np.loadtxt('data.csv', delimiter=',', skiprows=1)

# You can access the columns directly, but let us just define them for clarity.
# This uses array slicing/indexing to cut the correct columns into variables.
frame = data[:,0]
queue_density = data[:,1]
dynamic_density = data[:,2]

# With matplotlib we define a new subplot with a certain size (10x10)
fig, ax = plt.subplots(figsize=(10,10))

ax.plot(frame, queue_density, label='QD')
ax.plot(frame, dynamic_density, label='DD')

# Show the legend
plt.show()

